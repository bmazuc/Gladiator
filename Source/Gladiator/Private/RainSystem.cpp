// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "RainSystem.h"


// Sets default values
ARainSystem::ARainSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	particleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("particleSystemComp");
	particleSystemComp->SetupAttachment(RootComponent);
	particleSystemComp->bAllowRecycling = true;
}

// Called when the game starts or when spawned
void ARainSystem::BeginPlay()
{
	Super::BeginPlay();
	particleSystemComp->DeactivateSystem();

	FTimerHandle checkTimerHandle;
	GetWorldTimerManager().SetTimer(checkTimerHandle, this, &ARainSystem::CheckIfRaining, duration, true);
}

// Called every frame
void ARainSystem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

auto ARainSystem::CheckIfRaining() -> void
{
	int rain = FMath::RandRange(1, 100);

	if (rain <= this->rainingChance)
	{
		particleSystemComp->ActivateSystem();
		isRaining = true;
	}
	else
	{
		particleSystemComp->DeactivateSystem();
		isRaining = false;
	}
}

auto ARainSystem::GetIsRaining() -> bool
{
	return isRaining;
}