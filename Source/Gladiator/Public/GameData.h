// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "GameData.generated.h"

/**
	Class for data stocking;
 */
UCLASS()
class GLADIATOR_API UGameData : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Data)
		void SetBGame(bool state);
	UFUNCTION(BlueprintCallable, Category = Data)
		void SetBTutorial(bool state);

	UFUNCTION(BlueprintCallable, Category = Data)
		bool GetBGame();
	UFUNCTION(BlueprintCallable, Category = Data)
		bool GetBTutorial();
	
private:
	bool bGame		= false;
	bool bTutorial	= false;
};
