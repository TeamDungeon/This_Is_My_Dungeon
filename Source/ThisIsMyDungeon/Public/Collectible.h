#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

enum CollectibleType
{
	COIN,
	MANA,
	UPGRADE
};

UCLASS()
class THISISMYDUNGEON_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectible();

	float value = 0.f;
	CollectibleType type;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;

};
