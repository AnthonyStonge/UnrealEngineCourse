// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	//How can the AI get close to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup") //Consider EditDefaultOnly
		float AcceptanceRadius = 8000;

private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Gets called the when the pawn is possessed
	virtual void SetPawn(APawn* InPawn) override;

	void AimTowardsCrosshair();

	UFUNCTION()
		void OnPossessedTankDeath();

};
