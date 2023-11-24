#pragma once

#include "CoreMinimal.h"
#include "MyEntity.h"
#include "Demon.generated.h"

class UInputMappingContext;
class UInputAction;

/*
	/!\ this IS the player /!\
*/

UCLASS()
class THISISMYDUNGEON_API ADemon : public AMyEntity
{
	GENERATED_BODY()

public:
	ADemon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* cameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* camera;

	void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

protected:
	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player")
	float mana = 0.f;

public:
	void Tick(float deltaTime) override;

private:
	bool IsTileEmpty();

	void CollideWithCollectible(/*Collectible collectible*/);

	void PlaceTile();
};
