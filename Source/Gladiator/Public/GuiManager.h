// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "GuiManager.generated.h"

UCLASS()
class GLADIATOR_API AGuiManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGuiManager();

	virtual void BeginPlay() override;

protected:

	auto ChangeMenuWidget(TSubclassOf<UUserWidget>) -> void;
	auto DisplayCursor(bool) -> void;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Menus")
		TSubclassOf<UUserWidget> startingMenu;

	UUserWidget* currentMenu;

	APlayerController* playerCtrl;	
};
