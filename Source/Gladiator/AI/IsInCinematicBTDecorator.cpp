// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "IsInCinematicBTDecorator.h"


bool UIsInCinematicBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = Cast<AEnemy>(controller->GetPawn());

	return !enemy->IsInCinematic();
}