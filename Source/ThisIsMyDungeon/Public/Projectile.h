#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class THISISMYDUNGEON_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

	FVector3f direction;
	float damage = 0.f;
	float speed = 0.f;

public:
	virtual void Tick(float deltaTime) override;
};
