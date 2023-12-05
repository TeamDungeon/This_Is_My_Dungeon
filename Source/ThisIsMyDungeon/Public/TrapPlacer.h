// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "PreviewTrap.h"
#include "Trap.h"

#include "TrapPlacer.generated.h"

UCLASS()
class THISISMYDUNGEON_API ATrapPlacer : public ACharacter
{
	GENERATED_BODY()
	
public:	
	ATrapPlacer();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	FIntVector2 posTile = { 0,0 };

	UPROPERTY(EditAnywhere, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true", ClampMin = "1"))
	int tileSize = 16;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true"))
	bool placeTile = false;
	
	UPROPERTY(EditAnywhere, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true"))
	TSubclassOf<APreviewTrap> previewTileActor;

	UPROPERTY(EditAnywhere, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true"))
	TSubclassOf<ATrap> trapToPlace;

	UPROPERTY(EditAnywhere, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true"))
	float floorCoord = 0;

	TArray<FIntVector2> usedTiles;


	bool isEmpty = false;
	void PlaceTrap();

	void OpenPlacer();
	void ClosePlacer();

protected:
	bool IsTileEmpty();

	UPROPERTY(VisibleAnywhere)
	FIntVector2 pPreTilePos = { 0,0 };

	APreviewTrap* previewTile;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
