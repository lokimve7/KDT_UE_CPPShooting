// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

void UCMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// currScoreUI 의 위치를 500, 500 으로 하고 싶다.
	// 1. Slot 을 가져와서 (부모의Pointer  로 반환) Canvas Panel Slot 으로 형변환
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(currScoreUI->Slot);	
	// 2. 위치 변경
	slot->SetPosition(FVector2D(500, 500));
	// 3. 색상 변경 (120/255, 50/255, 200/255)
	currScoreUI->SetColorAndOpacity(FLinearColor(120/255.0f, 50/255.0f, 200/255.0f, 1));
}

void UCMainWidget::UpdateCurrScoreUI(int32 score)
{	
	//현재 점수 : score
	FString strScore = FString::Printf(TEXT("현재 점수 : %d"), score);

	currScoreUI->SetText(FText::FromString(strScore));	
}

void UCMainWidget::UpdateBestScoreUI(int32 bestScore)
{
	//최고 점수 : bestScore
	FString strBestScore = FString::Printf(TEXT("최고 점수 : %d"), bestScore);

	bestScoreUI->SetText(FText::FromString(strBestScore));
}
