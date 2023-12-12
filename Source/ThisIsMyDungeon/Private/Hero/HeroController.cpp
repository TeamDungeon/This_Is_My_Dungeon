#include "Hero/HeroController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Hero/Hero.h"
#include "Demon.h"
#include "DungeonManager.h"
#include "Waypoint.h"

#include <Kismet/GameplayStatics.h>
#include <NavigationSystem.h>

AHeroController::AHeroController() { PrimaryActorTick.bCanEverTick = false; }

void AHeroController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle unusedHandle; // To give them time to reach ground
	GetWorldTimerManager().SetTimer(unusedHandle, this, &AHeroController::FirstMove, 1.f, false);
}

void AHeroController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	possessedHero = Cast<AHero, APawn>(inPawn);
	if (!possessedHero)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroController::OnPossess Hero cast failled with Pawn " + inPawn->GetName()));
		return;
	}
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Green,
			TEXT("AHeroController::OnPossess Hero cast success with Pawn " + inPawn->GetName()));
}

void AHeroController::OnMoveCompleted(FAIRequestID requestID, EPathFollowingResult::Type result)
{
	if (demonInRange)
	{/*
		FAIMoveRequest moveRequest(demonInRange);
		FPathFindingQuery pathQuery;
		if (!BuildPathfindingQuery(moveRequest, pathQuery))
			return;

		FNavPathSharedPtr pathFound;
		FindPathForMoveRequest(moveRequest, pathQuery, pathFound);

		if (RequestMove(moveRequest, pathFound) != FAIRequestID::InvalidRequest)
			MoveToActor(demonInRange, toleranceWaypoint, true, true, false);*/
		return;
	}

	if (result == EPathFollowingResult::Success)
	{
		auto& nextPoints = currentWaypoint->NextWaypoint;
		if (nextPoints.Num() != 0)
		{
			int nextID = 0;
			if (nextPoints.Num() != 1)
				nextID = FMath::RandRange(0, nextPoints.Num() - 1);

			// Move to waypoint, ..., no Stop on overlap, Use path finding, ..., No Strafing
			if (MoveToLocation(nextPoints[nextID]->GetActorLocation(), toleranceWaypoint, false, true, false, false)
				== EPathFollowingRequestResult::RequestSuccessful)
			{
				currentWaypoint = nextPoints[nextID];
				//if (GEngine)
				//	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
				//		TEXT("Going to: " + currentWaypoint->GetActorLocation().ToString()));
			}
			else if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
					TEXT("AHeroController::OnMoveCompleted Move to request failled for " + GetName()));
		}
		else if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
				TEXT("AHeroController::OnMoveCompleted No waypointNext for " + GetName()));
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroController::OnMoveCompleted Previous path failled failled for " + GetName()));
		//possessedHero->Death();
	}
}

void AHeroController::FirstMove()
{
	// "Force" first MoveTo
	// Move to waypoint, ..., no Stop on overlap, Use path finding, ..., No Strafing
	MoveToLocation(currentWaypoint->GetActorLocation(), toleranceWaypoint, false, true, false, false);
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
	//		TEXT("Going to: " + currentWaypoint->GetActorLocation().ToString()));
}

bool AHeroController::IsDemonInSight(ADemon* demon)
{
	return LineOfSightTo(demon);
}

void AHeroController::DemonDetected(ADemon* demon)
{
	//currentMovement = GetCurrentMoveRequestID();
	//StopMovement();
	// Move to demon, ..., Stop on overlap, Use path finding, No Strafing
	MoveToActor(demon, toleranceWaypoint, true, true, false);
	demonInRange = demon;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
			TEXT("AHeroController::DemonDetected Called for " + GetName()));
}

void AHeroController::DemonLost()
{
	//ResumeMove(currentMovement);
	MoveToLocation(currentWaypoint->GetActorLocation(), toleranceWaypoint, false, true, false, false);
	demonInRange = nullptr;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
			TEXT("AHeroController::DemonLost Called for " + GetName()));
}

void AHeroController::SetStartWaypoint(AWaypoint* startWaypoint)
{
	currentWaypoint = startWaypoint;
}