#include "MyEntity.h"

AMyEntity::AMyEntity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyEntity::Death() { Destroy(); }

bool AMyEntity::IsAlive() { return health > 0.f; }

void AMyEntity::DoAttack(AMyEntity* target) { target->GetDamaged(damage); }

void AMyEntity::GetDamaged(float value)
{
	health -= value;

	if (!IsAlive())
		Death();
}