#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HeroController.generated.h"

/*
	HeroController moves their assigned Hero where needed
	To a waypoint or to the demon (depends if currently attacking)
	It keeps track of where it is
*/

UCLASS()
class THISISMYDUNGEON_API AHeroController : public AAIController
{
	GENERATED_BODY()

	/*
		VARIABLES
	*/
protected:
	/*
		Movement
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroController")
	float toleranceWaypoint = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeroController")
	float toleranceEndMultiplier = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroController")
	class AWaypoint* currentWaypoint = nullptr;

	/*
		The Hero
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HeroController")
	class AHero* possessedHero = nullptr;

	/*
		Attack
	*/
	class ADemon* demonInRange = nullptr;

	/*
		FUNCTIONS
	*/
public: // Constructor(s)
	AHeroController();

protected:
	/*
		UE Functions Override
	*/
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnMoveCompleted(FAIRequestID requestID, EPathFollowingResult::Type result) override;

	/*
		Movement
	*/
	// Baby's first steps
	virtual void FirstMove();

public:
	/*
		Checker
	*/
	virtual bool IsDemonInSight(class ADemon* demon);

	/*
		Communication with possessed pawn
	*/
	virtual void DemonDetected(class ADemon* demon);
	virtual void DemonLost();
	virtual void SetStartWaypoint(AWaypoint* startWaypoint);
};
