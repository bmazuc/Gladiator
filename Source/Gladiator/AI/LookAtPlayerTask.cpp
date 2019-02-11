// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "AIController.h"
#include "LookAtPlayerTask.h"

EBTNodeResult::Type ULookAtPlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACharacter * character = (controller) ? Cast<ACharacter>(controller->GetPawn()) : nullptr;

	if (!character || !playerPawn || !controller)
		return EBTNodeResult::Failed;

	FRotator targetRotation = (playerPawn->GetActorLocation() - controller->GetPawn()->GetActorLocation()).Rotation();
	//controller->GetPawn()->SetActorRotation(targetRotation);
	controller->ClientSetRotation(targetRotation);
	controller->StopMovement();

	return EBTNodeResult::Succeeded;
}

