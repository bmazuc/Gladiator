// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "MoveToPlayerTask.h"
#include "AIController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMoveToPlayerTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACharacter * character = (controller) ? Cast<ACharacter>(controller->GetPawn()) : nullptr;
	AEnemy * enemy = Cast<AEnemy>(controller);

	if (!character || !playerPawn || !controller) 
		return EBTNodeResult::Failed;

	FRotator targetRotation = (playerPawn->GetActorLocation() - controller->GetPawn()->GetActorLocation()).Rotation();
	targetRotation.Pitch = 0.f;
	controller->GetPawn()->SetActorRotation(targetRotation);
	controller->MoveToActor(playerPawn);

	return EBTNodeResult::Succeeded;
}
