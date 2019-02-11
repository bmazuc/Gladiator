// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "EnemyForwardDecorator.h"

#include "AIController.h"
#include "Enemy.h"

bool UEnemyForwardDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = Cast<AEnemy>(controller->GetPawn());

	if (!enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "FAILED TO FIND ENEMY");
		return false;
	}

	return enemy->IsAvoidingEnemy();
}

