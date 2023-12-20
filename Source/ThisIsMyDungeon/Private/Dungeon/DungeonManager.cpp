#include "Dungeon/DungeonManager.h"

#include "Dungeon/Waypoint.h"

ADungeonManager::ADungeonManager()
{
	// Add all rooms in RoomList here
	roomList.Add("Room1");
	roomList.Add("Room2");
	roomList.Add("Room3");
	roomList.Add("Room4");
	roomList.Add("Room5");
	roomList.Add("Room6");
	roomList.Add("Room7");
}

void ADungeonManager::UpdateRoomList()
{
	int newRoomId = FMath::RandRange(0, roomList.Num() - 1);
	nextRoomName = roomList[newRoomId];
	roomList.RemoveAt(newRoomId);
}

void ADungeonManager::SetMissingWaypoints()
{
	for (int i = 0; i < waypointList.Num(); i++)
		if (i != 0 && waypointList[i]->nextWaypoint.IsEmpty())
		{
			TArray<AWaypoint*> waypointToLinkTo;
			waypointToLinkTo.Add(waypointList[i - 1]);
			waypointList[i]->nextWaypoint = waypointToLinkTo;
		}
}

void ADungeonManager::DamageTreasure(float value)
{
	treasureLife -= value;
	if (treasureLife <= 0)
		OnTreasureGone();
}

void ADungeonManager::OnTreasureGone_Implementation() { /* For BP Use */ }
void ADungeonManager::OnNewWave_Implementation() { /* For BP Use */ }