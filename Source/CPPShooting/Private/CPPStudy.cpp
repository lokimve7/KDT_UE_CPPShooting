// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPStudy.h"

// Sets default values
ACPPStudy::ACPPStudy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPPStudy::BeginPlay()
{
	Super::BeginPlay();
	
	// 입력 활성화
	EnableInput(GetWorld()->GetFirstPlayerController());

	// 입력 바인딩
	InputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ACPPStudy::InputFire);
}

// Called every frame
void ACPPStudy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACPPStudy::InputFire()
{
	UE_LOG(LogTemp, Warning, TEXT("InputFire"));
}
