// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CPlayer.h"

// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere Component 추가
	compSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SPHERE"));
	// Root Component 로 하자
	RootComponent = compSphere;
	// Sphere 의 반지름을 50으로 하자
	compSphere->SetSphereRadius(50);
	// Collision Enable 설정
	compSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Object Type 설정 (Enemy로)
	compSphere->SetCollisionObjectType(ECC_GameTraceChannel1);
	// 모든 Response 를 Ignore 로 하자
	compSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	// Bullet 은 Overlap 으로 하자
	compSphere->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	

	// StaticMeshComponent 추가
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// RootComponent 의 자식으로 설정
	compMesh->SetupAttachment(RootComponent);
	// Collision Prests 를 NoCollision 으로 하자
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	// 드론 모양을 읽어오자
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resources/Drone/Drone_low.Drone_low'"));
	if (tempMesh.Succeeded())
	{
		// 드론 모양을 셋팅
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	// compMesh 의 위치, 회전값 설정
	compMesh->SetRelativeLocation(FVector(50, 0, 0));
	// Pitch, yaw, roll (y, z, x)
	compMesh->SetRelativeRotation(FRotator(0, 90, 90));
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	int32 rand = UKismetMathLibrary::RandomIntegerInRange(0, 9);
	// 또는 int32 rand = FMath::RandRange(0, 9);

	// 50% 확률로 방향을 플레이어를 향하게 
	if (rand < 5)
	{
		// 처음에 한번 플레이어를 향하는 방향을 구하고
		// 플레이어를 찾자.
		if (target == nullptr)
		{
			target = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

			// 1. 플레이어를 향하는 방향을 구하자 (player 위치 - 나(Enemy)의 위치)
			FVector playerPos = target->GetActorLocation();
			dir = playerPos - GetActorLocation();

			// 만약에 크기가 2...였다고 가정하면..
			// 2. 방향의 크기를 1로 바꾸자
			dir.Normalize();		//---> dir 의 크기가 1이된다.
			//dir.GetSafeNormal();	//---> dir 의 크기가 유지, dir의 크기를 1로만들었을때의 Vector 반환
		}
	}
	// 50% 확률로 방향을 아래로 향하게
	else
	{
		dir = -GetActorUpVector();
	}	

	// Overlap 충돌이 되었을 때 호출되는 함수 등록 (Delegate = 함수를 담을수 있는 변수)
	compSphere->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnOverlap);

}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	// 그 방향으로 계속 이동하고싶다.
	// 3. P = P0 + vt  를 이용해서 구한 방향으로 계속 움지이자.
	FVector p0 = GetActorLocation();
	FVector vt = dir * moveSpeed * DeltaTime;
	FVector p = p0 + vt;
	SetActorLocation(p);
}

void ACEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 놈 파괴
	OtherActor->Destroy();
	// 나를 파괴
	Destroy();
}

