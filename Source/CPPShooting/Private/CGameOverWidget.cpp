// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UWidget* widget;

	// btnRetry 를 가져오자. (UWidget* 로 반환)
	widget = GetWidgetFromName(TEXT("btnRetry"));
	// UButton 형으로 형변환
	btnRetry = Cast<UButton>(widget);
	// btnRetry 가 클릭 되었을 때 호출되는 함수 등록
	btnRetry->OnClicked.AddDynamic(this, &UCGameOverWidget::OnClickRetry);

	// btnQuit 을 가져오자. (UWidget* 로 반환)
	widget = GetWidgetFromName(TEXT("btnQuit"));
	// UButton형으로  형변환
	btnQuit = Cast<UButton>(widget);
	// btnQuit 이 클릭 되었을 때 호출되는 함수 등록
	btnQuit->OnClicked.AddDynamic(this, &UCGameOverWidget::OnClickQuit);
}

void UCGameOverWidget::OnClickRetry()
{
	// 레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainGameLevel"));
}

void UCGameOverWidget::OnClickQuit()
{
	// 앱을 종료 시킨다
	UKismetSystemLibrary::QuitGame(
		GetWorld(),
		GetWorld()->GetFirstPlayerController(),
		EQuitPreference::Quit, false);
}
