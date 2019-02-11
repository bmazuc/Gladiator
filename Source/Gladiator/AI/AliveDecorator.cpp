// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "AliveDecorator.h"
#include "AIController.h"
#include "Enemy.h"

bool UAliveDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = Cast<AEnemy>(controller->GetPawn());
	bool result = enemy->isDead ? false : true;

	return result;
}



