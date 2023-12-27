// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "Components/BoxComponent.h"
#include "CBullet.h"
#include "Kismet/GameplayStatics.h"
#include "CMainGameMode.h"


// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxComponent 추가 
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	//BoxComponent 를 RootComponent 로 만들자
	SetRootComponent(compBox); // 또는 RootComponent = compBox;
	//Collision Enable 설정(물리적인 충돌, 감지 충돌, 둘 다 허용)
	compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Object Type
	compBox->SetCollisionObjectType(ECC_GameTraceChannel3);
	//모든 Response 를 Ignore 하자
	compBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Enemy 를 Overlap 으로 하자
	compBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	
	//StaticeMeshComponent 추가
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	//compMesh 를 RootComponent 의 자식으로 설정
	compMesh->SetupAttachment(RootComponent);
	//Collision Preset 을 NoCollision으로 하자
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

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

	//총알 공장을 가져오자.
	ConstructorHelpers::FClassFinder<ACBullet> tempBulletFactory(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Bullet.BP_Bullet_C'"));
	if (tempBulletFactory.Succeeded())
	{
		bulletFactory = tempBulletFactory.Class;
	}

	//총알 소리 가져오자.
	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("/Script/Engine.SoundWave'/Game/Resources/star-wars-blaster.star-wars-blaster'"));
	if (tempSound.Succeeded())
	{
		fireSound = tempSound.Object;
	}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// 충돌 되었을 때 호출되는 함수 등록
	compBox->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnOverlap);

	// 탄창에 총알을 만들어서 넣자
	for (int32 i = 0; i < 5; i++)
	{
		// 1. 총알을 생성한다.
		ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(bulletFactory);
		// 2. 생성된 총알을 탄창에 넣는다.
		magazine.Add(bullet);
	}

	// TArray 사용 예시
	TArray<float> arrayNum;

	// 추가
	arrayNum.Add(10);
	arrayNum.Add(20);
	arrayNum.Add(moveSpeed);

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}

	// 삭제
	//arrayNum.RemoveAt(1);
	arrayNum.Remove(20);

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}

	// 중간 삽입
	arrayNum.Insert(100, 1);

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}
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
	

	// 현재시간을 증가
	currTime += DeltaTime;
	// 만약에 현재시간이 0.5 보다 크다면
	if (currTime > 0.5f)
	{
		// 총알을 발사
		//InputFire();
		// 현재시간 초기화
		currTime = 0;
	}
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//A, D 키 눌렀을 때 호출되는 함수 등록
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::InputHorizontal);
	//W, S 키 눌렀을 때 호출되는 함수 등록
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::InputVertical);
	//Fire 에 등록된 키가 눌렸을 때 호출되는 함수 등록
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ACPlayer::InputFire);
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

void ACPlayer::InputFire()
{
	// 총알공장(BP_Bullet) 에서 총알을 하나 생성한다.
	//ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(bulletFactory);
	//if (bullet == nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("bullet is null"));
	//}
	//else
	//{
	//	// 생성된 총알을 나의 위치에 놓는다.
	//	bullet->SetActorLocation( GetActorLocation() );
	//}

	//또는
	GetWorld()->SpawnActor<ACBullet>(bulletFactory, GetActorLocation(), GetActorRotation());

	// 총알 발사 소리
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

void ACPlayer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약에 충돌한 액터가 Enemy 라면
	if (OtherActor->GetName().Contains(TEXT("Enemy")))
	{
		// GameOverWidget 띄우자
		ACMainGameMode* currGameMode = GetWorld()->GetAuthGameMode<ACMainGameMode>();
		currGameMode->ShowGameOverUI();

		// 마우스 포이터 보이게 하자
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		// 게임을 일시 정지
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// 부딪힌 액터 파괴
		OtherActor->Destroy();

		// 나도 파괴
		Destroy();
	}	
}
