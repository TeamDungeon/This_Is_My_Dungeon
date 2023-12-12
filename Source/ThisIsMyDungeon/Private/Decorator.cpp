// Sue Me.

#include "Kismet/KismetMathLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Decorator.h"

// Sets default values
ADecorator::ADecorator()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	RootComponent = BoxCollider;
}

// Called when the game starts or when spawned
void ADecorator::BeginPlay()
{
	Super::BeginPlay();

	// Find Box bounds
	FBoxSphereBounds Bounds = BoxCollider->CalcBounds(BoxCollider->GetComponentTransform());
	//UKismetMathLibrary::RandomBoolWithWeight(SpawnRNG);

	for (int i = 0; i < AmountToSpawn; i++) {
		IDMeshToSpawn = FMath::RandRange(0, MeshesToSpawn.Num() - 1);
		for (int j = 0; j < MeshesToSpawn.Num(); j++) {
			if (j == IDMeshToSpawn) {
				// Find Random point within the boundig box
				FVector RandomPoint = FMath::RandPointInBox(FBox(Bounds.Origin - Bounds.BoxExtent, Bounds.Origin + Bounds.BoxExtent));

				// Spawn Actor
				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), RandomPoint, FRotator::ZeroRotator);
				RandomPoint.Z = 0.0f;

				if (SpawnedActor) {
					// Create Mesh
					UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(SpawnedActor, TEXT("MeshComponent"));
					MeshComponent->RegisterComponent();
					// Assign Mesh
					MeshComponent->SetStaticMesh(MeshesToSpawn[j]);
					MeshComponent->AttachToComponent(SpawnedActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
					// Attach object location to correct mesh location
					SpawnedActor->SetRootComponent(MeshComponent);
					SpawnedActor->SetActorLocation(RandomPoint);
					// Set Actor Rotation
					float ZRot = FMath::RandRange(0, 360);
					GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, FString::Printf(TEXT("%f"), ZRot));
					SpawnedActor->SetActorRotation(FRotator(0, ZRot, 0));
					// Set Actor Scale
					SpawnedActor->SetActorScale3D(Scale);
				}
			}
		}
	}
}