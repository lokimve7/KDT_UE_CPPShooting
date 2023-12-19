// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include "Components/BoxComponent.h"

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

	// StaticMeshComponent 를 RootComponent 의 자식으로
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	compMesh->SetupAttachment(compBox); //(RootComponent)
	// 크기를 0.5, 0.5, 1 로 하자
	compMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1));

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

