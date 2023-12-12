#include "Projectile.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    SetupCollider();
    SetupMovement();
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    if (collider)
    {
        collider->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
    }

    SetLifeSpan(10);
}

void AProjectile::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
}

void AProjectile::SetupMovement()
{
    movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    movement->UpdatedComponent = RootComponent;
    movement->InitialSpeed = 1000;
    movement->MaxSpeed = 1000;
    movement->bRotationFollowsVelocity = true;
    movement->ProjectileGravityScale = 0.f;
}

void AProjectile::SetupCollider()
{
    collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
    collider->InitSphereRadius(1.f);

    collider->SetGenerateOverlapEvents(true);
    collider->SetCollisionProfileName(FName("Pawn"));
    collider->CanCharacterStepUpOn = ECB_No;

    collider->SetNotifyRigidBodyCollision(true);

    //collider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlap);
    RootComponent = collider;

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Destroy();
}