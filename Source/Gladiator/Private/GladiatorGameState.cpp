// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "GameData.h"
#include "GladiatorGameState.h"

AGladiatorGameState::AGladiatorGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGladiatorGameState::BeginPlay()
{
	Super::BeginPlay();

	this->player = Cast<ABasePlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	for (TActorIterator<AInGameGuiManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->inGameGuiManager = *ActorItr;
	for (TActorIterator<AAIDirector> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->aiDirector = *ActorItr;
	for (TActorIterator<AAmbientSound> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->ambientSound = *ActorItr;
	for (TActorIterator<AMatineeActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		this->cinematics.Add(*ActorItr);

	UGameData* data = Cast<UGameData>(GetGameInstance());
	if (data->GetBGame())
		this->state = GAMESTATE::INTRO;
	else if (data->GetBTutorial())
		this->state = GAMESTATE::TUTORIAL;
}

void AGladiatorGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch(this->state)
	{
		case GAMESTATE::INTRO: 
		{ 
			this->IntroTick(DeltaTime); 
		} 
		break;

		case GAMESTATE::GAME:
		{
			this->RunningTick(DeltaTime);
		}
		break;

		case GAMESTATE::TUTORIAL:
		{
			this->TutorialTick(DeltaTime);
		}
		break;

		default:
			break;
	}
}

auto AGladiatorGameState::IntroTick(float DeltaTime) -> void
{
	if (!this->player->IsInCinematic())
	{
		this->state = GAMESTATE::GAME;
		this->aiDirector->ActivateEnemies(false);
	}
}

auto AGladiatorGameState::RunningTick(float DeltaTime) -> void
{
	if (!this->player)
		return;

	this->CheckIfLose();
	this->CheckIfWin();
}

auto AGladiatorGameState::TutorialTick(float DeltaTime) -> void
{
	if (!this->player)
		return;

	TArray<AEnemy*> enemies = this->aiDirector->GetAllEnemies();
	int currentLife = this->player->GetLife();
	if (currentLife <= 0 || enemies.Max() == 0 && this->inGameGuiManager)
	{
		this->state = GAMESTATE::END;
		this->cinematics[0]->Play();
		this->player->SetIsInCinematic(true);
		this->player->isAttacking = false;
		this->inGameGuiManager->GoToEndTutorialMenu();
		this->ambientSound->Stop();
		this->ambientSound->Play();
		if (currentLife <= 0)
			this->ambientSound->GetAudioComponent()->SetBoolParameter("hasWin", false);
		else
			this->ambientSound->GetAudioComponent()->SetBoolParameter("hasWin", true);
	}
}

auto AGladiatorGameState::CheckIfWin() -> void
{
	if (this->state == GAMESTATE::END)
		return;

	TArray<AEnemy*> enemies = this->aiDirector->GetAllEnemies();

	if (enemies.Max() == 0)
	{
		this->state = GAMESTATE::END;
		this->cinematics[1]->Play();
		this->inGameGuiManager->GoToWinMenu();
		this->ambientSound->Stop();
		this->ambientSound->Play();
		this->ambientSound->GetAudioComponent()->SetBoolParameter("hasWin", true);
	}
}

auto AGladiatorGameState::CheckIfLose() -> void
{
	int currentLife = this->player->GetLife();
	if (currentLife <= 0 && this->inGameGuiManager)
	{
		this->state = GAMESTATE::END;
		this->cinematics[1]->Play();
		this->inGameGuiManager->GoToLoseMenu();
		this->ambientSound->Stop();
		this->ambientSound->Play();
		this->ambientSound->GetAudioComponent()->SetBoolParameter("hasWin", false);
	}
}

auto AGladiatorGameState::GetGuiManager()->AInGameGuiManager*
{
	return this->inGameGuiManager;
}

auto AGladiatorGameState::GetAIDirector()->AAIDirector*
{
	return this->aiDirector;
}