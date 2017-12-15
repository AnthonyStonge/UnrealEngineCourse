// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:

	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override; //Needed for BP BeginPlay to work!

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000; //TODO Find a sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile>Projectile_BP;

	
	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; //TODO REMOVE THIS LINE

	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;
};
