// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "InGameGuiManager.h"
#include "BasePlayer.h"
#include "AI/AIDirector.h"
#include "Runtime/Engine/Classes/Sound/AmbientSound.h"
#include "Matinee/MatineeActor.h"
#include "GladiatorGameState.generated.h"

enum class GAMESTATE
{
	INTRO = 0,
	GAME,
	TUTORIAL,
	END
};

UCLASS()
class GLADIATOR_API AGladiatorGameState : public AGameState
{
	GENERATED_BODY()

public:
	AGladiatorGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	auto IntroTick(float DeltaTime) -> void;
	auto RunningTick(float DeltaTime) -> void;
	auto TutorialTick(float DeltaTime) -> void;

	auto CheckIfWin() -> void;
	auto CheckIfLose() -> void;

	auto GetGuiManager() -> AInGameGuiManager*;

	UFUNCTION(BlueprintCallable, Category = Getter)
		AAIDirector * GetAIDirector();
private:
	ABasePlayer*		player;
	AInGameGuiManager*	inGameGuiManager;
	AAIDirector*		aiDirector;
	AAmbientSound*		ambientSound;
	TArray<AMatineeActor*>	cinematics;
	GAMESTATE			state = GAMESTATE::INTRO;
};
