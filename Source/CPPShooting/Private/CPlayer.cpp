// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComponent 추가 
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//BoxComponent 를 RootComponent 로 만들자
	SetRootComponent(compBox); // 또는 RootComponent = compBox;
	
	//StaticeMeshComponent 추가
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//compMesh 를 RootComponent 의 자식으로 설정
	compMesh->SetupAttachment(RootComponent);
	//모양(StaticMesh) 을 읽어들여서 셋팅하자
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Resources/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));
	//만약에 잘 읽어들였다면
	if (tempMesh.Succeeded())
	{
		//Mesh를 셋팅하자
		compMesh->SetStaticMesh(tempMesh.Object);
		//회전시키자(x : 90, z : 90)
		//(Pitch=2.000000,Yaw=3.000000,Roll=1.000000)
		compMesh->SetRelativeRotation(FRotator(0, 90, 90));
		//크기조절
		compMesh->SetRelativeScale3D(FVector(4));
	}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//P = P0 + vt
	FVector p0 = GetActorLocation();

	//좌, 우를 결정하는 방향을 구한다.
	FVector dirH = GetActorRightVector() * h;
	//상, 하를 결정하는 방향을 구한다.
	FVector dirV = GetActorUpVector() * v;
	//최종 방향을 구하자
	FVector dir = dirH + dirV;
	//최종 방향의 크기를 1로 만들자.
	dir.Normalize();

	FVector vt = dir * moveSpeed * DeltaTime;
	FVector p = p0 + vt;
	SetActorLocation(p);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//A, D 키 눌렀을 때 호출되는 함수 등록
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::InputHorizontal);
	//W, S 키 눌렀을 때 호출되는 함수 등록
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::InputVertical);
}

void ACPlayer::InputHorizontal(float value)
{
	h = value;
	//UE_LOG(LogTemp, Warning, TEXT("H : %f"), value);
}

void ACPlayer::InputVertical(float value)
{
	v = value;
	//UE_LOG(LogTemp, Warning, TEXT("V : %f"), value);
}
