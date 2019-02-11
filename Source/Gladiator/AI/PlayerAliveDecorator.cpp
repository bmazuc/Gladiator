// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "BasePlayer.h"
#include "PlayerAliveDecorator.h"

bool UPlayerAliveDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	ABasePlayer * player = playerPawn ? Cast<ABasePlayer>(playerPawn) : nullptr;

	if (!player)
		return false;
	else if (player->life <= 0)
		return false;
	else
		return true;
}


