#include "Demon.h"

#include "TrapPlacer.h"
#include "GameFramework/Controller.h"

ADemon::ADemon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADemon::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
}

//-_PLAYER_RELATED_FUNCTIONS_---------------------------------------------------------

void ADemon::ToEdit()
{
	static_cast<ATrapPlacer*>(static_trapPlacer)->OpenPlacer();
	//posses the cursor
	UGameplayStatics::GetPlayerCharacter(this, 0)->Controller->Possess(static_trapPlacer);
	return;
}

//------------------------------------------------------------------------------------

void ADemon::BeginPlay()
{
	Super::BeginPlay();

	//spawn the trap placer aka the cusor.
	static_trapPlacer = GetWorld()->SpawnActor<ATrapPlacer>(
		trapPlacer,
		GetActorLocation(),
		{ 0,0,0 }
	);

	//set the static_player var if no set (use to reswitch to the player)
	if (static_player == nullptr)
		ATrapPlacer::SetPlayer(this);
}

void ADemon::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

bool ADemon::IsTileEmpty()
{
	return false;
}

void ADemon::CollideWithCollectible()
{
}

void ADemon::PlaceTile()
{
	
}