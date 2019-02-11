// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "BasePlayer.h"
#include "HUDMenu.generated.h"


UCLASS()
class GLADIATOR_API UHUDMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHUDMenu(const FObjectInitializer&);
	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateLife(UProgressBar* health);

protected:
	ABasePlayer* player;
	
};
