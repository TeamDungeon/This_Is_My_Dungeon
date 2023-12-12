#include "Demon.h"

#include "TrapPlacer.h"
#include "Projectile.h"
#include "GameFramework/Controller.h"

#include "StaticVars.h"

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
	static_cast<ATrapPlacer*>(AStaticVars::static_trapPlacer)->OpenPlacer();
	//posses the cursor
	UGameplayStatics::GetPlayerCharacter(this, 0)->Controller->Possess(AStaticVars::static_trapPlacer);
	return;
}

void ADemon::SpawnFireball()
{
	GetWorld()->SpawnActor<AProjectile>(
		fireBall,
		GetActorLocation() + (GetActorForwardVector()*100),
		GetActorRotation()
	);
}

//------------------------------------------------------------------------------------

void ADemon::BeginPlay()
{
	Super::BeginPlay();
	//set the static_player var if no set (use to reswitch to the player)
	AStaticVars::SetPlayer(this);

	//spawn the trap placer aka the cusor.
	AStaticVars::SetTrapPlacer(GetWorld()->SpawnActor<ATrapPlacer>(
		trapPlacer,
		GetActorLocation(),
		{ 0,0,0 }
	));

}

void ADemon::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
