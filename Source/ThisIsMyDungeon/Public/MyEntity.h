#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEntity.generated.h"

UCLASS()
class THISISMYDUNGEON_API AMyEntity : public ACharacter
{
	GENERATED_BODY()

public:
	AMyEntity();

protected:
	float health = 0.f;
	float damage = 0.f;
	float speed = 0.f;

public:
	virtual bool IsAlive();
	virtual void DoAttack(AMyEntity target);
	virtual void GetDamaged(float value);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float deltaTime) override;
};