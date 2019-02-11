 // Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "Enemy.h"
#include "AttackTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = Cast<AEnemy>(controller->GetPawn());
	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	float distance = FVector::Dist(playerPawn->GetActorLocation(), enemy->GetActorLocation());

	if (distance >= this->closeCombatDistance)
	{
		enemy->isAttacking = false;
		return EBTNodeResult::Failed;
	}

	enemy->isAttacking = true;

	return EBTNodeResult::Succeeded;
}


