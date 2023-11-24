#include "MyEntity.h"

AMyEntity::AMyEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AMyEntity::IsAlive()
{
	return health > 0.f;
}

void AMyEntity::DoAttack(AMyEntity target)
{
	target.GetDamaged(damage);
}

void AMyEntity::GetDamaged(float value)
{
	health -= value;
}

void AMyEntity::BeginPlay()
{
	Super::BeginPlay();
}

void AMyEntity::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}