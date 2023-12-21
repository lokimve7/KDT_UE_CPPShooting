// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainGameMode.h"

void ACMainGameMode::AddScore(int32 value)
{
	// 현재점수를 누적시키다
	currScore += value;
	
	UE_LOG(LogTemp, Warning, TEXT("currScore : %d"), currScore);
}
