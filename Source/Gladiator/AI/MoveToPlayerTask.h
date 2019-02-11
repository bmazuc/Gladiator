// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "MoveToPlayerTask.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UMoveToPlayerTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector	targetKey;
};
