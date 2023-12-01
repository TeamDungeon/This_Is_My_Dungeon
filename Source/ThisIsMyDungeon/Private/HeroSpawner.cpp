#include "HeroSpawner.h"

AHeroSpawner::AHeroSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHeroSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle startWaveHandle;
	FTimerDelegate startWaveDelegate = FTimerDelegate::CreateUObject(this, &AHeroSpawner::SpawnWave, 1);
	GetWorldTimerManager().SetTimer(startWaveHandle, startWaveDelegate, timeBeforeStart, false);
}

void AHeroSpawner::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AHeroSpawner::SpawnWave(int waveID)
{
	GetWorld()->SpawnActor<AHero>(heroesToSpawn[0], GetActorTransform());
	GetWorld()->SpawnActor<AHero>(heroesToSpawn[0], GetActorTransform());
	GetWorld()->SpawnActor<AHero>(heroesToSpawn[0], GetActorTransform());
	GetWorld()->SpawnActor<AHero>(heroesToSpawn[0], GetActorTransform());
}