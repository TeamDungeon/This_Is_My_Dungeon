#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroSpawner.generated.h"

/*
*	HeroSpawner handles the wave system of the game
*	Spawns the specified hero (and sets them up) when demanded
*	Wave system is not generated randomly, it's all Blueprint
*	It uses a lot of timers, so it has a small timer management system
*/

USTRUCT(BlueprintType)
struct FHeroToSpawn
{
	GENERATED_BODY()

public:
	// SPAWNS BLUEPRINTS (NOT C++ CLASSES)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Hero to spawn (BP ONLY)"))
	TSubclassOf<class AHero> heroType;

	// 0 if no upgrade levels need applying
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Hero upgarde lvl (starts at 0)"))
	int upgradeLevel = 0;
};

USTRUCT(BlueprintType)
struct FWaveStruct
{
	GENERATED_BODY()

public:
	// Wave ID can start at with any (int) number (negatives < 0 < positives)
	// But will play in-game from smallest to biggest ID (negative numbers included)
	// If two waves have the same ID, only first one (in the array) will be added to the final waves system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Wave ID (Check description)"))
	int waveID = 0;

	// Heroes will spawn at a regular pace (for now at least) (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeBetweenSpawns = -1.f;

	// Time between this wave and the next (seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Time before next Wave"))
	float timeBetweenWaves = -1.f;

	// The wave composition itself
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "List of Hero(es) to spawn"))
	TArray<FHeroToSpawn> heroesToSpawn;
};

UCLASS()
class THISISMYDUNGEON_API AHeroSpawner : public AActor
{
	GENERATED_BODY()

	/*
		VARIABLES
	*/
protected:
	/*
		Wave system
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroSpawner")
	float timeBeforeStart = 0.f;

	// Waves can be sorted by any order you wish
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroSpawner")
	TArray<FWaveStruct> waveStructure;

	/*
		Timer management
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroSpawner")
	bool bPaused = false;

	TArray<FTimerHandle> everyTimer;
	// World Timer Manager
	FTimerManager* WTM = nullptr;

	/*
		Wave system
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroSpawner|Waves|Debug")
	TArray<FWaveStruct> waveStructureSorted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroSpawner|Waves|Debug")
	int currentWave = 0;

	bool bFirstWave = true;

	FTimerHandle endHandle;

	TArray<class AHero*> allHeroesSpawned;

	/*
		Waypoints and hero starting
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hero|Looting|Debug")
	class ADungeonManager* dManager = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroSpawner|AI|Debug")
	class AWaypoint* startWaypoint = nullptr;

	FVector startPoint;
	FRotator startRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroSpawner|AI|Debug")
	FTransform startTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroSpawner|AI")
	FVector extraHeightToSpawn;

	/*
		FUNCTIONS
	*/
public: // Constructor(s)
	AHeroSpawner();

protected:
	virtual void BeginPlay() override;

	/*
		Get Set
	*/
	virtual void GetDungeonManager();
	virtual void SetStartTransform();

	/*
		Waves
	*/
	virtual void SortWaveList();
	virtual void SpawnWave();
	virtual void SpawnAHero(FHeroToSpawn aHero);

	/*
		Checker
	*/
	virtual void IsGameOver();

public:
	/*
		Probably useless, but fun to implement
	*/
	UFUNCTION(BlueprintCallable, Category = "HeroSpawner|Functions")
	virtual void PauseSpawner();
	UFUNCTION(BlueprintCallable, Category = "HeroSpawner|Functions")
	virtual void UnpauseSpawner();

	/*
		BP Event
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "HeroSpawner|Functions")
	void WavesAreOver();
};
