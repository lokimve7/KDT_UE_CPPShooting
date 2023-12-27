// Fill out your copyright notice in the Description page of Project Settings.


#include "CDestroyZone.h"
#include "Components/BoxComponent.h"
#include "CBullet.h"

// Sets default values
ACDestroyZone::ACDestroyZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// boxComponent 설정
	compBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	// RootComponent 로 설정
	SetRootComponent(compBox);
	// compBox 의 크기를 키우자
	compBox->SetBoxExtent(FVector(50, 2000, 50));
	// collision preset 을 설정
	compBox->SetCollisionProfileName(TEXT("DestroyZone"));
}

// Called when the game starts or when spawned
void ACDestroyZone::BeginPlay()
{
	Super::BeginPlay();
	
	// Overlap 충돌이 되었을 때 호출되는 함수 등록
	compBox->OnComponentBeginOverlap.AddDynamic(this, &ACDestroyZone::OnOverlap);
}

// Called every frame
void ACDestroyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDestroyZone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 만약에 총알이 아니면
	if (OtherComp->GetCollisionObjectType() != ECollisionChannel::ECC_GameTraceChannel2)
	{
		// 부딪힌 액터 파괴하자
		OtherActor->Destroy();
	}	
	else
	{
		Cast<ACBullet>(OtherActor)->InsertMagazine();
	}
}

