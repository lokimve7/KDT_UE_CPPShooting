// Fill out your copyright notice in the Description page of Project Settings.


#include "CBackground.h"

// Sets default values
ACBackground::ACBackground()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static Mesh Component 추가
	compMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	// RootComponent 로 설정
	RootComponent = compMesh;

	// Plane 모양을 읽어 와서 설정
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (tempMesh.Succeeded())
	{
		compMesh->SetStaticMesh(tempMesh.Object);
	}
	
	// 우주 이미지 읽어 와서 설정
	ConstructorHelpers::FObjectFinder<UMaterial> tempMat(TEXT("/Script/Engine.Material'/Game/Resources/MatBG.MatBG'"));
	if (tempMat.Succeeded())
	{
		compMesh->SetMaterial(0, tempMat.Object);
	}
}

// Called when the game starts or when spawned
void ACBackground::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBackground::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 아래로 움직이자 (P = P0 + vt)
	FVector p0 = GetActorLocation();
	FVector vt = FVector::DownVector * scrollSpeed * DeltaTime;
	FVector p = p0 + vt;

	// 만약에 p 의 z 값이 -3000 보다 작으면 p 의 z 값에 9000 을 더한다.
	if (p.Z < -3000)
	{
		p.Z += 9000;
	}

	SetActorLocation(p);
}

