// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyManager.h"



// Sets default values
ACEnemyManager::ACEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	// 일정시간이 지나면
	// 에너미공장에서 에너미를 생성과 동시에 위치를 나(EnemyManager)의 위치로
}

// Called every frame
void ACEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 필요한 멤버변수 : 현재시간
	
	// 1. 현재시간을 흐르게 한다.
	currTime += DeltaTime;
	// 2. 만약에 현재시간이 1보다 커졌다면 (1초가 지났다면)
	if (currTime > 1)
	{
		// 3. 1초가 지났어요 라고 Outlog 에 출력
		UE_LOG(LogTemp, Warning, TEXT("11111111111"));
		// 4. 현재시간을 초기화
		currTime = 0;
	}
}

