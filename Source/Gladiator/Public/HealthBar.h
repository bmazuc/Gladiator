// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "Entity.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()


public:
	UHealthBar(const FObjectInitializer&);
	auto SetOwner(AEntity*) -> void;
	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateLife(UProgressBar* health);

protected:
	AEntity*	owner;
};
