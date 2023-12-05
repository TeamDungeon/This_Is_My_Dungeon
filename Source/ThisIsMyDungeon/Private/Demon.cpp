#include "Demon.h"

#include "TrapPlacer.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

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
	auto* temp = GetWorld()->SpawnActor<ATrapPlacer>(
		trapPlacer,
		GetActorLocation(),
		{ 0,0,0 }
	);
	UGameplayStatics::GetPlayerCharacter(this, 0)->Controller->Possess(temp);
	return;
}

//------------------------------------------------------------------------------------

void ADemon::BeginPlay()
{
	Super::BeginPlay();
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