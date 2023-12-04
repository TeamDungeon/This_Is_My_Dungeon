#include "HeroController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Hero.h"
#include "DungeonManager.h"

#include <Kismet/GameplayStatics.h>
#include <Demon.h>
#include <NavigationSystem.h>

AHeroController::AHeroController()
{
	PrimaryActorTick.bCanEverTick = false;
	//behaviorTreeC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	//blackBoardC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board Component"));
}

void AHeroController::BeginPlay()
{
	Super::BeginPlay();

	GetStartWaypoint();

	//if (IsValid(behaviorTree))
	//{
	//	RunBehaviorTree(behaviorTree);
	//	behaviorTreeC->StartTree(*behaviorTree);
	//}
}

void AHeroController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	possessedHero = Cast<AHero, APawn>(inPawn);
	if (!possessedHero)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("AHeroController::OnPossess Hero cast failled with Pawn " + inPawn->GetName()));
		return;
	}
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
			TEXT("AHeroController::OnPossess Hero cast success with Pawn " + inPawn->GetName()));
}

void AHeroController::OnMoveCompleted(FAIRequestID requestID, EPathFollowingResult::Type result)
{
	if (result == EPathFollowingResult::Success)
	{
		if ((int32)waypointID + 1 < currentWaypoint.Num())
		{
			while (currentWaypoint[waypointID + 1] == currentWaypoint[waypointID]) waypointID++;
			// Move to waypoint, ..., no Stop on overlap, Use path finding, ..., No Strafing
			if (MoveToLocation(currentWaypoint[waypointID + 1]->GetActorLocation(), toleranceWaypoint, false, true, false, false)
				== EPathFollowingRequestResult::RequestSuccessful)
			{
				waypointID++;
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
						TEXT("Going to: " + currentWaypoint[waypointID]->GetActorLocation().ToString()));
			}
			else if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
					TEXT("AHeroController::OnMoveCompleted Move to request failled for " + GetName()));
		}
		else if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
				TEXT("AHeroController::OnMoveCompleted No waypoint next for " + GetName()));
	}
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			TEXT("AHeroController::OnMoveCompleted Previous path failled failled for " + GetName()));
}

void AHeroController::GetStartWaypoint()
{
	TArray<AActor*> dManager;
	if (UWorld* World = GetWorld())
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonManager::StaticClass(), dManager);
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("AHeroController::GetStartWaypoint Coudn't get World for " + GetName()));
		return;
	}

	if (dManager.Num() != 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("AHeroController::GetStartWaypoint Coudn't get THE DungeonManager for " + GetName()));
		return;
	}

	currentWaypoint = Cast<ADungeonManager>(dManager[0])->WaypointList;
	if (currentWaypoint.Num() < 1)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("AHeroController::GetStartWaypoint List is empty for " + GetName()));
		return;
	}

	FTimerHandle unusedHandle; // To give them time to reach ground
	GetWorldTimerManager().SetTimer(unusedHandle, this, &AHeroController::StartMove, 2.f, false);
}

void AHeroController::StartMove()
{
	// "Force" first MoveTo
	// Move to waypoint, ..., no Stop on overlap, Use path finding, ..., No Strafing
	MoveToLocation(currentWaypoint[waypointID++]->GetActorLocation(), toleranceWaypoint, false, true, false, false);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
			TEXT("Going to: " + currentWaypoint[waypointID]->GetActorLocation().ToString()));
}

void AHeroController::DemonDetected(ADemon* demon)
{
	currentMovement = GetCurrentMoveRequestID();
	PauseMove(currentMovement);
	// Move to demon, ..., Stop on overlap, Use path finding, No Strafing
	MoveToActor(demon, toleranceWaypoint, true, true, false);
}

void AHeroController::DemonLost()
{
	ResumeMove(currentMovement);
}