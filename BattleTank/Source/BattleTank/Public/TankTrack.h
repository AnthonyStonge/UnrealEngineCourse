// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank track is used to set maximum driving force, and apply force to the tank.
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 
	//Sets a throttle between -1 and +1, changeable in GameSettings - InputSettings
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	

	//Max force per track, in newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000; //Assume 40 tons tank, and 1g acceleration

private:
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;

};
