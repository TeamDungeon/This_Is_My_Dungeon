#include "Trap.h"

ATrap::ATrap() { PrimaryActorTick.bCanEverTick = true; }

int ATrap::GetCost() const { return cost; }

FUintVector2 ATrap::GetTileSize() const { return tileSize; }

UTexture2D* ATrap::GetTrapImage() { return trapImage; }