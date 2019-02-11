// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Entity.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATOR_API AEnemy : public AEntity
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	auto MoveToPlayer() -> void;
	auto MoveToTarget(FVector) -> void;
	auto UpdateRotation() -> void;
	auto AvoidEnemy() -> void;
	auto IsAvoidingEnemy() -> const bool { return this->isAvoidingEnemy; }

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void SetPassive(bool value = true) { this->isPassive = value; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters)
		float speed;
	UPROPERTY(EditAnywhere, Category = Parameters)
		bool isPassive = false;
	UPROPERTY(EditAnywhere, Category = Parameters)
		float distanceToPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool attackPhase;

private:
	bool isAvoidingEnemy = false;
};
