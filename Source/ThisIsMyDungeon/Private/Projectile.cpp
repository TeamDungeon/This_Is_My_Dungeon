#include "Projectile.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::BeginPlay()
{
}

void AProjectile::Tick(float deltaTime)
{
}

void AProjectile::SetDirection(FVector3f source, FVector3f destination)
{
	direction = source - destination;
	if (!direction.Normalize())
	{
		/*error*/
	}
}