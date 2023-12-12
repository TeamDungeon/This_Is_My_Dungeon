// Sue Me.

#include "DungeonManager.h"

// Sets default values
ADungeonManager::ADungeonManager()
{
	// Add all rooms in RoomList here
	RoomList.Add("Room1");
	RoomList.Add("Room2");
	RoomList.Add("Room3");
	RoomList.Add("Room4");
	RoomList.Add("Room5");
	RoomList.Add("Room6");
	RoomList.Add("Room7");
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