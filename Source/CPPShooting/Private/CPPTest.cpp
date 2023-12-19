// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPTest.h"
#include "FSM.h"

class TestBase
{
public:
	TestBase()
	{
		UE_LOG(LogTemp, Warning, TEXT("TestBase 생성자"));
	}

	virtual void PrintMyName()
	{
		UE_LOG(LogTemp, Warning, TEXT("나의 이름은 TestBase"));
	}


public:
	int score = 10;
};

class TestA : public TestBase
{
public:
	TestA()
	{
		UE_LOG(LogTemp, Warning, TEXT("TestA 생성자"));			
	}

	virtual void PrintMyName() override
	{
		UE_LOG(LogTemp, Warning, TEXT("나의 이름은 TestA"));
	}


public:
	int myAge = 27;
};

class TestB : public TestBase
{
public:
	TestB()
	{
		UE_LOG(LogTemp, Warning, TEXT("TestB 생성자"));
	}

	virtual void PrintMyName() override
	{
		UE_LOG(LogTemp, Warning, TEXT("나의 이름은 TestB"));
	}
};




// Sets default values
ACPPTest::ACPPTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fsm = CreateDefaultSubobject<UFSM>(TEXT("FSM"));
}

// Called when the game starts or when spawned
void ACPPTest::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Hello World CPP"));
	//UE_LOG(LogTemp, Warning, TEXT("number1의 값은 %d 이다. %.2f"), 100, 111.5f);
	//UE_LOG(LogTemp, Warning, TEXT("나의 이름은 %s"), *myName);

	//int32 returnValue = Plus(123, 456);

	//TestA 클래스 만들자
	TestA* pA = new TestA();
	pA->PrintMyName();

	TestBase* pBase = pA;
	pBase->PrintMyName();


	//TestB 클래스 만들자
	TestB* pB = new TestB();

	TestBase* array = new TestBase[2];
	
	array[0] = *pA;
	array[1] = *pB;

	array[0].PrintMyName();
	array[1].PrintMyName();


	delete pA;
	delete pB;
}

// Called every frame
void ACPPTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
}

/*

반환자료형 함수이름([매개변수1, 매개변수2.....])
{
	To Do..

	[return 반환값;]
}

*/


int32 ACPPTest::Plus(int32 num1, int32 num2)
{
	int32 result = num1 + num2;
	UE_LOG(LogTemp, Warning, TEXT("합의 결과 : %d"), result);
	return result;

}



