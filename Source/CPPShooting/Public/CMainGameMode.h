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
	UFUNCTION()
	void AddScore(int32 value);

	UPROPERTY()
	int32 currScore = 0;
};
