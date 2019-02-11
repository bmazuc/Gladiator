// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "PlayerTooFarDecorator.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API UPlayerTooFarDecorator : public UBTDecorator
{
	GENERATED_BODY()

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector	targetKey;
};
