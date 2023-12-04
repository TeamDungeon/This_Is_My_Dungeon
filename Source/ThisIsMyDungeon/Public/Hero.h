#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Hero.generated.h"

/*
	/!\ this IS the ENEMY /!\
*/

UCLASS()
class THISISMYDUNGEON_API AHero : public AMyEntity
{
	GENERATED_BODY()

public:
	AHero();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float treasureDrop = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Treasure Droped Increase On Upgrade"))
	float treasureUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Damage Increase On Upgrade"))
	float damageUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Health Increase On Upgrade"))
	float healthUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Speed Increase On Upgrade"))
	float speedUpgrade = 0.f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values|Upgrade", meta = (DisplayName = "Current Upgrade Level"))
	int upgradeLevel = 0;

private:
	// If demon in range is nullptr = no demon on range
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Values", meta = (AllowPrivateAccess = "true"))
	class ADemon* demonInRange = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values", meta = (AllowPrivateAccess = "true"))
	bool isAttacking = false;

	UCharacterMovementComponent* moveComponent = nullptr;

	// FUNCTIONS
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void DemonDetected();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void DemonLost();

public:
	virtual void Upgrade(int nbUgrades = 1);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsAttacking();
};
