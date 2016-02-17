// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include "WinTrigger.h"


// Sets default values
AWinTrigger::AWinTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachTo(RootComponent);
	Trigger->SetRelativeScale3D(FVector(10, 10, 10));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWinTrigger::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AWinTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWinTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWinTrigger::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult)
{
	if (OtherActor->IsA(APawnWithCamera::StaticClass()))
	{
		if (OtherActor->IsA(APawnWithCamera::StaticClass()))
		{
			
			GetWorld()->ServerTravel(FString("/Game/Maps/Win"));
		}
	}
}

