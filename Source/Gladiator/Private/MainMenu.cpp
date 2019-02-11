// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MainMenu.h"
#include "GameData.h"
#include "GladiatorGameState.h"

void UMainMenu::LaunchGame()
{
	if (GEngine->GetWorld() != nullptr && GEngine->GetWorld()->GetGameInstance() != nullptr)
	{
		UGameData* gameData = Cast<UGameData>(GEngine->GetWorld()->GetGameInstance());
		gameData->SetBGame(true);
		gameData->SetBTutorial(false);
	}
	UGameplayStatics::OpenLevel(GetWorld(), "scene");
}

void UMainMenu::LaunchTutorial()
{
	if (GEngine->GetWorld() != nullptr && GEngine->GetWorld()->GetGameInstance() != nullptr)
	{
		UGameData* gameData = Cast<UGameData>(GEngine->GetWorld()->GetGameInstance());
		gameData->SetBTutorial(true);
		gameData->SetBGame(false);
	}
	UGameplayStatics::OpenLevel(this->GetWorld(), "Tutorial");
}

void UMainMenu::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}