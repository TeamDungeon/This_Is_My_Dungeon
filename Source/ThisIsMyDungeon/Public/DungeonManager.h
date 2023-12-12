// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.h"
#include "DungeonManager.generated.h"



UCLASS()
class THISISMYDUNGEON_API ADungeonManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floats") float TreasureLife;

	UPROPERTY(BlueprintReadWrite, Category = "Strings") FString NextRoomName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<FString> RoomList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector3") FVector NextRoomPos = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<FVector> WaypointGhostList;		// TO REMOVE
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<AWaypoint*> WaypointList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ADungeonManager();

	UFUNCTION(BlueprintCallable) void UpdateRoomList();
	UFUNCTION(BlueprintCallable) void SetMissingWaypoints();
};
