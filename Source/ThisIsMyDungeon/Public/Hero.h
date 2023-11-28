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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values | Upgrade", meta = (DisplayName = "Treasure Droped Increase On Upgrade"))
	float treasureUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values | Upgrade", meta = (DisplayName = "Damage Increase On Upgrade"))
	float damageUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values | Upgrade", meta = (DisplayName = "Health Increase On Upgrade"))
	float healthUpgrade = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values | Upgrade", meta = (DisplayName = "Speed Increase On Upgrade"))
	float speedUpgrade = 0.f;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values | Upgrade")
	int upgradeLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Values")
	bool isAtTheEnd = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Values")
	bool isBarricadeInRange = false;

public:
	virtual void Tick(float deltaTime) override;

	virtual void Upgrade(int nbUgrades = 1);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool GetHeroAtEnd();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void SetHeroAtEnd(bool value);

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void DoSpecialAbility();

private:
	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void UpgradeOne();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void FindRoomPath();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsPlayerInRange();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void BarricadeInRange();
};
