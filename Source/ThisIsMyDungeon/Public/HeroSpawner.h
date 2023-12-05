#pragma once

#include <Hero.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroSpawner.generated.h"

USTRUCT(BlueprintType)
struct FHeroToSpawn
{
	GENERATED_BODY()

public:
	// SPAWNS BLUEPRINTS (NOT C++ CLASSES)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	TSubclassOf<AHero> heroType;

	// 0 if no upgrade levels need applying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	int upgradeLevel = 0;
};

USTRUCT(BlueprintType)
struct FWaveStruct
{
	GENERATED_BODY()

public:
	// Wave ID can start at with any (int) number (negatives < 0 < positives)
	// But will play in-game from smallest to biggest ID (negative numbers included)
	// If two waves have the same ID, only first one (in Array) will be added to the final waves system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	int waveID = 0;

	// Heroes will spawn at a regular pace (for now at least) (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float timeBetweenSpawns = -1.f;

	// Time between this wave and the next (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float timeBetweenWaves = -1.f;

	// The wave composition itself
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	TArray<FHeroToSpawn> heroesToSpawn;
};

UCLASS()
class THISISMYDUNGEON_API AHeroSpawner : public AActor
{
	GENERATED_BODY()

public:
	AHeroSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float timeBeforeStart = 0.f;

	// Waves can be sorted by any order you wish
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	TArray<FWaveStruct> waveStructure;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values", meta = (AllowPrivateAccess = "true"))
	bool isPaused = false;

	TArray<FTimerHandle> everyTimer;
	FTimerManager* WTM = nullptr; // world timer manager

	TArray<FWaveStruct> waveStructureSorted;
	int currentWave = 0;

	// FUNCTIONS
protected:
	virtual void BeginPlay() override;

	virtual void SortWaveList();
	virtual void SpawnWave();
	virtual void SpawnAHero(FHeroToSpawn aHero);

public:
	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void PauseSpawner();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void UnpauseSpawner();
};
