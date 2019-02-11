// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "AvoidEnemyTask.h"
#include "BasePlayer.h"
#include "Enemy.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UAvoidEnemyTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	AEnemy * enemy = controller ? Cast<AEnemy>(controller->GetPawn()) : nullptr;

	if (!enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "FAILED TO FIND ENEMY");
		return EBTNodeResult::Failed;
	}

	FVector targetLocation =  controller->GetPawn()->GetActorLocation() + controller->GetPawn()->GetActorLocation().RightVector * 150.f;
	controller->GetCharacter()->LaunchCharacter(controller->GetPawn()->GetActorLocation().RightVector * enemy->speed, false, false);

	return EBTNodeResult::Succeeded;
}


