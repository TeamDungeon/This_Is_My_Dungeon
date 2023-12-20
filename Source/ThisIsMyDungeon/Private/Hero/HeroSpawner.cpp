#include "Hero/HeroSpawner.h"

#include "Hero/Hero.h"
#include "Dungeon/DungeonManager.h"

#include <Kismet/GameplayStatics.h>

AHeroSpawner::AHeroSpawner() { PrimaryActorTick.bCanEverTick = false; }

void AHeroSpawner::BeginPlay()
{
	Super::BeginPlay();

	WTM = &GetWorldTimerManager();

	WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), this, &AHeroSpawner::GetDungeonManager, timeBeforeStart / 2.f, false);

	WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), this, &AHeroSpawner::SpawnWave, timeBeforeStart, false);

	SortWaveList();
}

void AHeroSpawner::SortWaveList()
{
	if (waveStructure.Num() <= 0)
		return;

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

		// else two waves have the same ID
		else if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroSpawner::BeginPlay Sort failled, two wave have the same ID"));
	}
}

void AHeroSpawner::SpawnWave()
{
	if (waveStructure.Num() <= 0)
	{
		WavesAreOver();
		return;
	}

	currentWave++;
	dManager->OnNewWave();
	float totalWaveTime = waveStructureSorted[currentWave].timeBetweenWaves + .5f;

	// Set every Hero to spawn with a timer
	for (int i = 0; i < waveStructureSorted[currentWave].heroesToSpawn.Num(); i++)
	{
		float waitForSpawnTime = waveStructureSorted[currentWave].timeBetweenSpawns * i;

		totalWaveTime += waitForSpawnTime;

		auto spawnHeroDelegate = FTimerDelegate::CreateUObject(this,
			&AHeroSpawner::SpawnAHero, waveStructureSorted[currentWave].heroesToSpawn[i]);

		WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), spawnHeroDelegate, waitForSpawnTime, false);
	}

	if (currentWave + 1 < waveStructureSorted.Num())
	{
		WTM->SetTimer(everyTimer.AddDefaulted_GetRef(), this, &AHeroSpawner::SpawnWave, totalWaveTime, false);
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
	SetStartTransform();
	auto theHero = GetWorld()->SpawnActor<AHero>(aHero.heroType, startTransform);
	if (theHero)
	{
		allHeroesSpawned.Add(theHero);
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT || WITH_EDITOR
		theHero->SetFolderPath("Heroes");
#endif
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

void AHeroSpawner::SetStartTransform()
{
	startWaypoint = dManager->waypointList.Last();

	startPoint = dManager->nextRoomPos;
	startPoint += extraHeightToSpawn;

	startRotation.Yaw = 180.f;

	startTransform = FTransform(startRotation, startPoint);
}

void AHeroSpawner::GetDungeonManager()
{
	TArray<AActor*> arrayDungeonManager;
	if (UWorld* World = GetWorld())
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonManager::StaticClass(), arrayDungeonManager);
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroSpawner::GetDungeonManager Coudn't get World for " + GetName()));
		return;
	}

	if (arrayDungeonManager.Num() != 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroSpawner::GetDungeonManager Coudn't get THE DungeonManager for " + GetName()));
		return;
	}
	dManager = Cast<ADungeonManager>(arrayDungeonManager[0]);

	SetStartTransform();
}

void AHeroSpawner::WavesAreOver_Implementation() { /* For BP use*/ }