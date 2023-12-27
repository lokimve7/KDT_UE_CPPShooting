// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>
#include "CPlayer.h"

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComponent 생성 후 RootComponent 로
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	SetRootComponent(compBox);
	// compBox 의 BoxExtent 의 값을 25, 25, 50 으로 하자
	compBox->SetBoxExtent(FVector(25, 25, 50));
	// compBox 의 Collision preset 을 Bullet 으로 하자
	compBox->SetCollisionProfileName(TEXT("Bullet"));

	// StaticMeshComponent 를 RootComponent 의 자식으로
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox); //(RootComponent)
	// 크기를 0.5, 0.5, 1 로 하자
	compMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1));
	// Collision preset 을 NoCollision 으로 하자
	compMesh->SetCollisionProfileName(TEXT("NoCollision"));

	// Cube 를 읽어와서 셋팅
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}

	// Cube 의 매터리얼 셋팅
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Engine/EngineDebugMaterials/TangentColorMaterial.TangentColorMaterial'"));
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//위로 계속 이동하고 싶다.(P = P0 + vt)
	FVector p0 = GetActorLocation();
	FVector vt = GetActorUpVector() * moveSpeed * DeltaTime;
	FVector p = p0 + vt;
	SetActorLocation(p);
}

void ACBullet::SetAcitve(bool isActive)
{
	// 만약에 isActive 가 true 면
	if (isActive == true)
	{
		// 모양(mesh) 를 보이게 하자
		compMesh->SetVisibility(isActive);
		// 충돌 할 수 있게 하자
		compBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	// 그렇지 않으면
	else
	{
		// 모양(mesh) 를 안보이게 하자
		compMesh->SetVisibility(isActive);
		// 충돌 하지 않게 하자
		compBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACBullet::InsertMagazine()
{
	// 1. Player 를 찾자
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

	// 2. 만약에 player 를 찾지 못했으면 함수를 나가라.
	if (actor == nullptr) return;
	
	// 3. ACPlayer 로 형변환
	ACPlayer* player = Cast<ACPlayer>(actor);
	// 4. 나를 Player 가 가지고 있는 탄창에 넣자
	player->magazine.Add(this);
	// 5. 나를 비활성화
	SetAcitve(false);


}

