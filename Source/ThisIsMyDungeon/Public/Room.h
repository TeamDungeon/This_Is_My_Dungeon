// Sue Me.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonManager.h"
#include "Room.generated.h"

class ADungeonManager;

UCLASS()
class THISISMYDUNGEON_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lists") TArray<FVector> RoomWaypoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	ARoom();
};
