#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"
#include "Decorator.generated.h"

UCLASS()
class THISISMYDUNGEON_API ADecorator : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP|Ints")
	int AmountToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP|Ints")
	int IDMeshToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP|Floats")
	float SpawnRNG;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP|Lists")
	TArray<UStaticMesh*> MeshesToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP|Vector")
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Miscs")
	UBoxComponent* BoxCollider;

public:
	ADecorator();

protected:
	virtual void BeginPlay() override;
};
