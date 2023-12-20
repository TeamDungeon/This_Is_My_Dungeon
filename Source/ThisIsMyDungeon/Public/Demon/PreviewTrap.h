#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	class UStaticMeshComponent* meshComponent;

	UPROPERTY(EditAnywhere, Category = "PreviewTrap")
	class UBoxComponent* collider;

	void Valid();
	void UnValid();

	bool AsOverlaping();

protected:
	virtual void BeginPlay() override;

	void SetupMesh();
	void SetupCollider();
};
