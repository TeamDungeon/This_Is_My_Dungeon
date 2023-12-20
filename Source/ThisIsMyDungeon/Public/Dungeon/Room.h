#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector3")
	FVector roomExit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists")
	TArray<class AWaypoint*> roomWaypoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enums")
	TEnumAsByte<ERoomType> roomType;

public:
	ARoom();
};
