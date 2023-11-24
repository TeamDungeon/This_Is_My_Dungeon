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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float speed = 0.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float deltaTime) override;

	virtual bool IsAlive();
	virtual void DoAttack(AMyEntity target);
	virtual void GetDamaged(float value);
};