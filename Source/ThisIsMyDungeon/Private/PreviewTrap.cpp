// Sue Me.


#include "PreviewTrap.h"

// Sets default values
APreviewTrap::APreviewTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComponent"));
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComponent"));
	RootComponent = meshComponent;
}

// Called when the game starts or when spawned
void APreviewTrap::BeginPlay()
{
	Super::BeginPlay();
	meshComponent->SetStaticMesh(mesh);
	meshComponent->SetMaterial(0, validMaterial);
}

void APreviewTrap::Valid()
{
	meshComponent->SetMaterial(0, validMaterial);
}
void APreviewTrap::UnValid()
{
	meshComponent->SetMaterial(0, unValidMaterial);
}

// Called every frame
void APreviewTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

