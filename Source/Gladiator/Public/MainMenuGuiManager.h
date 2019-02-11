// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GuiManager.h"
#include "MainMenuGuiManager.generated.h"

UCLASS()
class GLADIATOR_API AMainMenuGuiManager : public AGuiManager
{
	GENERATED_BODY()
	
public:	
	AMainMenuGuiManager();

	virtual void BeginPlay() override;

	auto GoToMainMenu() -> void;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
		TSubclassOf<UUserWidget> mainMenu;
};
