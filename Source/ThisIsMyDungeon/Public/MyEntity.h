#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEntity.generated.h"

UCLASS()
class THISISMYDUNGEON_API AMyEntity : public ACharacter
{
	GENERATED_BODY()

	/*
		VARIABLES
	*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float speed = 0.f;

	/*
		FUNCTIONS
	*/
public: // Constructor(s)
	AMyEntity();

public:
	virtual void Death();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsAlive();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void DoAttack(AMyEntity* target);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void GetDamaged(float value);
};