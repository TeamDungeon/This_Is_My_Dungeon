// Sue Me.


#include "PreviewTrap.h"

// Sets default values
APreviewTrap::APreviewTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComponent"));
	SetupMesh();
	SetupCollider();
	//meshComponent->AttachToComponent(collider, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void APreviewTrap::BeginPlay()
{
	Super::BeginPlay();
	meshComponent->SetStaticMesh(mesh);
	meshComponent->SetMaterial(0, validMaterial);
	
	//meshComponent->collider
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

