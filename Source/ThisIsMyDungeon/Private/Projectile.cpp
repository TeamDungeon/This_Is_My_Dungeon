#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ScriptDelegates.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

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

	SetLifeSpan(lifespanOnSpawn);
}

void AProjectile::SetupMovement()
{
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	movement->UpdatedComponent = RootComponent;
	movement->InitialSpeed = speed;
	movement->MaxSpeed = speed;
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

void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	Destroy();
}