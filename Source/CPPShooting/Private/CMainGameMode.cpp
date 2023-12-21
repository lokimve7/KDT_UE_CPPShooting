// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainGameMode.h"
#include "CMainWidget.h"

ACMainGameMode::ACMainGameMode()
{
	// MainWidget 클래스 가져오자
	ConstructorHelpers::FClassFinder<UCMainWidget> tempMainWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
	if (tempMainWidget.Succeeded())
	{
		mainWidget = tempMainWidget.Class;
	}
}

void ACMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	// mainWiget 생성
	mainUI = CreateWidget<UCMainWidget>(GetWorld(), mainWidget);
	// 생성된 Widget 을 화면에 붙이자
	mainUI->AddToPlayerScreen();
}

void ACMainGameMode::AddScore(int32 value)
{
	// 현재점수를 누적시키다
	currScore += value;

	// 현재점수 UI를 갱신
	mainUI->UpdateCurrScoreUI(currScore);

	// 만약에 현재점수가 최고점수보다 크다면
	if (currScore > bestSocre)
	{
		// 최고점수를 현재점수로 갱신
		bestSocre = currScore;
		// 최고점수 UI 를 갱신
		mainUI->UpdateBestScoreUI(bestSocre);
	}
}
