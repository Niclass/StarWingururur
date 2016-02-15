// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class STARFOX_API ABullet : public AActor
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* MovementComponent;
public:
	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BulletMesh;



};
