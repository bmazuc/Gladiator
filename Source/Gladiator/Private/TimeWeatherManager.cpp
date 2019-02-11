// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "TimeWeatherManager.h"


// Sets default values
ATimeWeatherManager::ATimeWeatherManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeWeatherManager::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ADirectionalLight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->sun = *ActorItr;

	for (TActorIterator<ASkyLight> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->ambientLight = *ActorItr;

	for (TActorIterator<AAmbientSound> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->ambientSound = *ActorItr;

	for (TActorIterator<ARainSystem> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->rainSystem = *ActorItr;

	if (this->ambientSound)
	{
		this->ambientSound->GetAudioComponent()->SetBoolParameter("isNight", isNight);
		if (this->rainSystem)
			this->ambientSound->GetAudioComponent()->SetBoolParameter("isRaining", this->rainSystem->GetIsRaining());
	}
	if (this->rainSystem)
		this->rainSystem->CheckIfRaining();

}

// Called every frame
void ATimeWeatherManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!this->sun)
		return;

	FRotator rot = FRotator(sunSpeed * DeltaTime, 0, 0);
	this->sun->AddActorLocalRotation(rot);

	FRotator rotComp = this->sun->GetActorRotation();

	this->CheckIfNight(rotComp);
	this->SetIntensity(rotComp);
	this->CheckIfRaining();
}

auto ATimeWeatherManager::CheckIfRaining() -> void
{
	if (isRainingPreviousFrame == this->rainSystem->GetIsRaining())
		return;

	isRainingPreviousFrame = this->rainSystem->GetIsRaining();

	if (this->ambientSound)
		this->ambientSound->GetAudioComponent()->SetBoolParameter("isRaining", this->rainSystem->GetIsRaining());

	if (!this->ambientLight)
		return;

	if (this->rainSystem->GetIsRaining())
		this->ambientLight->GetLightComponent()->SetIntensity(0.75f);
	else
		this->ambientLight->GetLightComponent()->SetIntensity(1.0f);
}

auto ATimeWeatherManager::CheckIfNight(FRotator rot) -> void
{
	if (rot.Pitch <= nightThreshold)
		isNight = false;
	else if (rot.Pitch >= -nightThreshold)
		isNight = true;
}

auto ATimeWeatherManager::SetIntensity(FRotator rot) -> void
{
	if (isNightPreviousFrame != isNight)
	{
		if (this->ambientSound)
			this->ambientSound->GetAudioComponent()->SetBoolParameter("isNight", isNight);
		isNightPreviousFrame = isNight;

		if (isNight && this->sun)
			this->sun->GetLightComponent()->SetIntensity(0.0f);
	}

	float intensity = 0.0f;

	if (!isNight)
	{
		intensity = sunIntensity * (rot.Pitch / -sunZenith);
		if (this->sun)
			sun->GetLightComponent()->SetIntensity(intensity);
	}
}