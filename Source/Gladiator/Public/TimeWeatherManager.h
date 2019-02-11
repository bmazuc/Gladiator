// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Runtime/Engine/Classes/Sound/AmbientSound.h"
#include "RainSystem.h"
#include "TimeWeatherManager.generated.h"

UCLASS()
class GLADIATOR_API ATimeWeatherManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeWeatherManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	auto CheckIfNight(FRotator) -> void;
	auto SetIntensity(FRotator) -> void;
	auto CheckIfRaining() -> void;

	ADirectionalLight*		sun;
	ASkyLight*				ambientLight;
	AAmbientSound*			ambientSound;
	ARainSystem*			rainSystem;

	UPROPERTY(EditAnywhere, Category = Time)
		float sunSpeed = 30.0f;
	UPROPERTY(VisibleAnywhere, Category = Time)
		float sunZenith = 90.0f;
	UPROPERTY(EditAnywhere, Category = Time)
		float sunIntensity = 3.141593f;
	UPROPERTY(EditAnywhere, Category = Time)
		bool isNight = false;
	UPROPERTY(VisibleAnywhere, Category = Time)
		bool isNightPreviousFrame = false;
	UPROPERTY(EditAnywhere, Category = Time)
		float nightThreshold = 1.0f;
	UPROPERTY(EditAnywhere, Category = Rain)
		bool isRaining = false;
	bool isRainingPreviousFrame = false;
};
