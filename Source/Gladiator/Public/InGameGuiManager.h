// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GuiManager.h"
#include "InGameGuiManager.generated.h"

UCLASS()
class GLADIATOR_API AInGameGuiManager : public AGuiManager
{
	GENERATED_BODY()

public:
	AInGameGuiManager();

	virtual void BeginPlay() override;

	auto GoToWinMenu() -> void;
	auto GoToLoseMenu() -> void;
	auto GoToEndTutorialMenu() -> void;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
		TSubclassOf<UUserWidget> winMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
		TSubclassOf<UUserWidget> loseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
		TSubclassOf<UUserWidget> endTutorialMenu;
};
