// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include "PawnWithCamera.h"


// Sets default values
APawnWithCamera::APawnWithCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	UFOMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UFO"));
	UFOMesh->AttachTo(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	CollisionSphere->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CollisionSphere->InitSphereRadius(16.0f);
	CollisionSphere->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = CollisionSphere;

	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->AttachTo(RootComponent);
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(0.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 1.0f;

	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->AttachTo(OurCameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//*************************
	// Set handling parameters
	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 100.f;
	Health = 100.f;
	MaxHealth = 100.f;
	Boost = 100.f;
	MaxBoost = 100.f;


	CanBoost = true;
}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{

	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;


	AddActorLocalRotation(DeltaRotation);
	//*************************
	Super::Tick(DeltaTime);

	{
		FRotator YawRotation = GetActorRotation();
		YawRotation.Yaw = FMath::Clamp(YawRotation.Yaw + CameraInput.X, -30.0f, 30.0f);
		SetActorRotation(YawRotation);

		FRotator PitchRotation = GetActorRotation();
		PitchRotation.Pitch = FMath::Clamp(PitchRotation.Pitch + CameraInput.Y, -30.0f, 30.0f);
		SetActorRotation(PitchRotation);
	}

	if (Boost <= 0)
	{
		CanBoost = false;
	}
	if (Boost >= MaxBoost)
	{
		CanBoost = true;
	}
	// Is there no input?
	if (!CanBoost)
	{
		if (Boost <= 100)
		{
			Boost += .5f;
		}
	}

}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	//Hook up every-frame handling for our four axes
	InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);
	InputComponent->BindAxis("Thrust", this, &APawnWithCamera::ThrustInput);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &APawnWithCamera::ShootBullet);
}


void APawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}


void APawnWithCamera::ThrustInput(float Val)
{

	if (CanBoost && Boost >= 0)
	{
		bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
		// If input is not held down, reduce speed
		float CurrentAcc = bHasInput ? (Val * Acceleration) : (-1.5f * Acceleration);
		// Calculate new speed
		float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
		// Clamp between MinSpeed and MaxSpeed
		CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);


		if (bHasInput && Boost >= 0)
		{
			Boost--;
		}
		else if(!bHasInput && Boost <= MaxBoost)
			Boost += .5f;

	}
	if (!CanBoost)
	{
		float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * (-1.5f * Acceleration));
		// Clamp between MinSpeed and MaxSpeed
		CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
	}
}

void APawnWithCamera::ShootBullet()
{
	//PlaneMesh->ToggleVisibility();
	GetWorld()->SpawnActor<ABullet>(BulletClass, UFOMesh->GetSocketLocation("Gun"), UFOMesh->GetSocketRotation("Gun"));
}

void APawnWithCamera::TakeDamage()
{
	Health -= 10.f;
	if (Health <= 0)
	{
		GetWorld()->ServerTravel(FString("/Game/Maps/GameOver"));
	}
}
