// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

#include "PreviewTrap.generated.h"

UCLASS()
class THISISMYDUNGEON_API APreviewTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreviewTrap();

	UPROPERTY(EditAnywhere, Category = "PreviewTrap")
	UStaticMesh* mesh;

	UPROPERTY(EditAnywhere, Category = "PreviewTrap")
	UMaterial* validMaterial;

	UPROPERTY(EditAnywhere, Category = "PreviewTrap")
	UMaterial* unValidMaterial;

	UPROPERTY(EditAnywhere, Category = "PreviewTrap")
	UStaticMeshComponent* meshComponent;

	UPROPERTY(EditAnywhere, Category = "PreviewTrap")
	UBoxComponent* collider;

	void Valid();
	void UnValid();

	bool AsOverlaping();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupMesh();
	void SetupCollider();


};
