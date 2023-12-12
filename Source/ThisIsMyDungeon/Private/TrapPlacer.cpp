// Sue Me.

#include "TrapPlacer.h"

#include "Demon.h"

#include "StaticVars.h"

// Sets default values
ATrapPlacer::ATrapPlacer()
{
	PrimaryActorTick.bCanEverTick = true;
	this->SetActorTickEnabled(false); // disable tick by default
}

void ATrapPlacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Find the tile position
	const auto& loc = GetActorLocation() / tileSize;
	posTile = { static_cast<int>(loc.X), static_cast<int>(loc.Y) };

	//Use to remove tile 0
	if (loc.X >= 0)posTile.X += 1;
	else posTile.X -= 1;
	if (loc.Y >= 0)posTile.Y += 1;
	else posTile.Y -= 1;

	if (pPreTilePos != posTile)
	{
		//-_Preview_managment_-------
		//Seems a bit heavy may need chang in close future, need test on console
		previewTile->SetActorLocation({ static_cast<double>((posTile.X > 0 ? posTile.X : posTile.X + 1) * tileSize),
										static_cast<double>((posTile.Y > 0 ? posTile.Y : posTile.Y + 1) * tileSize),
										floorCoord });
		//---------------------------

		if (IsTileEmpty() && static_cast<ADemon*>(AStaticVars::static_player)->mana >= trapToPlace.GetDefaultObject()->GetCost() && !previewTile->AsOverlaping())
		{
			previewTile->Valid(); //Set the green color
			isEmpty = true;
		}
		else
		{
			previewTile->UnValid(); // Set the red color
			isEmpty = false; // need to be set to false
		}
		
		pPreTilePos = posTile;
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
	previewTile->SetActorHiddenInGame(false);//Enable the preview
	SetActorLocation(AStaticVars::static_player->GetActorLocation());
	this->SetActorTickEnabled(true);
}
void ATrapPlacer::ClosePlacer()
{
	//previewTile->SetHidden(true);//Disable the preview
	previewTile->SetActorHiddenInGame(true);
	this->SetActorTickEnabled(false);
}

void ATrapPlacer::PlaceTrap()
{
	if (isEmpty)
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

		//remove money
		static_cast<ADemon*>(AStaticVars::static_player)->mana -= trapToPlace.GetDefaultObject()->GetCost();
		
		isEmpty = false;
		previewTile->UnValid();
	}
}

// Called when the game starts or when spawned
void ATrapPlacer::BeginPlay()
{
	Super::BeginPlay();

	//spawn the preview tile (the square cursor)
	previewTile = GetWorld()->SpawnActor<APreviewTrap>(
		previewTileActor,
		GetActorLocation(),
		{ 0,0,0 }
	);

	//Used for the trap size could be used in the future
	//FUintVector2 temp = trapToPlace.GetDefaultObject()->GetTileSize();
	//previewTile->SetActorScale3D({ static_cast<double>(temp.X), static_cast<double>(temp.Y),1. });

	previewTile->SetActorHiddenInGame(true);//Disable the preview
}

void ATrapPlacer::ToPlayer()
{
	ClosePlacer();
	UGameplayStatics::GetPlayerCharacter(this, 0)->Controller->Possess(AStaticVars::static_player);
}

ACharacter* ATrapPlacer::GetStaticPlayer()
{
	return AStaticVars::static_player;
}