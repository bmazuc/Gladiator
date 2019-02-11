// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "EndMenu.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UEndMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = EndMenu)
		void Retry();
	
	UFUNCTION(BlueprintCallable, Category = EndMenu)
		void Quit();
};
