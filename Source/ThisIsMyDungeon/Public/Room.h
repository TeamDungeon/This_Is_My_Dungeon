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
	Wood	UMETA(DisplayName = "Wood")
};


UCLASS()
class THISISMYDUNGEON_API ARoom : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector3") FVector RoomExit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<AWaypoint*> RoomWaypoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enums") TEnumAsByte<ERoomType> RoomType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector2") FVector DecorationBoxStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector2") FVector DecorationBoxEnd;

protected:
	virtual void BeginPlay() override;

public:	
	ARoom();
};
