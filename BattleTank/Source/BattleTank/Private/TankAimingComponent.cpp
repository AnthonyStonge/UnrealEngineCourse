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

	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	
	//First fire after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	
	if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
		//UE_LOG(LogTemp, Warning, TEXT("Firing State : Reloading"));
	}
	else if(IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
		//UE_LOG(LogTemp, Warning, TEXT("Firing State : Aiming"));
	}
	else
	{
		FiringState = EFiringState::Locked;
		//UE_LOG(LogTemp, Warning, TEXT("Firing State : Locked"));
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}


void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!Barrel) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // Vectors are equal
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		//auto Time = GetWorld()->GetTimeSeconds();

		//Use for debug.
		//UE_LOG(LogTemp, Warning, TEXT("%f : Aim solution found"), Time);
	}
	
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretYaw = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretYaw;

	//Use for debug
	UE_LOG(LogTemp, Warning, TEXT("AimAsTurretRotator: %s"), *DeltaRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Turret vector: %s"), *AimAsRotator.ToString());

	Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
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

		if (!ensure(Barrel)) { return; }
		if (!ensure(Projectile_BP)) { return; }
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






