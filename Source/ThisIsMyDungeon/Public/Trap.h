#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class THISISMYDUNGEON_API ATrap : public AActor
{
	GENERATED_BODY()

public:
	ATrap();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	int tileSize_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	int tileSize_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	AActor* upgradedTrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	int	cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	bool canDamageEnemy;

public:
	virtual void Tick(float deltaTime) override;

	virtual void Upgrade();
	virtual void Destroy();
};
