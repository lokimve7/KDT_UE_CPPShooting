// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPSHOOTING_API ACMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACMainGameMode();

	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void AddScore(int32 value);

	UFUNCTION()
	void SaveData();

	UFUNCTION()
	void LoadData();

	UFUNCTION()
	void ShowGameOverUI();


	UPROPERTY()
	int32 currScore = 0;

	UPROPERTY()
	int32 bestSocre = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCMainWidget> mainWidget;

	UPROPERTY(EditAnywhere)
	class UCMainWidget* mainUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCGameOverWidget> gameOverWidget;

	UPROPERTY(EditAnywhere)
	class UCGameOverWidget* gameOverUI;
};
