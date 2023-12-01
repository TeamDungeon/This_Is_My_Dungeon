// Sue Me.

#define DEBUG 1

#include "DungeonManager.h"

// Sets default values
ADungeonManager::ADungeonManager()
{
	// Add all rooms in RoomList here
	RoomList.Add("P_Room1");
	RoomList.Add("P_Room2");
	RoomList.Add("P_Room3");
	RoomList.Add("P_Room4");
	RoomList.Add("P_Room5");
	RoomList.Add("P_Room6");
	RoomList.Add("P_Room7");
}

// Called when the game starts or when spawned
void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonManager::UpdateRoomList()
{
	int NewRoomId = FMath::RandRange(0, RoomList.Num() - 1);
	NextRoomName = RoomList[NewRoomId];
	RoomList.RemoveAt(NewRoomId);

#if DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("Room generated : %s"), *NextRoomName));
#endif DEBUG

}

void ADungeonManager::SetMissingWaypoints()
{
	for (int i = 0; i < WaypointList.Num(); i++) {
		if (i != 0 && WaypointList[i]->NextWaypoint.IsEmpty()) {
			TArray<AWaypoint*> WaypointToLinkTo;
			WaypointToLinkTo.Add(WaypointList[i - 1]);
			WaypointList[i]->NextWaypoint = WaypointToLinkTo;
		}
	}
}