#include "Hero/Hero.h"

#include "Demon.h"

#include "StaticVars.h"

#include "Hero/HeroController.h"
#include "GameFramework/CharacterMovementComponent.h"

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationYaw = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AHeroController::StaticClass();

	moveComponent = GetCharacterMovement();
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	WTM = &GetWorldTimerManager();
	controller = Cast<AHeroController>(GetController());

	moveComponent->MaxWalkSpeed = speed * 100.f;

	weaponScale.SetNum(nbWeaponsMax);
	SetWeaponSize();
}

void AHero::DemonDetected(ADemon* demon)
{
	if (!controller->IsDemonInSight(demon)) // Check if demon in sight to avoid detection through walls
		return;

	demonInRange = demon;
	if (demonInRange == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange,
				TEXT("AHero::DemonDetected Called but no Demon at hand for " + GetName()));
		return;
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green,
			TEXT("AHero::DemonDetected Called success for " + GetName()));

	controller->DemonDetected(demonInRange);

	WTM->SetTimer(attackHandle, this, &AHero::AttackDemon, timerAttackMoment);
}

void AHero::DemonLost()
{
	WTM->ClearTimer(attackHandle);

	if (demonInRange == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange,
				TEXT("AHero::DemonLost Called but no Demon at hand for " + GetName()));
		return;
	}

	demonInRange = nullptr;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green,
			TEXT("AHero::DemonLost Called success for " + GetName()));
}

void AHero::GetDamaged(float value)
{
	Super::GetDamaged(value);

	if (!IsAlive() && GetLifeSpan() == 0.f)
		Death();
	else
	{
		if (WTM->TimerExists(damageAnimHandle))
		{
			GetMesh()->SetVisibility(true);
			blinkingCpt = 0;
			WTM->ClearTimer(damageAnimHandle);
		}
		// Blinking when damaged
		WTM->SetTimer(damageAnimHandle, this, &AHero::DamageBlinking, blinkingSpeed, true);
	}
}

void AHero::SetStartWaypoint(AWaypoint* startWaypoint)
{
	if (!controller)
	{
		controller = Cast<AHeroController>(GetController());
	}
	if (!startWaypoint)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHero::SetStartWaypoint Called but no Waypoint was sent for " + GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHero::SetStartWaypoint Death for " + GetName()));
		}
		SetLifeSpan(.5f);
		return;
	}
	controller->SetStartWaypoint(startWaypoint);
}

void AHero::Death()
{
	SetLifeSpan(lifeSpanOnDeath);
	moveComponent->StopActiveMovement();

	static_cast<ADemon*>(static_player)->mana += manaDrop;
}

void AHero::LootTreasure()
{
}

void AHero::DamageBlinking()
{
	blinkingCpt++;
	if (blinkingCpt >= blinkingAmount)
	{
		GetMesh()->SetVisibility(true);
		blinkingCpt = 0;
		WTM->ClearTimer(damageAnimHandle);

		return;
	}
	else
		GetMesh()->SetVisibility(!GetMesh()->IsVisible());
}

void AHero::Upgrade(int nbUpgrades)
{
	if (upgradeLevel >= weaponOnUpgrade.Num())
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange,
				TEXT("AHero::Upgrade Called but already at max lvl possible for " + GetName()));
		return;
	}

	if ((upgradeLevel + nbUpgrades) >= weaponOnUpgrade.Num())
	{
		nbUpgrades = weaponOnUpgrade.Num() - upgradeLevel - 1;
		if (nbUpgrades <= 0)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange,
					TEXT("AHero::Upgrade Called but no upgrade possible for " + GetName()));
			return;
		}
	}

	upgradeLevel += nbUpgrades;
	treasureDrop += treasureUpgrade * nbUpgrades;
	health += healthUpgrade * nbUpgrades;
	speed += speedUpgrade * nbUpgrades;
	damage += damageUpgrade * nbUpgrades;

	SetWeaponSize();
}

void AHero::SetWeaponSize()
{
	for (int i = 0; i < nbWeaponsMax; i++)
		weaponScale[i] = FVector((double)weaponOnUpgrade[upgradeLevel].bOnDisplay[i]);
	bUpgradeDone = true;
}

void AHero::AttackDemon()
{
	if (!demonInRange)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Orange,
				TEXT("AHero::AttackDemon Called but no demon in range anymore " + GetName()));
		return;
	}

	demonInRange->GetDamaged(damage);

	WTM->SetTimer(attackHandle, this, &AHero::AttackDemon, attackSequence->GetPlayLength());
}

bool AHero::IsMoving()
{
	return GetVelocity().Length() > 0.f;
}

bool AHero::IsAttacking()
{
	return WTM->TimerExists(attackHandle);
}