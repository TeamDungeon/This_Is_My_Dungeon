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

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTreeComponent* behaviorTreeC;

	UPROPERTY(EditAnywhere, Category = "AI")
	UBlackboardComponent* blackBoardC;

	//UPROPERTY(EditAnywhere, Category = "AI")
	//UBehaviorTree* behaviorTree = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class AHero* possessedHero = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	FVector startWaypoint;

	virtual void OnPossess(APawn* inPawn) override;

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
};
