// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MainMenuGuiManager.h"


// Sets default values
AMainMenuGuiManager::AMainMenuGuiManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainMenuGuiManager::BeginPlay()
{
	Super::BeginPlay();	
}

auto AMainMenuGuiManager::GoToMainMenu() -> void
{
	ChangeMenuWidget(mainMenu);
}