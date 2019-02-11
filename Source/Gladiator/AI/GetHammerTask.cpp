// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "GetHammerTask.h"
#include "AIController.h"
#include "Enemy.h"
#include "Weapon.h"

EBTNodeResult::Type UGetHammerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = Cast<AEnemy>(controller->GetPawn());
	const AWeapon * targetHammer = enemy->GetHammer();
	const float distanceMin = 20.f;
	float distanceToWeapon = FVector::Dist(enemy->GetActorLocation(), targetHammer->GetActorLocation());

	enemy->isPicking = true;

	if (distanceToWeapon > distanceMin)
	{
		controller->MoveToLocation(targetHammer->GetActorLocation());
		enemy->isPicking = true;
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Succeeded;
}


