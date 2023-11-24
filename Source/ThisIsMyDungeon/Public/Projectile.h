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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	FVector3f direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float speed = 0.f;

public:
	virtual void Tick(float deltaTime) override;

	virtual void SetDirection(FVector3f source, FVector3f destination);
};
