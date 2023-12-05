#pragma once

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

#include "CoreMinimal.h"
#include "MyEntity.h"


#include "Demon.generated.h"

class UInputMappingContext;
class UInputAction;

/*
	/!\ this IS the PLAYER /!\
*/

UCLASS()
class THISISMYDUNGEON_API ADemon : public AMyEntity
{
	GENERATED_BODY()

public:
	ADemon();	

	//-_PLAYER_RELATED_VARS_--------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAcess = "true", ClampMin = "0"))
	float mana = 0.f; //Set to not null for mana by default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class ATrapPlacer> trapPlacer;

	//-_PLAYER_RELATED_FUNCTIONS_---------------------------------------------------------

	//UPROPERTY(VisibleAnywhere, Category = "Player")
	UFUNCTION(BlueprintCallable, Category = "Player")
	void ToEdit();

	//------------------------------------------------------------------------------------

protected:
	virtual void BeginPlay() override;

	

public:
	virtual void Tick(float deltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

private:
	virtual bool IsTileEmpty();

	virtual void CollideWithCollectible(/*Collectible collectible*/);

	virtual void PlaceTile();
};
