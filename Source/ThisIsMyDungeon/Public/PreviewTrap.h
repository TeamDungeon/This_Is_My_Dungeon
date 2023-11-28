// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

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


	void Valid();
	void UnValid();


	/*void Init();
	UStaticMeshComponent* meshComponent;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
