#include "Hero.h"

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;
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

void AHero::UpgradeOne()
{
}

void AHero::FindRoomPath()
{
}

void AHero::GetNextPoint()
{
}

void AHero::DoSpecialAbility_Implementation()
{
}

bool AHero::IsPlayerInRange()
{
	return false;
}

void AHero::BarricadeInRange()
{
	isBarricadeInRange = !isBarricadeInRange;
}