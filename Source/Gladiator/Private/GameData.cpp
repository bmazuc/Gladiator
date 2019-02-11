// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "GameData.h"

void UGameData::SetBGame(bool state)
{
	this->bGame = state;
}

void UGameData::SetBTutorial(bool state)
{
	this->bTutorial = state;
}

bool UGameData::GetBGame()
{
	return this->bGame;
}

bool UGameData::GetBTutorial()
{
	return this->bTutorial;
}


