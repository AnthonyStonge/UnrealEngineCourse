// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeedRotation)
{
	auto RotationChange = FMath::Clamp<float>(RelativeSpeedRotation ,-1.0, 1.0) * MaxDregreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator( 0, RawNewRotation, 0));
}

