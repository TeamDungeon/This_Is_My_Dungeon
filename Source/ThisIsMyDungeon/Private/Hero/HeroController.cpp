#include "Hero/HeroController.h"

#include "Hero/Hero.h"
#include "Demon/Demon.h"

#include "Dungeon/DungeonManager.h"
#include "Dungeon/Waypoint.h"

#include <Kismet/GameplayStatics.h>
#include <Navigation/CrowdFollowingComponent.h>

AHeroController::AHeroController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHeroController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle firstMoveHandle; // To give them time to reach ground
	GetWorldTimerManager().SetTimer(firstMoveHandle, this, &AHeroController::FirstMove, 1.f, false);
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
	if (demonInRange || !possessedHero->IsAlive())
		return;

	if (result == EPathFollowingResult::Success)
	{
		auto& nextPoints = currentWaypoint->nextWaypoint;
		if (nextPoints.Num() != 0)
		{
			int nextID = 0;
			if (nextPoints.Num() != 1)
				nextID = FMath::RandRange(0, nextPoints.Num() - 1);

			if (!nextPoints[nextID])
			{
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
						TEXT("AHeroController::OnMoveCompleted nextPoints[nextID] doesn't exist for " + GetName()));
				return;
			}

			if (nextPoints[nextID]->nextWaypoint.Num() == 0)
				// If next Waypoint is the end of the line
				// Hero will be at treasure room
				// Set tolerance high to avoid overcrowding blocking heroes
				toleranceWaypoint *= toleranceEndMultiplier;

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
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
					TEXT("AHeroController::OnMoveCompleted No waypointNext for " + GetName()));

			// If there is no more waypoint Hero should be in treasure room
			possessedHero->StartLooting();
		}
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red,
				TEXT("AHeroController::OnMoveCompleted Previous path failled failled for " + GetName()));
		//possessedHero->Death(); // Might be a needed, what we call in French, "cache-misère"
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
	// Move to demon, ..., Stop on overlap, Use path finding, No Strafing
	MoveToActor(demon, toleranceWaypoint, true, true, false);
	demonInRange = demon;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue,
			TEXT("AHeroController::DemonDetected Called for " + GetName()));
}

void AHeroController::DemonLost()
{
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