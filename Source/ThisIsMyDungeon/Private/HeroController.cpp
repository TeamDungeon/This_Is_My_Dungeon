#include "HeroController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Hero.h"

AHeroController::AHeroController()
{
	behaviorTreeC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	blackBoardC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board Component"));
}

void AHeroController::BeginPlay()
{
	if (startWaypoint.IsZero())
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Starting Waypoint set on HeroController /!\\"));
}

void AHeroController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	possessedHero = Cast<AHero, APawn>(inPawn);
	if (!possessedHero)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hero cast failled AHeroController::OnPossess() with " + inPawn->GetName()));
		return;
	}

	// Move to waypoint, ..., Stop on overlap, Use path finding, ..., No Strafing
	MoveToLocation(possessedHero->GetWaypoint(), -1.f, true, true, false, false);
}

void AHeroController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	MoveToLocation(possessedHero->GetWaypoint(), -1.f, true, true, false, false);
}