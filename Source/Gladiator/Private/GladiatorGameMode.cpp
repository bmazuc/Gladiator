// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "BasePlayer.h"
#include "GladiatorGameMode.h"


void AGladiatorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ABasePlayer* player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

auto AGladiatorGameMode::SetGuiManager(AInGameGuiManager* currentGuiManager) -> void
{
	this->guiManager = currentGuiManager;
}

auto AGladiatorGameMode::GetGuiManager()->AInGameGuiManager*
{
	return this->guiManager;
}