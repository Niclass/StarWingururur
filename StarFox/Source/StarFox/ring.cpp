// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include "ring.h"


// Sets default values
Aring::Aring()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ring"));
	RingMesh->AttachTo(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachTo(RootComponent);
	Trigger->SetRelativeScale3D(FVector(10, 10, 10));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &Aring::OnBeginOverlap);

}

// Called when the game starts or when spawned
void Aring::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aring::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void Aring::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult)
{
	Destroy();
}




