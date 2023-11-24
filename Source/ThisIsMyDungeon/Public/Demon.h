#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Demon.generated.h"

UCLASS()
class THISISMYDUNGEON_API ADemon : public AMyEntity
{
	GENERATED_BODY()

public:
	ADemon();

protected:
	void BeginPlay() override;

	float mana = 0.f;

public:
	void Tick(float DeltaTime) override;

private:
	bool IsTileEmpty();

	void CollideWithCollectible(/*Collectible collectible*/);

	void PlaceTile();
};
