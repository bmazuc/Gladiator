 #pragma once

#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GLADIATOR_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	auto SpawnEnemy() ->AEnemy*;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enemy)
		TSubclassOf<AEnemy> enemyBlueprint;

private:
	USceneComponent * rootScene;
	TArray<AEnemy*> enemiesArray;
};
