// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0) * MaxDregreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	

	SetRelativeRotation(FRotator((FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees)), 0, 0));
}

