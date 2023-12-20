#include "Demon/PreviewTrap.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>

APreviewTrap::APreviewTrap()
{
	PrimaryActorTick.bCanEverTick = false;

	SetupMesh();
	SetupCollider();
}

void APreviewTrap::BeginPlay()
{
	Super::BeginPlay();
	meshComponent->SetStaticMesh(mesh);
	meshComponent->SetMaterial(0, validMaterial);
}

void APreviewTrap::SetupMesh()
{
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComponent"));
	RootComponent = meshComponent;
}

void APreviewTrap::SetupCollider()
{
	collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	collider->AttachToComponent(meshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	collider->SetRelativeLocation({ -50, -50, 0 });
	collider->SetWorldScale3D({ 1.5,1.5,1.5 });
}

void APreviewTrap::Valid()
{
	meshComponent->SetMaterial(0, validMaterial);
}
void APreviewTrap::UnValid()
{
	meshComponent->SetMaterial(0, unValidMaterial);
}

bool APreviewTrap::AsOverlaping()
{
	TSet<AActor*> temp;
	collider->GetOverlappingActors(temp);
	if (temp.Num() > 1)
		return true;

	return false;
}