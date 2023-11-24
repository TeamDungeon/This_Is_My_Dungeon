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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Values")
	int upgradeLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	FVector3f currentDestination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
	bool isBarricadeInRange = false;

public:
	virtual void Tick(float deltaTime) override;

	virtual void Upgrade(int nbUgrades = 1);

	UFUNCTION(BlueprintNativeEvent, Category = "Functions")
	void DoSpecialAbility();

private:
	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void UpgradeOne();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void FindRoomPath();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void GetNextPoint();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual bool IsPlayerInRange();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	virtual void BarricadeInRange();
};
