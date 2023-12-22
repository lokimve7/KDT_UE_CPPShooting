// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPPSHOOTING_API UCGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// BeginPlay 와 같은 기능의 함수
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere)
	class UButton* btnRetry;

	UPROPERTY(EditAnywhere)
	class UButton* btnQuit;

public:
	UFUNCTION()
	void OnClickRetry();

	UFUNCTION()
	void OnClickQuit();	
};
