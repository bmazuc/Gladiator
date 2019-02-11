// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "InGameGuiManager.h"

AInGameGuiManager::AInGameGuiManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInGameGuiManager::BeginPlay()
{
	Super::BeginPlay();
	this->DisplayCursor(false);
}

auto AInGameGuiManager::GoToWinMenu() -> void
{
	if (winMenu)
		ChangeMenuWidget(winMenu);
}

auto AInGameGuiManager::GoToLoseMenu() -> void
{
	if (loseMenu)
		ChangeMenuWidget(loseMenu);
}

auto AInGameGuiManager::GoToEndTutorialMenu() -> void
{
	if (endTutorialMenu)
		ChangeMenuWidget(endTutorialMenu);
}