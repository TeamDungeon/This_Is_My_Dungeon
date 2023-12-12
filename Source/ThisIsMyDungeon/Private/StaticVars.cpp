#include "StaticVars.h"

ACharacter* AStaticVars::static_trapPlacer = nullptr;
ACharacter* AStaticVars::static_player = nullptr;


// Sets default values
AStaticVars::AStaticVars()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AStaticVars::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, "StaticVars");
}

void AStaticVars::SetPlayer(ACharacter* player)
{
	if (static_player == nullptr)
		static_player = player;
}

void AStaticVars::SetTrapPlacer(ACharacter* trapPlacer)
{
	if (static_trapPlacer == nullptr)
		static_trapPlacer = trapPlacer;
}