#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HeroController.generated.h"

/*
	HeroController moves their assigned Hero where needed
	(To a waypoint or to the demon)
	It keeps track of where it is
*/

UCLASS()
class THISISMYDUNGEON_API AHeroController : public AAIController
{
	GENERATED_BODY()

	/*
		VARIABLES
	*/
public:
	/*
		Movement
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CPP Values|AI")
	float toleranceWaypoint = 50.f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Values|AI")
	class AWaypoint* currentWaypoint;

	/*
		The Hero
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CPP Values|AI")
	class AHero* possessedHero = nullptr; // TODO delete ?

private:
	/*
		Attack
	*/
	FAIRequestID currentMovement;

	class ADemon* demonInRange = nullptr;

	/*
		FUNCTIONS
	*/
public: // Constructor(s)
	AHeroController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnMoveCompleted(FAIRequestID requestID, EPathFollowingResult::Type result) override;

	// Baby's first steps
	virtual void FirstMove();

public:
	virtual bool IsDemonInSight(class ADemon* demon);

	virtual void DemonDetected(class ADemon* demon);
	virtual void DemonLost();

	virtual void SetStartWaypoint(AWaypoint* startWaypoint);
};
