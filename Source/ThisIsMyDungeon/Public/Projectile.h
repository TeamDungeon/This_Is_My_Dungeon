#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"


#include "Projectile.generated.h"

UCLASS()
class THISISMYDUNGEON_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float damage = 0.f;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* Movement;

	void SetupMovement();
};
