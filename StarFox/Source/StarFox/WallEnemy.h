// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PawnWithCamera.h"
#include "WallEnemy.generated.h"

UCLASS()
class STARFOX_API AWallEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere)
		APawnWithCamera* pwc;

	UFUNCTION()
		void OnBeginOverlap(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
