#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UENUM(BlueprintType)
enum class ColType
{
	COL_NONE     UMETA(DisplayName = "NONE"),
	COL_COIN     UMETA(DisplayName = "Coin"),
	COL_MANA     UMETA(DisplayName = "Mana"),
	COL_UPGRADE  UMETA(DisplayName = "Upgrade"),
};

UCLASS()
class THISISMYDUNGEON_API ACollectible : public AActor
{
	GENERATED_BODY()

public:
	ACollectible();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float value = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	ColType type = ColType::COL_NONE;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float deltaTime) override;
};
