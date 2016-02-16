// Fill out your copyright notice in the Description page of Project Settings.

#include "StarFox.h"
#include"Blueprint/UserWidget.h"
#include "StarFoxGameMode.h"

void AStarFoxGameMode::BeginPlay()
{
	

	Super::BeginPlay();
	if (HUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AStarFoxGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time--;
	if (Time <= 0)
	{
		GetWorld()->ServerTravel(FString("/Game/Maps/GameOver"));
	}
}

int32 AStarFoxGameMode::GetTime()
{
	return Time;
}

void AStarFoxGameMode::AddTime(int32 AddedTime)
{
	Time += AddedTime;
}



