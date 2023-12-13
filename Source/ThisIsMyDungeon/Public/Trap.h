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
	FUintVector2 GetTileSize() const;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	FUintVector2 tileSize = { 1,1 };
	
	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	ATrap* upgradedTrap;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	int	cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	float damage = 1.f;

	UPROPERTY(EditAnywhere, Category = "Trap", meta = (AllowPrivateAcess = "true"))
	bool canDamageEnemy = true;

	UPROPERTY(EditAnywhere, Category = "Trap")
	UTexture2D* trapImage = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Trap")
	UTexture2D* GetTrapImage();//Used for the ui

public:
	virtual void Tick(float deltaTime) override;

	virtual void Upgrade();
	virtual void Destroy();
};
