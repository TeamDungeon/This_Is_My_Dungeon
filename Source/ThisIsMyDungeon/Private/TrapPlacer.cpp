// Sue Me.

#include "TrapPlacer.h"

// Sets default values
ATrapPlacer::ATrapPlacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->SetActorTickEnabled(false);
}

void ATrapPlacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto& loc = GetActorLocation() / tileSize;
	posTile = { static_cast<int>(loc.X), static_cast<int>(loc.Y) };

	//-_Use_to_remove_tile_0_-----------
	if (loc.X >= 0)posTile.X += 1;
	else posTile.X -= 1;
	if (loc.Y >= 0)posTile.Y += 1;
	else posTile.Y -= 1;
	//----------------------------------

	if (pPreTilePos != posTile)
	{
		if (IsTileEmpty())
		{
			previewTile->Valid();
			isEmpty = true;
		}
		else
		{
			previewTile->UnValid();
		}
		//-_Preview_managment_-------
		//Seems a bit heavy may need chang in close future, need test on console
		previewTile->SetActorLocation({ static_cast<double>((posTile.X > 0 ? posTile.X - 1 : posTile.X) * tileSize), static_cast<double>((posTile.Y > 0 ? posTile.Y - 1 : posTile.Y) * tileSize), 0 });
		//---------------------------
		pPreTilePos = posTile;
	}

	if (placeTile && isEmpty)
	{
		PlaceTrap();
		isEmpty = false;
	}
}

bool ATrapPlacer::IsTileEmpty()
{
	for (const auto& i : usedTiles)
	{
		if (i.X == posTile.X && i.Y == posTile.Y)
		{
			if (GEngine)
			{
				FString temp = "[ERROR] Tile already placed at: " + FString::FromInt(posTile.X) + ", " + FString::FromInt(posTile.Y);
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, temp);
			}
			return false;
		}
	}
	return true;
}



void ATrapPlacer::OpenPlacer()
{
	previewTile = GetWorld()->SpawnActor<APreviewTrap>(
		previewTileActor,
		{ 0,0,GetActorLocation().Z },
		{ 0,0,0 }
	);
	this->SetActorTickEnabled(true);
}
void ATrapPlacer::ClosePlacer()
{
	previewTile->Destroy();
	previewTile = nullptr;
	this->SetActorTickEnabled(false);
}

void ATrapPlacer::PlaceTrap()
{
	if (GEngine)
	{
		FString temp = "Tile Placed at: " + FString::FromInt(posTile.X) + ", " + FString::FromInt(posTile.Y);
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, temp);
	}
	usedTiles.Add({ posTile.X, posTile.Y });

	GetWorld()->SpawnActor<ATrap>(
		trapToPlace,
		previewTile->GetActorLocation(),
		{ 0,0,0 }
	);
	//TODO place an actor trap in the world.

	ClosePlacer();// TODO Remove when adding to player
}

// Called when the game starts or when spawned
void ATrapPlacer::BeginPlay()
{
	Super::BeginPlay();
	OpenPlacer();// TODO Remove when adding to player
}