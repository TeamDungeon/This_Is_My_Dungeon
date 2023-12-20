#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonManager.generated.h"

UCLASS()
class THISISMYDUNGEON_API ADungeonManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonManager")
	float treasureLife;

	UPROPERTY(BlueprintReadWrite, Category = "DungeonManager")
	FString nextRoomName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonManager")
	TArray<FString> roomList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonManager")
	FVector nextRoomPos = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DungeonManager")
	TArray<class AWaypoint*> waypointList;

public:
	ADungeonManager();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void UpdateRoomList();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void SetMissingWaypoints();

	UFUNCTION(BlueprintCallable, Category = "Functions")
	void DamageTreasure(float damage);

	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnTreasureGone();

	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnNewWave();
};
