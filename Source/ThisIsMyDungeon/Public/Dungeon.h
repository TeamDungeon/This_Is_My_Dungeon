// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Dungeon.generated.h"




UCLASS()
class THISISMYDUNGEON_API ADungeon : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere) FName LevelToLoad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vectors") TArray<FVector> WaypointList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FNames") FName RoomName;


protected:
	virtual void BeginPlay() override;

public:	
	ADungeon();

	// For the Path, use /Game as root of the Content folder
	UFUNCTION(BlueprintCallable) void LoadRoom(FString _RoomDir);
};
