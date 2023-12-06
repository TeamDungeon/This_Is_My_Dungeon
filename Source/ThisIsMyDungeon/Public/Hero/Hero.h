#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Hero.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeWeapon
{
	GENERATED_BODY()

public:
	// Index is the weapon order in the Animation Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Weapon x Is On Display"))
	TArray<bool> bIsOnDisplay;
};

/*
	/!\ this IS the ENEMY /!\
*/

UCLASS()
class THISISMYDUNGEON_API AHero : public AMyEntity
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|OnDeath", meta = (DisplayName = "Treasure Droped"))
	float treasureDrop = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|OnDeath")
	float lifeSpanOnDeath = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|OnDeath")
	float blinkingSpeed = .5f;

	// Note: Upgrades have a linear increase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Treasure Droped Increase"))
	float treasureUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Damage Increase"))
	float damageUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Health Increase"))
	float healthUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade", meta = (DisplayName = "Speed Increase"))
	float speedUpgrade = 0.f;

protected:
	// Index is the upgrade level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values|Upgrade")
	TArray<FUpgradeWeapon> weaponOnUpgrade; // for Weapon Scales in Animation Blueprint

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	int nbWeaponsMax = 0; // for Weapon Scale

private:
	// If demon in range is nullptr (or None) -> no demon to attack is in range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values|Debug", meta = (AllowPrivateAccess = "true"))
	class ADemon* demonInRange = nullptr;

	// Cannot upgrade beyond weaponOnUpgrade size
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values|Upgrade", meta = (DisplayName = "Current Upgrade Level", AllowPrivateAccess = "true"))
	int upgradeLevel = 0;

	// Used for Animation Blueprint
	UPROPERTY(BlueprintReadWrite, Category = "Values|Debug", meta = (AllowPrivateAccess = "true"))
	bool bUpgradeDone = false; // for Animation Blueprint to know to change its current values

	// Used for Animation Blueprint
	UPROPERTY(BlueprintReadOnly, Category = "Values|Debug", meta = (AllowPrivateAccess = "true"))
	TArray<FVector> weaponScale; // for Weapon Scales in the Animation Blueprint to change its values

	UCharacterMovementComponent* moveComponent = nullptr;

	// FUNCTIONS
public:
	AHero();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void DemonDetected(class ADemon* demon);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void DemonLost();

private:
	virtual void DeadBlinking();
	virtual void SetWeaponSize();

public:
	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void Upgrade(int nbUpgrades = 1);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsAttacking();

	virtual void GetDamaged(float value) override;

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void Death();
};
