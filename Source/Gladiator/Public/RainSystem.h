// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RainSystem.generated.h"

UCLASS()
class GLADIATOR_API ARainSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARainSystem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	UFUNCTION()
		virtual void Tick( float DeltaSeconds ) override;

	auto CheckIfRaining() -> void;
	auto GetIsRaining() -> bool;

private:

	UPROPERTY(EditAnywhere, Category = RainParticle)
		UParticleSystemComponent*	particleSystemComp;
	UPROPERTY(EditAnywhere, Category = RainParameters)
		float	rainingChance = 40.0f;
	UPROPERTY(EditAnywhere, Category = RainParameters)
		float	duration = 10.0f;
	UPROPERTY(VisibleAnywhere, Category = RainParameters)
		bool isRaining = false;
};
