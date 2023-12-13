#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ScriptDelegates.h"

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
	float damage = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float speed = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float distanceToDespawn = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float lifespanOnSpawn = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileMovementComponent* movement;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* collider;

	void SetupMovement();
	void SetupCollider();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);
};
