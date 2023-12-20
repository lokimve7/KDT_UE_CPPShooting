// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyManager.h"
#include "CEnemy.h"


// Sets default values
ACEnemyManager::ACEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Enemy 공장 불러오자
	ConstructorHelpers::FClassFinder<ACEnemy> tempEnemyFactory(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Enemy.BP_Enemy_C'"));
	if (tempEnemyFactory.Succeeded())
	{
		enemyFactory = tempEnemyFactory.Class;
	}
}

// Called when the game starts or when spawned
void ACEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// 생성시간을 랜덤한 값으로 셋팅
	createTime = FMath::RandRange(fMin, fMax);
}

// Called every frame
void ACEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 필요한 멤버변수 : 현재시간, 생성시간, EnemyFactory(EnemyBlueprint)
	
	// 1. 현재시간을 흐르게 한다.
	currTime += DeltaTime;
	// 2. 만약에 현재시간이 생성시간 보다 커졌다면 (생성시간초가 지났다면)
	if (currTime > createTime)
	{
		// 3. Enemy 를 생성하고 위치시키자.
		GetWorld()->SpawnActor<ACEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
		// 4. 현재시간을 초기화
		currTime = 0;
		// 5. 생성시간을 랜덤한 값으로 셋팅
		createTime = FMath::RandRange(fMin, fMax);
	}
}

