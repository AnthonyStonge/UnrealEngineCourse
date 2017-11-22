// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller can't find player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller found tank : %s"), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO Move Towards the player

	//Aim At Player
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

	//Fire when ready
}

/*void ATankAIController::Tick(float deltatime)
{
	UE_LOG(LogTemp, Display,TEXT("Tick works on AI controller")
}*/

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

}



ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}


