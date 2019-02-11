// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "AttackPhaseDecorator.h"
#include "AIController.h"
#include "Enemy.h"
	
bool UAttackPhaseDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent * blackBoard = OwnerComp.GetBlackboardComponent();
	//bool result = blackBoard->GetValueAsBool(this->targetKey.SelectedKeyName);
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = Cast<AEnemy>(controller->GetPawn());
	bool result = enemy->attackPhase;

	return result;
}


