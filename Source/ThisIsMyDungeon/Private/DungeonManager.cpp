// Sue Me.

#define DEBUG 1

#include "DungeonManager.h"

// Sets default values
ADungeonManager::ADungeonManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add all rooms in RoomList here
	RoomList.Add("Room1");
	RoomList.Add("Room2");
	RoomList.Add("Room3");
	RoomList.Add("Room4");
	RoomList.Add("Room5");
	//RoomList.Add("Room6");

	// Add treasure room waypoint
	WaypointList.Add(FVector(0.0f, 0.0f, 0.0f));

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

	//TArray<int> tempList;
	//FVector temp;
	//for (int i = 0; i < WaypointList.Num(); i++) {
	//	if (WaypointList[i] == temp) {
	//		tempList.Add(i);
	//	}
	//	temp = WaypointList[i];
	//}

#if DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("Room generated : %s"), *NextRoomName));
#endif DEBUG

}