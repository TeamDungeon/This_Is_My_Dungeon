// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapPlacer.generated.h"

UCLASS()
class THISISMYDUNGEON_API ATrapPlacer : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	int xPosTile = 0;
	UPROPERTY(VisibleAnywhere)
	int yPosTile = 0;

	UPROPERTY(EditAnywhere, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true", ClampMin = "1"))
	int tileSize = 16;

	UPROPERTY(EditAnywhere, Category = "TrapPlacer", meta = (AllowPrivateAcess = "true"))
	bool tryPlaceTile = false;


	
	TArray<TPair<int, int>> usedTiles;
	//std::vector< std::tuple<int, int, bool> > usedTile;

	// Sets default values for this actor's properties
	ATrapPlacer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
