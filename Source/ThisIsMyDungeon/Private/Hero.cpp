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

void AHero::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
}