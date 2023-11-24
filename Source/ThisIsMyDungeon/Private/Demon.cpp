#include "Demon.h"

ADemon::ADemon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADemon::BeginPlay()
{
	Super::BeginPlay();
}

void ADemon::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

bool ADemon::IsTileEmpty()
{
	return false;
}

void ADemon::CollideWithCollectible()
{
}

void ADemon::PlaceTile()
{
}
