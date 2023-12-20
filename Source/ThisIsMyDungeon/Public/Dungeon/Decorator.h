#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Decorator.generated.h"

UCLASS()
class THISISMYDUNGEON_API ADecorator : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	int amountToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	int IDMeshToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	float spawnRNG;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	TArray<class UStaticMesh*> meshesToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP")
	FVector scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	class UBoxComponent* boxCollider;

public:
	ADecorator();

protected:
	virtual void BeginPlay() override;
};
