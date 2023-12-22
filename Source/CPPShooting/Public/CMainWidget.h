// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPPSHOOTING_API UCMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* currScoreUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* bestScoreUI;

	UFUNCTION()
	void UpdateCurrScoreUI(int32 score);

	UFUNCTION()
	void UpdateBestScoreUI(int32 bestScore);
};
