// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "InGameGuiManager.h"
#include "GladiatorGameMode.generated.h"

/*enum class GAMESTATE
{
	NONE = 0,
	RUNNING = 1,
	END = 2
};*/


UCLASS()
class GLADIATOR_API AGladiatorGameMode : public AGameMode
{
	GENERATED_BODY()

public:
		virtual void Tick(float DeltaTime) override;
		auto SetGuiManager(AInGameGuiManager*) -> void;
		auto GetGuiManager()->AInGameGuiManager*;
	
private:
	AInGameGuiManager*	guiManager;
	//GAMESTATE state = GAMESTATE::RUNNING;
};
