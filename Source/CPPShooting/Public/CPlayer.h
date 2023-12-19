// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

UCLASS()
class CPPSHOOTING_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* compBox;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* compMesh;

	//메모리 관리를 하지 않는 기본변수들은 UPROPERTY 를 쓰지 않아도 된다.
	UPROPERTY()
	float h = 0;
	UPROPERTY()
	float v = 0;
	UPROPERTY(EditAnywhere)
	float moveSpeed = 500;

public:
	//사용자 입력을 처리하는 함수
	UFUNCTION()
	void InputHorizontal(float value);

	UFUNCTION()
	void InputVertical(float value);
};
