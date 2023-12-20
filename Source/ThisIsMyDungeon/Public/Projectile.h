#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class THISISMYDUNGEON_API AProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float damage = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float speed = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float distanceToDespawn = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float lifespanOnSpawn = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	class UProjectileMovementComponent* movement;
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* collider;

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

	void SetupMovement();
	void SetupCollider();

	UFUNCTION()
	void OnHit(class UPrimitiveComponent* hitComponent, AActor* otherActor, class UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
