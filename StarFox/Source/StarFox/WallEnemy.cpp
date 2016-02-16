// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include "WallEnemy.h"


// Sets default values
AWallEnemy::AWallEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy"));
	EnemyMesh->AttachTo(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->AttachTo(RootComponent);
	Trigger->SetRelativeScale3D(FVector(10, 10, 10));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWallEnemy::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AWallEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AWallEnemy::OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult)
{
	if (OtherActor->IsA(APawnWithCamera::StaticClass()))
	{
		pwc = Cast<APawnWithCamera>(OtherActor);
		if (pwc != NULL)
		{
			pwc->TakeDamage();
		}

		Destroy();
	}
	else if (OtherActor->IsA(ABullet::StaticClass()))
	{
		Destroy();

	}
}
