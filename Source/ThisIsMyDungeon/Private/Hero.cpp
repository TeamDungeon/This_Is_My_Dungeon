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
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	moveComponent->MaxWalkSpeed = speed * 100.f;

	weaponScale.SetNum(nbWeaponsMax);
	weaponOnUpgrade.SetNum(nbPossibleUpgrades);
	for (int i = 0; i < nbPossibleUpgrades; i++)
		weaponOnUpgrade[i].bIsOnDisplay.SetNum(nbWeaponsMax);

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

void AHero::Upgrade(int nbUgrades)
{
	if (upgradeLevel >= nbPossibleUpgrades)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange,
				TEXT("AHero::Upgrade Called but already at max lvl possible for " + GetName()));
		return;
	}

	upgradeLevel += nbUgrades;
	treasureDrop += treasureUpgrade * nbUgrades;
	health += healthUpgrade * nbUgrades;
	speed += speedUpgrade * nbUgrades;
	damage += damageUpgrade * nbUgrades;

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