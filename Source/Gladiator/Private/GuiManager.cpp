// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "GuiManager.h"


AGuiManager::AGuiManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGuiManager::BeginPlay()
{
	playerCtrl = GetWorld()->GetFirstPlayerController();
	ChangeMenuWidget(startingMenu);
}

auto AGuiManager::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidget) -> void
{
	if (currentMenu != nullptr)
	{
		currentMenu->RemoveFromViewport();
		currentMenu = nullptr;
		this->DisplayCursor(false);
	}

	if (NewWidget != nullptr)
	{
		currentMenu = CreateWidget<UUserWidget>(GetWorld(), NewWidget);
		if (currentMenu != nullptr)
		{
			currentMenu->AddToViewport();
			this->DisplayCursor(true);
		}
	}
}

auto AGuiManager::DisplayCursor(bool state) -> void
{
	playerCtrl->bShowMouseCursor = state;
}