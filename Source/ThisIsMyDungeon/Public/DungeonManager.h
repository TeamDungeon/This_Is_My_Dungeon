// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonManager.generated.h"

UCLASS()
class THISISMYDUNGEON_API ADungeonManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(BlueprintReadWrite, Category = "Strings") FString NextRoomName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<FString> RoomList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vector3") FVector NextRoomPos = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<FVector> WaypointList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ADungeonManager();

	UFUNCTION(BlueprintCallable) void UpdateRoomList();

};