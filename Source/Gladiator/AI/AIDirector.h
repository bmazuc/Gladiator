// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "AIDirector.generated.h"

UCLASS()
class GLADIATOR_API AAIDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	AAIDirector();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	auto SpawnEnemies() -> void;
	auto GetAllSpawners() -> TArray<AEnemySpawner*>;
	auto GetAllEnemies() -> TArray<AEnemy*>;
	auto RemoveAllSpawners() -> void;
	auto Attack() -> void;
	auto CancelAttack() -> void;
	auto SpawnRandomEnemy() -> void;
	auto ActivateEnemies(bool) -> void;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void SetAllPassive(bool value = true);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void SetAllGods(bool value = true);

	UPROPERTY(EditAnywhere, Category = Enemy)
		int32 numberOfEnemies = 1;

	UPROPERTY(EditAnywhere, Category = Enemy)
		float timeBeforeAttack = 5.f; //	seconds

private:
	TArray<AEnemySpawner*> spawnerArray;
	TArray<AEnemy*> enemyArray;
	float initialTimeBeforeAttack;
	bool isAllPassive = false;
};
