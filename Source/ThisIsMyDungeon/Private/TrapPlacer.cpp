// Sue Me.


#include "TrapPlacer.h"

// Sets default values
ATrapPlacer::ATrapPlacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrapPlacer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrapPlacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto& transf = GetTransform();
	const auto& xpos = transf.GetLocation().X;
	const auto& ypos = transf.GetLocation().Y;
	xPosTile = xpos / tileSize;
	yPosTile = ypos / tileSize;

	if (xpos > 0) xPosTile += 1;
	else xPosTile -= 1;

	if (ypos > 0) yPosTile += 1;
	else yPosTile -= 1;
}

