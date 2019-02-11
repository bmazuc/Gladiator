// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "Enemy.h"
#include "AIController.h"
#include "GetAwayFromPlayerTask.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UGetAwayFromPlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	AAIController * controller = Cast<AAIController>(OwnerComp.GetOwner());
	ACharacter * character = (controller) ? Cast<ACharacter>(controller->GetPawn()) : nullptr;

	if (!character || !playerPawn || !controller)
		return EBTNodeResult::Failed;

	AEnemy * enemy = Cast<AEnemy>(character);
	FVector targetLocation = character->GetActorLocation() + UKismetMathLibrary::GetForwardVector(character->GetActorRotation()) * -150.f;
	FRotator targetRotation = (playerPawn->GetActorLocation() - controller->GetPawn()->GetActorLocation()).Rotation();

	UWorld * world = this->GetWorld();
	FCollisionQueryParams traceParameters(FName(TEXT("AITraceBackward")));
	FVector startLocation = character->GetActorLocation() + UKismetMathLibrary::GetForwardVector(character->GetActorRotation()) * -100.f;
	FVector endLocation = character->GetActorLocation() + UKismetMathLibrary::GetForwardVector(character->GetActorRotation()) * -150.f;
	FHitResult hitResult;

	if (!world->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_WorldStatic, traceParameters) && !enemy->IsAvoidingEnemy())
	{
		controller->MoveToLocation(targetLocation);
	}

	controller->ClientSetRotation(targetRotation);

	return EBTNodeResult::Succeeded;
}



