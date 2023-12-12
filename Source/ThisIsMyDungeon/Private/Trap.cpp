#include "Trap.h"

ATrap::ATrap()
{
	PrimaryActorTick.bCanEverTick = true;
}

int ATrap::GetCost() const
{
	return cost;
}

FUintVector2 ATrap::GetTileSize() const
{
	return tileSize;
}

void ATrap::BeginPlay()
{
}

void ATrap::Tick(float DeltaTime)
{
}

void ATrap::Upgrade()
{
}

void ATrap::Destroy()
{
}