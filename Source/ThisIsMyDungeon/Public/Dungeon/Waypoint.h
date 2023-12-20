#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

UCLASS()
class THISISMYDUNGEON_API AWaypoint : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint")
	TArray<AWaypoint*> nextWaypoint;

public:
	AWaypoint();
};
