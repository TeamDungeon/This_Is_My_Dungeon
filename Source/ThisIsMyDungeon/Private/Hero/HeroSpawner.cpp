#include "Hero/HeroSpawner.h"

#include "Hero/Hero.h"
#include "DungeonManager.h"

#include <Kismet/GameplayStatics.h>

AHeroSpawner::AHeroSpawner() { PrimaryActorTick.bCanEverTick = false; }

void AHeroSpawner::BeginPlay()
{
	Super::BeginPlay();

	WTM = &GetWorldTimerManager();

	WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), this, &AHeroSpawner::GetStartWaypoint, timeBeforeStart, false);

	WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), this, &AHeroSpawner::SpawnWave, timeBeforeStart + 2.f, false);

	SortWaveList();
}

void AHeroSpawner::SortWaveList()
{
	waveStructureSorted.Add(waveStructure[0]);
	for (int i = 1; i < waveStructure.Num(); i++)
	{
		// if wave ID smaller than start wave sorted, add to front
		if (waveStructureSorted[0].waveID > waveStructure[i].waveID)
			waveStructureSorted.Insert(waveStructure[i], 0);

		// if wave ID smaller than last wave sorted, add to back
		else if (waveStructureSorted.Last().waveID < waveStructure[i].waveID)
			waveStructureSorted.Add(waveStructure[i]);

		// else check where to insert wave
		else if (waveStructureSorted[0].waveID < waveStructure[i].waveID)
			for (int j = 0; j < waveStructureSorted.Num(); j++)
			{
				if (waveStructureSorted[j].waveID > waveStructure[i].waveID)
				{
					waveStructureSorted.Insert(waveStructure[i], j);
					break;
				}
			}
		// else two wave have the same ID
		else if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroSpawner::BeginPlay Sort failled, two wave have the same ID"));
	}
}

void AHeroSpawner::SpawnWave()
{
	float totalWaveTime = waveStructureSorted[currentWave].timeBetweenWaves;

	// Set every Hero to span with a timer
	for (int i = 0; i < waveStructureSorted[currentWave].heroesToSpawn.Num(); i++)
	{
		float waitForSpawnTime = waveStructureSorted[currentWave].timeBetweenSpawns * i;

		if (waitForSpawnTime == 0.f) // Timer with 0 seconde will not do anything
			SpawnAHero(waveStructureSorted[currentWave].heroesToSpawn[i]);
		else
		{
			totalWaveTime += waitForSpawnTime;

			auto spawnHeroDelegate = FTimerDelegate::CreateUObject(this,
				&AHeroSpawner::SpawnAHero, waveStructureSorted[currentWave].heroesToSpawn[i]);

			WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), spawnHeroDelegate, waitForSpawnTime, false);
		}
	}

	if (currentWave + 1 < waveStructureSorted.Num())
	{
		WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), this, &AHeroSpawner::SpawnWave, totalWaveTime, false);

		currentWave++;
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green,
				TEXT("AHeroSpawner::SpawnWave All waves spawned"));

		WTM->SetTimer(endHandle, this, &AHeroSpawner::IsGameOver, 1.f, true);
	}
}

void AHeroSpawner::SpawnAHero(FHeroToSpawn aHero)
{
	auto theHero = GetWorld()->SpawnActor<AHero>(aHero.heroType, startTransform);
	if (theHero)
	{
		allHeroesSpawned.Add(theHero);
		if (GEngine)
			theHero->SetFolderPath("Heroes");
		theHero->SetStartWaypoint(startWaypoint);
		if (aHero.upgradeLevel)
			theHero->Upgrade(aHero.upgradeLevel);
	}
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
			TEXT("AHeroSpawner::SpawnAHero Hero wasn't spawned"));
}

void AHeroSpawner::IsGameOver()
{
	for (int i = 0; i < allHeroesSpawned.Num(); i++)
		if (!allHeroesSpawned[i]->IsAlive())
			allHeroesSpawned.Remove(allHeroesSpawned[i]);

	if (allHeroesSpawned.Num() == 0)
		WavesAreOver(); // Call for BP use
}

void AHeroSpawner::PauseSpawner()
{
	for (int i = 0; i < everyTimer.Num(); i++)
		if (everyTimer[i].IsValid())
		{
			if (WTM->IsTimerActive(everyTimer[i]))
				WTM->PauseTimer(everyTimer[i]);

			else if (!WTM->TimerExists(everyTimer[i]))
				everyTimer.Remove(everyTimer[i]);
		}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
			TEXT("AHeroSpawner::Pause All timer paused"));

	bPaused = true;
}

void AHeroSpawner::UnpauseSpawner()
{
	for (int i = 0; i < everyTimer.Num(); i++)
		if (everyTimer[i].IsValid())
		{
			if (WTM->IsTimerPaused(everyTimer[i]))
				WTM->UnPauseTimer(everyTimer[i]);

			else if (!WTM->TimerExists(everyTimer[i]))
				everyTimer.Remove(everyTimer[i]);
		}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
			TEXT("AHeroSpawner::Unpause All timer unpaused"));

	bPaused = false;
}

void AHeroSpawner::GetStartWaypoint()
{
	TArray<AActor*> dManager;
	if (UWorld* World = GetWorld())
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonManager::StaticClass(), dManager);
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroSpawner::GetStartWaypoint Coudn't get World for " + GetName()));
		return;
	}

	if (dManager.Num() != 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroSpawner::GetStartWaypoint Coudn't get THE DungeonManager for " + GetName()));
		return;
	}

	auto uniqueManager = Cast<ADungeonManager>(dManager[0]);

	startWaypoint = uniqueManager->WaypointList.Last();

	startPoint = uniqueManager->NextRoomPos;
	startPoint += extraHeightToSpawn;

	startRotation.Yaw = 180.f;

	startTransform = FTransform(startRotation, startPoint);
}

void AHeroSpawner::WavesAreOver_Implementation() { /* For BP use*/ }