// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonManager.h"
#include "Waypoint.h"
#include "Room.generated.h"

class ADungeonManager;

UENUM(BlueprintType)
enum ERoomType
{
	Basic	UMETA(DisplayName = "Basic"),
	Bone	UMETA(DiplayName = "Bone"),
};


UCLASS()
class THISISMYDUNGEON_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector3") FVector RoomExit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<AWaypoint*> RoomWaypoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enums") TEnumAsByte<ERoomType> RoomType;

protected:
	virtual void BeginPlay() override;

public:	
	ARoom();
};
