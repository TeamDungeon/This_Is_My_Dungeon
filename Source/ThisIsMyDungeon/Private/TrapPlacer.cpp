// Sue Me.


#include "TrapPlacer.h"

// Sets default values
ATrapPlacer::ATrapPlacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrapPlacer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapPlacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto& transf = GetTransform();
	const auto& xpos = transf.GetLocation().X;
	const auto& ypos = transf.GetLocation().Y;
	xPosTile = xpos / tileSize;
	yPosTile = ypos / tileSize;

	if (xpos > 0) xPosTile += 1;
	else xPosTile -= 1;

	if (ypos > 0) yPosTile += 1;
	else yPosTile -= 1;

	if (tryPlaceTile)
	{
		for (const auto& i : usedTiles)
		{
			if (i.Get<0>() == xPosTile && i.Get<1>() == yPosTile)
			{
				FString temp = "[ERROR] Tile already placed at: " + FString::FromInt(xPosTile) + ", " + FString::FromInt(yPosTile);
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, temp);
				tryPlaceTile = false;
				return;
			}
		}
		usedTiles.Add(TPair<int, int>(xPosTile, yPosTile));
		if (GEngine)
		{
			FString temp = "Tile Placed at: " + FString::FromInt(xPosTile) + ", " + FString::FromInt(yPosTile);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, temp);
		}

		tryPlaceTile = false;
	}
}

