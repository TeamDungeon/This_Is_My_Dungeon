#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Hero.generated.h"

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

	void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
};
