#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Hero.generated.h"

/*
	Hero is a generic class that get declined through blueprints
	The upgrade values are static, and the stats increase linearly
	Visuals can change when ganing an upgrade lvl, max upgrade lvl exists
	Can attack the player, Blinks when hurt

	Look at HeroController class to learn more on Hero structure
*/

USTRUCT(BlueprintType)
struct FUpgradeWeapon
{
	GENERATED_BODY()

public:
	// Index is the weapon order in the Animation Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Weapon x Is On Display"))
	TArray<bool> bOnDisplay;
};

/*
	/!\ this IS the ENEMY /!\
*/

UCLASS()
class THISISMYDUNGEON_API AHero : public AMyEntity
{
	GENERATED_BODY()

	/*
		VARIABLES
	*/
protected:
	/*
		Components
	*/
	UCharacterMovementComponent* moveComponent = nullptr;

	class AHeroController* controller = nullptr;

	// World Timer Manager ptr
	FTimerManager* WTM = nullptr;

	/*
		OnDeath
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|OnDeath", meta = (DisplayName = "Treasure Droped"))
	float treasureDrop = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|OnDeath", meta = (DisplayName = "Mana Droped"))
	float manaDrop = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|OnDeath")
	float lifeSpanOnDeath = 5.f;

	/*
		Upgrade stats
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	float speedMultiplier = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Upgrade", meta = (DisplayName = "Treasure Droped Increase"))
	float treasureUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Upgrade", meta = (DisplayName = "Damage Increase"))
	float damageUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Upgrade", meta = (DisplayName = "Health Increase"))
	float healthUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Upgrade", meta = (DisplayName = "Speed Increase"))
	float speedUpgrade = 0.f;

	/*
		More Upgrade (Weapon specific)
	*/
	// Index is the upgrade level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Upgrade")
	TArray<FUpgradeWeapon> weaponOnUpgrade; // for Weapon Scales in Animation Blueprint

	// Cannot upgrade beyond weaponOnUpgrade size
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hero|Upgrade", meta = (DisplayName = "Current Upgrade Level"))
	int upgradeLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Upgrade")
	int nbWeaponsMax = 0; // for Weapon Scale

	/*
		Even more Upgrade (communication with Animation Blueprint)
	*/
	// Used for Animation Blueprint
	UPROPERTY(BlueprintReadWrite, Category = "Hero|Upgrade|Debug")
	bool bUpgradeDone = false; // for Animation Blueprint to know to change its current values

	// Used for Animation Blueprint
	UPROPERTY(BlueprintReadOnly, Category = "Hero|Upgrade|Debug")
	TArray<FVector> weaponScale; // for Weapon Scales in the Animation Blueprint to change its values

	/*
		Looting
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Looting", meta = (DisplayName = "Loot Treasure every x sec"))
	float lootTimer = 5.f;

	FTimerHandle lootHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hero|Looting|Debug")
	class ADungeonManager* dManager = nullptr;

	/*
		Attack
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Attack", meta = (DisplayName = "Attack Moment (sync with AB)"))
	float timerAttackMoment = .4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Attack", meta = (DisplayName = "Attack Sequence (sync with AB)"))
	UAnimSequence* attackSequence = nullptr;

	// If demon in range is nullptr (or None) -> no demon to attack is in range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hero|Attack")
	class ADemon* demonInRange = nullptr;

	FTimerHandle attackHandle;

	/*
		Damaged
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Damaged")
	float blinkingSpeed = .2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Damaged")
	int blinkingAmount = 5;

	FTimerHandle damageAnimHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hero|Damaged|Debug")
	int blinkingCpt = 0;

	/*
		FUNCTIONS
	*/
public: // Constructor(s)
	AHero();

protected:
	virtual void BeginPlay() override;

	virtual void GetDungeonManager();

	UFUNCTION(BlueprintCallable, Category = "Hero|Functions")
	virtual void DemonDetected(class ADemon* demon);

	UFUNCTION(BlueprintCallable, Category = "Hero|Functions")
	virtual void DemonLost();

	virtual void DamageBlinking();

	virtual void SetWeaponSize();

	virtual void AttackDemon();

	virtual void LootTreasure();

public:
	UFUNCTION(BlueprintCallable, Category = "Hero|Functions")
	virtual void Upgrade(int nbUpgrades = 1);

	UFUNCTION(BlueprintCallable, Category = "Hero|Functions")
	virtual bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Hero|Functions")
	virtual bool IsAttacking();

	// Already blueprint callable
	virtual void GetDamaged(float value) override;

	// Used by HeroSpawner
	virtual void SetStartWaypoint(class AWaypoint* startWaypoint);

	UFUNCTION(BlueprintCallable, Category = "Hero|Functions")
	virtual void Death();

	virtual void StartLooting();

	UFUNCTION(BlueprintNativeEvent, Category = "Hero|Functions")
	void OnDeath();
};
