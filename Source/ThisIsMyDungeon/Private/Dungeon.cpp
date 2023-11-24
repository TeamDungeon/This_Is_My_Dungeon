// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreamingDynamic.h"



ADungeon::ADungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADungeon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeon::LoadRoom(FString _RoomDir)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*_RoomDir), true);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Loaded room"));
}
