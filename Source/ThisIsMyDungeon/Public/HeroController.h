#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HeroController.generated.h"

UCLASS()
class THISISMYDUNGEON_API AHeroController : public AAIController
{
	GENERATED_BODY()

public:
	AHeroController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float toleranceWaypoint = 50.f;

protected:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	//UBehaviorTree* behaviorTree = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	//class UBehaviorTreeComponent* behaviorTreeC;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	//UBlackboardComponent* blackBoardC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AHero* possessedHero = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TArray<FVector> waypointList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	int waypointID = 0;

private:
	FAIRequestID currentMovement;

	// FUNCTIONS
public:
	virtual void DemonDetected(class ADemon* demon);
	virtual void DemonLost();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* inPawn) override;
	virtual void OnMoveCompleted(FAIRequestID requestID, EPathFollowingResult::Type result) override;

private:
	virtual void GetWaypointList();
	virtual void StartMove();
};
