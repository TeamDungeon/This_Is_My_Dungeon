#include "Dungeon/Decorator.h"

#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

ADecorator::ADecorator()
{
	boxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	RootComponent = boxCollider;
}

void ADecorator::BeginPlay()
{
	Super::BeginPlay();

	// Find Box bounds
	FBoxSphereBounds Bounds = boxCollider->CalcBounds(boxCollider->GetComponentTransform());

	for (int i = 0; i < amountToSpawn; i++)
	{
		bool CanSpawn = UKismetMathLibrary::RandomBoolWithWeight(spawnRNG);
		if (CanSpawn)
		{
			IDMeshToSpawn = FMath::RandRange(0, meshesToSpawn.Num() - 1);
			for (int j = 0; j < meshesToSpawn.Num(); j++)
			{
				if (j == IDMeshToSpawn)
				{
					// Find Random point within the boundig box
					FVector randomPoint = FMath::RandPointInBox(FBox(Bounds.Origin - Bounds.BoxExtent, Bounds.Origin + Bounds.BoxExtent));

					// Spawn Actor
					AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), randomPoint, FRotator::ZeroRotator);
#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT || WITH_EDITOR
					spawnedActor->SetFolderPath("Level/Decor");
#endif
					randomPoint.Z = 15.0;

					if (spawnedActor)
					{
						// Create Mesh
						UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(spawnedActor, TEXT("MeshComponent"));
						meshComponent->RegisterComponent();
						// Assign Mesh
						meshComponent->SetStaticMesh(meshesToSpawn[j]);
						meshComponent->AttachToComponent(spawnedActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
						// Attach object location to correct mesh location
						spawnedActor->SetRootComponent(meshComponent);
						spawnedActor->SetActorLocation(randomPoint);
						// Set Actor Rotation
						float ZRot = FMath::RandRange(0, 360);
						spawnedActor->SetActorRotation(FRotator(0, ZRot, 0));
						// Set Actor Scale
						spawnedActor->SetActorScale3D(scale);
					}
				}
			}
		}
	}
}