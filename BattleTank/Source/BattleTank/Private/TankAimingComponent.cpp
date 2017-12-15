// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true; //TODO Should this really tick?

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//First fire after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	//TODO Handle aiming and locked firing state
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Barrel"));

	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		//auto Time = GetWorld()->GetTimeSeconds();

		//Use for debug.
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found"), Time);
	}
	
}


//TODO void MoveTurretTowards
void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretYaw = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretYaw;

	//Use for debug
	//UE_LOG(LogTemp, Warning, TEXT("AimAsTurretRotator: %s"), *DeltaRotator.ToString());

	Turret->Rotate(DeltaRotator.Yaw);
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelPitch = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelPitch;

	//Use for debug
	//UE_LOG(LogTemp, Warning, TEXT("AimAsBarrelRotator: %s"), *DeltaRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{

		if (!ensure(Barrel && Projectile_BP)) { return; }
		//spawn a projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile_BP,
			Barrel->GetSocketLocation(FName("ProjectileSpawn")),
			Barrel->GetSocketRotation(FName("ProjectileSpawn"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}


}



