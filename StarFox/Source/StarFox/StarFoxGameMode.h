// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/GameMode.h"
#include "StarFoxGameMode.generated.h"

/**
 *
 */
UCLASS()
class STARFOX_API AStarFoxGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(VisibleAnywhere)
		int32 Time = 1000;

	UFUNCTION(BlueprintPure, Category = "Time")
		int32 GetTime();

	UFUNCTION(Category = "Time")
		void AddTime(int32 AddedTime);

	UPROPERTY()
	class UUserWidget* CurrentWidget;



	


};
