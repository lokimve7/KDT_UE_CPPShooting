// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainWidget.h"
#include "Components/TextBlock.h"

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
