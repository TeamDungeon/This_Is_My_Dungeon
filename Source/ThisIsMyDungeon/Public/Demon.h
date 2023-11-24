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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* cameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* camera;

	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	float mana = 0.f;

public:
	virtual void Tick(float deltaTime) override;

private:
	virtual bool IsTileEmpty();

	virtual void CollideWithCollectible(/*Collectible collectible*/);

	virtual void PlaceTile();
};
