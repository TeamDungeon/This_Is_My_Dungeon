#include "Hero.h"

#include "HeroController.h"
#include "GameFramework/CharacterMovementComponent.h"

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationYaw = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AHeroController::StaticClass();

	moveComponent = GetCharacterMovement();

	for (int i = 0; i < nbWeaponsTotal; i++)
		weaponScale.AddDefaulted();

	SetWeaponSize();
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
	moveComponent->MaxWalkSpeed = speed * 100.f;

	FTimerHandle deathAnimHandle;
	auto spawnHeroDelegate = FTimerDelegate::CreateUObject(this, &AHero::GetDamaged, 1000.f);
	GetWorldTimerManager().SetTimer(deathAnimHandle, spawnHeroDelegate, 6.f, false);
}

void AHero::Tick(float deltaTime)
{
	Super::Tick(deltaTime); // /!\ PrimaryActorTick.bCanEverTick = false;
}

void AHero::DemonDetected()
{
	if (demonInRange == nullptr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
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
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
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

void AHero::Upgrade(int nbUgrades)
{
	upgradeLevel += nbUgrades;
	treasureDrop += treasureUpgrade * nbUgrades;
	health += healthUpgrade * nbUgrades;
	speed += speedUpgrade * nbUgrades;
	damage += damageUpgrade * nbUgrades;

	SetWeaponSize();
}

bool AHero::IsMoving()
{
	return GetVelocity().Length() > 0.f;
}

bool AHero::IsAttacking()
{
	return isAttacking;
}

void AHero::SetWeaponSize()
{
	for (int i = 0; i < nbWeaponsTotal; i++)
		weaponScale[i] = FVector::Zero();

	switch (upgradeLevel)
	{
	case 0:
		weaponScale[0] = FVector::One(); // == simple sword
		break;

	case 1:
		weaponScale[0] = FVector::One(); // == simple sword
		weaponScale[2] = FVector::One(); // == simple sword (other hand)
		break;

	case 2:
		weaponScale[1] = FVector::One(); // == upgraded sword
		break;

	case 3:
		weaponScale[1] = FVector::One(); // == upgraded sword
		weaponScale[3] = FVector::One(); // == shield lvl1
		break;

	case 4:
		weaponScale[1] = FVector::One(); // == upgraded sword
		weaponScale[4] = FVector::One(); // == shield lvl2
		break;

	case 5:
		weaponScale[1] = FVector::One(); // == upgraded sword
		weaponScale[5] = FVector::One(); // == shield lvl3
		break;

	default:
	case 6:
		weaponScale[1] = FVector::One(); // == upgraded sword
		weaponScale[6] = FVector::One(); // == shield lvl4
		break;
	}

	bUpgradeDone = true;
}