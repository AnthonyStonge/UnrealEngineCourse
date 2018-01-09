// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

/*
 *
 *
 *		Enum for aiming state
 *
 *
 */
UENUM()
enum class EFiringState : uint8
{
	Locked	 UMETA(DisplayName = "Locked"),
	Aiming	 UMETA(DisplayName = "Aiming"),
	Reloading	 UMETA(DisplayName = "Reloading")
};

/*
 *
 *		Forward declaration
 *
 */
class UTankBarrel; 
class UTankTurret;
class AProjectile;

/*
 *
 *		Class
 *		Hold's barrel property and elevate method
 *
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Firing")
		float LaunchSpeed = 10000; //TODO Find a sensible default 

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile>Projectile_BP;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	FVector AimDirection;

	double LastFireTime = 0;

};
