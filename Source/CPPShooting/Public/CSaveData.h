// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CSaveData.generated.h"

/**
 * 
 */
UCLASS()
class CPPSHOOTING_API UCSaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	float saveBestScore = 0;
};
