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
}

void AHero::Tick(float deltaTime)
{
	Super::Tick(deltaTime); // PrimaryActorTick.bCanEverTick = false;
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

void AHero::Upgrade(int nbUgrades)
{
	for (int i = 0; i < nbUgrades; i++)
		UpgradeOne();
}

void AHero::UpgradeOne()
{
	upgradeLevel++;
	treasureDrop += treasureUpgrade;
	health += healthUpgrade;
	speed += speedUpgrade;
	damage += damageUpgrade;
}