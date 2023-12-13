#include "Demon.h"

#include "TrapPlacer.h"
#include "Projectile.h"

#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

ADemon* ADemon::instance = nullptr;

ADemon::ADemon()
{
	PrimaryActorTick.bCanEverTick = true;
}

//-_PLAYER_RELATED_FUNCTIONS_---------------------------------------------------------

void ADemon::ToEdit()
{
	ATrapPlacer::GetInstance()->OpenPlacer();
	//posses the cursor
	UGameplayStatics::GetPlayerCharacter(this, 0)->Controller->Possess(ATrapPlacer::GetInstance());
	return;
}

void ADemon::SpawnFireball()
{
	GetWorld()->SpawnActor<AProjectile>(
		fireBall,
		GetActorLocation() + (GetActorForwardVector() * 100),
		GetActorRotation()
	);
}

//------------------------------------------------------------------------------------

void ADemon::BeginPlay()
{
	Super::BeginPlay();
	//set the static_player var if no set (use to reswitch to the player)
	instance = this;

	//spawn the trap placer aka the cusor.
	GetWorld()->SpawnActor<ATrapPlacer>(
		trapPlacer,
		GetActorLocation(),
		{ 0,0,0 }
	);

	//set the player speed
	GetCharacterMovement()->MaxWalkSpeed = speed * 100.f;
}

ADemon* ADemon::GetInstance()
{
	return instance;
}