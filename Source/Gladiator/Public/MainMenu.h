// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = MainMenu)
		void LaunchGame();
	UFUNCTION(BlueprintCallable, Category = MainMenu)
		void LaunchTutorial();
	UFUNCTION(BlueprintCallable, Category = MainMenu)
		void QuitGame();	
};
