#include "Hero/Hero.h"

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

	moveComponent->MaxWalkSpeed = speed * 100.f;

	weaponScale.SetNum(nbWeaponsMax);
	SetWeaponSize();

	//FTimerHandle deathAnimHandle;
	//auto spawnHeroDelegate = FTimerDelegate::CreateUObject(this, &AHero::GetDamaged, 1000.f); // for test purpose
	//GetWorldTimerManager().SetTimer(deathAnimHandle, spawnHeroDelegate, 6.f, false);
}

void AHero::Tick(float deltaTime)
{
	Super::Tick(deltaTime); // /!\ PrimaryActorTick.bCanEverTick = false;
}

void AHero::DemonDetected(ADemon* demon)
{
	demonInRange = demon;
	if (demonInRange == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange,
				TEXT("AHero::DemonDetected Called but no Demon at hand for " + GetName()));
		return;
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			TEXT("AHero::DemonDetected Called success for " + GetName()));

	AHeroController* controller = Cast<AHeroController>(GetController());
	controller->DemonDetected(demonInRange);
}

void AHero::DemonLost()
{
	if (demonInRange == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange,
				TEXT("AHero::DemonLost Called but no Demon at hand for " + GetName()));
		return;
	}

	demonInRange = nullptr;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			TEXT("AHero::DemonLost Called success for " + GetName()));
}

void AHero::GetDamaged(float value)
{
	Super::GetDamaged(value);

	if (!IsAlive() && GetLifeSpan() == 0.f)
		Death();
}

void AHero::Death()
{
	SetLifeSpan(lifeSpanOnDeath);
	moveComponent->StopActiveMovement();

	FTimerHandle deathAnimHandle;
	GetWorldTimerManager().SetTimer(deathAnimHandle, this, &AHero::DeadBlinking, blinkingSpeed, true);
}

void AHero::DeadBlinking()
{
	GetMesh()->SetVisibility(!GetMesh()->IsVisible());
}

void AHero::Upgrade(int nbUpgrades)
{
	if (upgradeLevel >= weaponOnUpgrade.Num())
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange,
				TEXT("AHero::Upgrade Called but already at max lvl possible for " + GetName()));
		return;
	}

	if ((upgradeLevel + nbUpgrades) >= weaponOnUpgrade.Num())
	{
		nbUpgrades = weaponOnUpgrade.Num() - upgradeLevel - 1;
		if (nbUpgrades <= 0) 
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange,
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
		weaponScale[i] = FVector((double)weaponOnUpgrade[upgradeLevel].bIsOnDisplay[i]);
	bUpgradeDone = true;
}

bool AHero::IsMoving()
{
	return GetVelocity().Length() > 0.f;
}

bool AHero::IsAttacking()
{
	return demonInRange != nullptr;
}