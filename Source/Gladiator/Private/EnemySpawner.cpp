#include "Gladiator.h"
#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	this->rootScene = CreateDefaultSubobject<USceneComponent>("SceneComp");

	RootComponent = rootScene;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

auto AEnemySpawner::SpawnEnemy() -> AEnemy*
{
	auto new_enemy = this->GetWorld()->SpawnActor(this->enemyBlueprint);

	if (!new_enemy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "ERROR TO SPAWN ENNEMY");
		return nullptr;
	}

	new_enemy->SetActorLocation(this->GetActorLocation());

	return Cast<AEnemy>(new_enemy);
}

