#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Hero.generated.h"

/*
	/!\ this IS NOT the player /!\
*/

UCLASS()
class THISISMYDUNGEON_API AHero : public AMyEntity
{
	GENERATED_BODY()

public:
	AHero();

protected:
	void BeginPlay() override;

public:
	void Tick(float deltaTime) override;
};
