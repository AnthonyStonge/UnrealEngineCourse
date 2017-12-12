// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());


	if (PlayerTank)
	{
		//TODO check acceptance radius
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim At Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire when ready
		ControlledTank->Fire(); //TODO Do not fire every frame, limit the firing rate

	}
}




