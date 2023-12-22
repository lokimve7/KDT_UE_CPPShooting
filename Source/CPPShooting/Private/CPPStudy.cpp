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

	if (isMove == true)
	{
		//거리 = 시간 * 속력
		FVector p0 = GetActorLocation();
		FVector vt = GetActorRightVector() * 150 * DeltaTime;
		FVector p = p0 + vt;

		// 이동거리만큼 distance 빼주자
		distance -= 150 * DeltaTime;

		// 만약에 이동한 거리가 0보다 크다면?
		if (distance > 0)
		{
			SetActorLocation(p);
		}
		// 만약에 이동한 거리가 0보다 작니?
		else if (distance < 0)
		{
			p = p + GetActorRightVector() * distance;
			SetActorLocation(p);
			distance = 0;
		}
	}
}

void ACPPStudy::InputFire()
{
	UE_LOG(LogTemp, Warning, TEXT("InputFire"));

	isMove = true;
}
