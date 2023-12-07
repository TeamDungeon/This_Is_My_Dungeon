#include "Projectile.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
    SetupMovement();
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void AProjectile::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
}

void AProjectile::SetupMovement()
{
    Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    Movement->UpdatedComponent = RootComponent;
    Movement->InitialSpeed = 1000;
    Movement->MaxSpeed = 1000;
    Movement->bRotationFollowsVelocity = true;
    Movement->bShouldBounce = true;
    Movement->ProjectileGravityScale = 0.f;
}