#pragma once

#include <Hero.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroSpawner.generated.h"

UCLASS()
class THISISMYDUNGEON_API AHeroSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AHeroSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float timeBeforeStart = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float timeRestPeriod = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values")
	bool isPaused = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Values")
	TArray<TSubclassOf<AHero>> heroesToSpawn;

	// FUNCTIONS
public:
	virtual void SpawnWave(int waveID);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
};
