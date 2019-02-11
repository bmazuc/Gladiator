// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "PlayerTooCloseDecorator.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UPlayerTooCloseDecorator : public UBTDecorator
{
	GENERATED_BODY()

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector	targetKey;
};
