// Fill out your copyright notice in the Description page of Project Settings.


#include "CMainGameMode.h"
#include "CMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "CSaveData.h"
#include "CGameOverWidget.h"

ACMainGameMode::ACMainGameMode()
{
	// MainWidget 클래스 가져오자
	ConstructorHelpers::FClassFinder<UCMainWidget> tempMainWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_MainWidget.BP_MainWidget_C'"));
	if (tempMainWidget.Succeeded())
	{
		mainWidget = tempMainWidget.Class;
	}

	// GameOverWidget 클래스 가져오자
	ConstructorHelpers::FClassFinder<UCGameOverWidget> tempGameOverWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/BP_GameOverWidget.BP_GameOverWidget_C'"));
	if (tempGameOverWidget.Succeeded())
	{
		gameOverWidget = tempGameOverWidget.Class;
	}
}

void ACMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	// mainWiget 생성
	mainUI = CreateWidget<UCMainWidget>(GetWorld(), mainWidget);
	// 생성된 Widget 을 화면에 붙이자
	mainUI->AddToPlayerScreen();
	// 최고 점수 불러오자
	LoadData();
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
		// 최고점수 저장
		SaveData();
	}
}

void ACMainGameMode::SaveData()
{
	// bestScore -> CSaveData 에 있는 saveBestScore 변수에 넣는다.

	// 1. CSaveData 를 하나 생성한다. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::CreateSaveGameObject(UCSaveData::StaticClass());
	// 2. 생성한 놈을 CSaveData 로 형변환
	UCSaveData* saveData = Cast<UCSaveData>(saveGame);
	// 3. saveBestScore = bestScore
	saveData->saveBestScore = bestSocre;
	// 4. CSaveData 을 저장
	UGameplayStatics::SaveGameToSlot(saveData, TEXT("BEST_SCORE"), 0);
}

void ACMainGameMode::LoadData()
{
	// 1. "BEST_SCORE" 으로 되어 있는 데이터를 불러온다. (USaveGame*)
	USaveGame* loadGame = UGameplayStatics::LoadGameFromSlot(TEXT("BEST_SCORE"), 0);
	// 2. 만약에 잘 읽어왔다면 (저장한 값이 있었다면)
	if (loadGame != nullptr)
	{
		// 3. 불러온 객체를 UCSaveData 로 형변환
		UCSaveData* loadData = Cast<UCSaveData>(loadGame);	
		// 4. bestScore = saveBestScore
		bestSocre = loadData->saveBestScore;
		// 5. 최고 점수 UI 갱신
		mainUI->UpdateBestScoreUI(bestSocre);
	}
}

void ACMainGameMode::ShowGameOverUI()
{
	// GameOverWidget 을 만든다.
	gameOverUI = CreateWidget<UCGameOverWidget>(GetWorld(), gameOverWidget);
	// 만든 Widget 을 화면에 띄운다.
	gameOverUI->AddToPlayerScreen();
}
