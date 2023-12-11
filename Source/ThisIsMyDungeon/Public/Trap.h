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

	int GetCost() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true", ClampMin = "1", ClampMax = "3"))
	int tileSize_X = 1;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true", ClampMin = "1", ClampMax = "3"))
	int tileSize_Y = 1;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	ATrap* upgradedTrap;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	int	cost = 0;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	float damage = 1.f;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	bool canDamageEnemy = true;

public:
	virtual void Tick(float deltaTime) override;

	virtual void Upgrade();
	virtual void Destroy();
};
