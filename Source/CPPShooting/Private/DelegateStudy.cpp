// Fill out your copyright notice in the Description page of Project Settings.


#include "DelegateStudy.h"

// Sets default values
ADelegateStudy::ADelegateStudy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADelegateStudy::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(GetWorld()->GetFirstPlayerController());
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADelegateStudy::InputTest);


	// 람다식
	// [this] (매개변수...) -> 반환값 
	// {
	//		To do...
	// }

	// DECLARE_DELEGATE 함수 등록  (3가지)
	simpleDel.BindUFunction(this, TEXT("SimpleDelFunc"));
	simpleDel.BindUObject(this, &ADelegateStudy::SimpleDelFunc);
	/*simpleDel.BindLambda([this]()->void {
		UE_LOG(LogTemp, Warning, TEXT("Call SimpleDelFunc by Lambda"));
	});*/

	// DECLARE_DELEGATE_OneParam 함수 등록
	simpleOneParamDel.BindUFunction(this, TEXT("SimpleOneParamDelFunc"));
	simpleOneParamDel.BindUObject(this, &ADelegateStudy::SimpleOneParamDelFunc);
	/*simpleOneParamDel.BindLambda([this](FString str) -> void {
		UE_LOG(LogTemp, Warning, TEXT("Call SimpleOneParamDelFunc by Lambda"));
	});*/

	// DECLARE_MULTICAST_DELEGATE 함수 등록
	delHandle = multiDel.AddUFunction(this, TEXT("MultiDel1"));
	multiDel.AddUObject(this, &ADelegateStudy::MultiDel2);
	multiDel.AddUObject(this, &ADelegateStudy::SimpleDelFunc);
	multiDel.AddLambda([this]() -> void {
		UE_LOG(LogTemp, Warning, TEXT("Call multiDel by Lambda"));
	});

	// DECLARE_MULTICAST_DELEGATE_TwoParams 함수 등록
	multiTwoParamDel.AddUFunction(this, TEXT("MultiTwoParamDel1"));
	multiTwoParamDel.AddUObject(this, &ADelegateStudy::MultiTwoParamDel2);
	multiTwoParamDel.AddLambda([this](int32 num, FString str) -> void {
		UE_LOG(LogTemp, Warning, TEXT("Call multiTwoParamDel by Lambda - %d, %s"), num, *str);
	});
}

// Called every frame
void ADelegateStudy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADelegateStudy::InputTest()
{
	// DECLARE_DELEGATE 에 들어 있는 함수를 호출
	simpleDel.ExecuteIfBound();
	// DECLARE_DELEGATE 에 들어 있는 함수 제거
	simpleDel.Unbind();

	// DECLARE_DELEGATE_OneParam 에 들어 있는 함수를 호출
	simpleOneParamDel.ExecuteIfBound(TEXT("hi!!"));
	// DECLARE_DELEGATE_OneParam 의 함수 제거
	simpleOneParamDel.Unbind();

	// DECLARE_MULTICAST_DELEGATE 에 들어 있는 함수를 호출
	multiDel.Broadcast();
	// DECLARE_MULTICAST_DELEGATE 의 함수 제거
	multiDel.Clear();			// 모두
	//multiDel.RemoveAll(this);	// 자신의 클래스에 있는 함수
	//multiDel.Remove(delHandle);	// 하나만 

	// DECLARE_MULTICAST_DELEGATE_TwoParams 에 들어있는 함수 호출
	multiTwoParamDel.Broadcast(100, TEXT("hello"));
	// DECLARE_MULTICAST_DELEGATE_TwoParams 의 함수 제거
	multiTwoParamDel.Clear();
	//multiTwoParamDel.RemoveAll(this);
	//multiTwoParamDel.Remove( Add 할 당시의 리턴값을 변수에 저장해서 그 변수 )
}

void ADelegateStudy::SimpleDelFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("SimpleDelFunc"));
}

void ADelegateStudy::SimpleOneParamDelFunc(FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("SimpleOneParamDelFunc - %s"), *str);
}

void ADelegateStudy::MultiDel1()
{
	UE_LOG(LogTemp, Warning, TEXT("MultiDel1"));
}

void ADelegateStudy::MultiDel2()
{
	UE_LOG(LogTemp, Warning, TEXT("MultiDel2"));
}

void ADelegateStudy::MultiTwoParamDel1(int32 num, FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("MultiTwoParamDel1 - %d, %s"), num, *str);
}

void ADelegateStudy::MultiTwoParamDel2(int32 num, FString str)
{
	UE_LOG(LogTemp, Warning, TEXT("MultiTwoParamDel2 - %d, %s"), num, *str);
}

