#include "HeroController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Hero.h"
#include "DungeonManager.h"
#include <Kismet/GameplayStatics.h>

AHeroController::AHeroController()
{
	behaviorTreeC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	blackBoardC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board Component"));
}

void AHeroController::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle unusedHandle;
	GetWorldTimerManager().SetTimer(
		unusedHandle, this, &AHeroController::GetWaypointList, 2.f, false);

	if (IsValid(behaviorTree))
	{
		RunBehaviorTree(behaviorTree);
		behaviorTreeC->StartTree(*behaviorTree);
	}
}

void AHeroController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	possessedHero = Cast<AHero, APawn>(inPawn);
	if (!possessedHero)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("Hero cast failled AHeroController::OnPossess() with " + inPawn->GetName()));
		return;
	}
}

void AHeroController::OnMoveCompleted(FAIRequestID requestID, EPathFollowingResult::Type result)
{
	if (result == EPathFollowingResult::Success)
	{
		if ((int32)waypointID + 1 < waypointList.Num())
		{
			// Move to waypoint, ..., no Stop on overlap, Use path finding, ..., No Strafing
			if (MoveToLocation(waypointList[waypointID + 1], -1.f, false, true, false, false)
				== EPathFollowingRequestResult::RequestSuccessful)
				waypointID++;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
					TEXT("Going to: " + waypointList[waypointID].ToString()));
		}
		else if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT("OnMoveCompleted: No waypoint next"));
	}
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			TEXT("OnMoveCompleted failled"));
}

void AHeroController::GetWaypointList()
{
	TArray<AActor*> dManager;
	if (UWorld* World = GetWorld())
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonManager::StaticClass(), dManager);
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AHeroController::GetWaypointList() ERROR"));
		return;
	}

	waypointList = Cast<ADungeonManager>(dManager[0])->WaypointList;
	// Move to waypoint, ..., no Stop on overlap, Use path finding, ..., No Strafing
	MoveToLocation(waypointList[waypointID++], -1.f, false, true, false, false);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
			TEXT("Going to: " + waypointList[waypointID].ToString()));
}