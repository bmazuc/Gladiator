// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "HUDMenu.h"

UHUDMenu::UHUDMenu(const FObjectInitializer& objInit)
	: Super(objInit)
{
	player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

void UHUDMenu::UpdateLife(UProgressBar* health)
{
	if (!player)
		return ;

	float max = (float)player->GetLifeMax();
	float current = (float)player->GetLife();
	float result = current / max;
	
	if (health)
	{
		health->SetPercent(result);
	}
}