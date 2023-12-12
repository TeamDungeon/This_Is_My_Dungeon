#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticVars.generated.h"

UCLASS()
class THISISMYDUNGEON_API AStaticVars : public AActor
{
	GENERATED_BODY()
public:
	//-_Here_are_some_static_variable_that_need_to_be_acess_------------------------
	static ACharacter* static_trapPlacer;
	static ACharacter* static_player;
	//------------------------------------------------------------------------------
	AStaticVars();

	static void SetPlayer(ACharacter* player);
	static void SetTrapPlacer(ACharacter* trapPlacer);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};


