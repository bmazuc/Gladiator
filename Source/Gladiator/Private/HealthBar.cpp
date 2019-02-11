// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "HealthBar.h"


UHealthBar::UHealthBar(const FObjectInitializer& objInit)
	: Super(objInit)
{
}

auto UHealthBar::SetOwner(AEntity* entity) -> void
{
	owner = entity;
}

void UHealthBar::UpdateLife(UProgressBar* health)
{
	if (!owner)
		return;

	float max = (float)owner->GetLifeMax();
	float current = (float)owner->GetLife();
	float result = current / max;

	if (health)
	{
		health->SetPercent(result);
	}
}