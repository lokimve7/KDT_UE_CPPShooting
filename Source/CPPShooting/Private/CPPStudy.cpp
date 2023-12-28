// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPStudy.h"

class UserInfo
{
public:
	UserInfo() {}

	UserInfo(int32 a, float h) { 
		age = a;
		height = h;
	}

	int32 age;
	float height;
};

class FSortByNumber
{
public:
	bool operator() (const float& a, const float& b) const {
		return a > b; // 내림차순
		//return a < b; // 오름차순
	}
};

class FSortByUserInfo
{
public:
	bool operator() (const UserInfo& a, const UserInfo& b) const {
		return a.age > b.age;
	}
};


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



	// TArray 사용 예시
	TArray<UserInfo*> arrayUserInfo;
	UserInfo pUser(10, 20);
	arrayUserInfo.Add(&pUser);

	UserInfo pUser2(5, 30);
	arrayUserInfo.Add(&pUser2);

	UserInfo pUser3(25, 3);
	arrayUserInfo.Add(&pUser3);

	arrayUserInfo.Sort(FSortByUserInfo());

	for (int32 i = 0; i < arrayUserInfo.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"),  arrayUserInfo[i]->age);
	}



	TArray<float> arrayNum;

	// 추가
	arrayNum.Add(56);
	arrayNum.Add(7);
	arrayNum.Add(45);
	arrayNum.Add(1);


	// 숫자를 오름차순으로 정렬
	//arrayNum.Sort();
	//arrayNum.Sort(FSortByNumber());

	for (int32 i = 0; i < arrayNum.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	}

	TArray<FString> arrString;
	arrString.Add(TEXT("b"));
	arrString.Add(TEXT("a"));
	arrString.Add(TEXT("c"));
	arrString.Sort();

	for (int32 i = 0; i < arrString.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *arrString[i]);
	}

	//// 삭제
	////arrayNum.RemoveAt(1);
	//arrayNum.Remove(20);

	//for (int32 i = 0; i < arrayNum.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	//}

	//// 중간 삽입
	//arrayNum.Insert(100, 1);

	//for (int32 i = 0; i < arrayNum.Num(); i++)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%d : %f"), i, arrayNum[i]);
	//}


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
