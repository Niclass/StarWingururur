// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include "BoxDestroy.h"


// Sets default values
ABoxDestroy::ABoxDestroy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

