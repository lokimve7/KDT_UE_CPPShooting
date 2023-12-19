// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM.h"

// Sets default values for this component's properties
UFSM::UFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...

	
}


// Called every frame
void UFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	currTime += DeltaTime;
	if (currTime > 2)
	{
		state = EState::MOVE;
		UE_LOG(LogTemp, Warning, TEXT("EState::MOVE"));
	}
}

