// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include "BoxDestroy.h"


// Sets default values
ABoxDestroy::ABoxDestroy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	BoxMesh->AttachTo(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachTo(RootComponent);
	Trigger->SetRelativeScale3D(FVector(10, 10, 10));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABoxDestroy::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ABoxDestroy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoxDestroy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABoxDestroy::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult)
{
	if (OtherActor->IsA(APawnWithCamera::StaticClass()))
	{
		GetWorld()->ServerTravel(FString("/Game/Maps/GameOver"));
	}
}	

