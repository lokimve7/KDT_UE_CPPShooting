// Fill out your copyright notice in the Description page of Project Settings.


#include "CGameOverWidget.h"
#include "Components/Button.h"

void UCGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// btnRetry 를 가져오자. (UWidget* 로 반환)
	UWidget* widget = GetWidgetFromName(TEXT("btnRetry"));
	// UButton 형으로 형반환
	btnRetry = Cast<UButton>(widget);
	// btnRetry 가 클릭 되었을 때 호출되는 함수 등록
	btnRetry->OnClicked.AddDynamic(this, &UCGameOverWidget::OnClickRetry);
}

void UCGameOverWidget::OnClickRetry()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClickRetry"));
}
