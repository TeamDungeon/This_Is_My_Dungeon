#pragma once

#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

#include "CoreMinimal.h"
#include "MyEntity.h"


#include "Demon.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class THISISMYDUNGEON_API ADemon : public AMyEntity
{
	GENERATED_BODY()

public:
	ADemon();	

	//-_PLAYER_RELATED_VARS_--------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", meta = (ClampMin = "0"))
	float mana = 0.f; //Set to not null for mana by default

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<class ATrapPlacer> trapPlacer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	TSubclassOf<class AProjectile> fireBall;

	//-_PLAYER_RELATED_FUNCTIONS_---------------------------------------------------------

	UFUNCTION(BlueprintCallable, Category = "Player")
	void ToEdit();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SpawnFireball();

	//------------------------------------------------------------------------------------

	static ADemon* GetInstance();

protected:
	virtual void BeginPlay() override;

	static ADemon* instance;

};
