#include "Hero.h"

#include "HeroController.h"

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AHeroController::StaticClass();
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
}

void AHero::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AHero::Upgrade(int nbUgrades)
{
	for (int i = 0; i < nbUgrades; i++)
		UpgradeOne();
}

FVector AHero::GetWaypoint()
{
	return currentWaypoint;
}

void AHero::SetWaypoint(FVector newWaypoint)
{
	currentWaypoint = newWaypoint;
}

bool AHero::GetHeroAtEnd()
{
	return isAtTheEnd;
}

void AHero::SetHeroAtEnd(bool value)
{
	isAtTheEnd = value;
}

void AHero::UpgradeOne()
{
	upgradeLevel++;
	treasureDrop += treasureUpgrade;
	health += healthUpgrade;
	speed += speedUpgrade;
	damage += damageUpgrade;
}

void AHero::FindRoomPath()
{
}

void AHero::DoSpecialAbility()
{
}

bool AHero::IsPlayerInRange()
{
	return false;
}

void AHero::BarricadeInRange()
{
}