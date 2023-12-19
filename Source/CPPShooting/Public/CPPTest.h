// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPPTest.generated.h"



UCLASS()
class CPPSHOOTING_API ACPPTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPPTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//VisibleAnywhere		: 어디서든 볼 수 있게 하자
	//VisibleInstanceOnly	: 월드에 배치한 클래스에서만 볼 수 있게
	//VisibleDefaultsOnly	: 블루프린트 앙에서만 볼 수 있게
	
	//EditAnywhere			: 어디서든 수정 할 수 있게 하자
	//EditInstanceOnly		: 월드에 배치한 클래스에서만 수정할 수 있게
	//EditDefaultsOnly		: 블루프린트 창에서만 수정할 수 있게

	//BlueprintReadWrite	: 해당 변수를 블루프린트에서 Get / Set 으로 사용할 수 있다
	//BlueprintReadOnly		: 해당 변수를 블루프린트에서 Get 으로 사용할 수 있다

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 number1 = 10;

	FString myName = TEXT("김현진");

	UPROPERTY()
	ACPPTest* myClass;
		
	//BlueprintCallable		: 블루프린트에서 함수를 호출 할 수 있게 (with 실행핀)
	//BlueprintPure			: 불루프린트에서 함수를 호출 할 수 있게 (실행핀 없는!)
	UFUNCTION(BlueprintPure)
	int32 Plus(int32 num1, int32 num2);

	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFSM* fsm;
};
