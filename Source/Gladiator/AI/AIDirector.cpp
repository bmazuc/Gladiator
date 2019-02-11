#include "Gladiator.h"
#include "AIDirector.h"
#include "EngineUtils.h"

AAIDirector::AAIDirector()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIDirector::BeginPlay()
{
	Super::BeginPlay();
	this->GetAllSpawners();
	this->SpawnEnemies();
	this->initialTimeBeforeAttack = this->timeBeforeAttack;
}

void AAIDirector::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	this->timeBeforeAttack -= DeltaTime;

	if (this->timeBeforeAttack <= 0.f)
	{
		this->Attack();
		this->timeBeforeAttack = this->initialTimeBeforeAttack;
	}
}

void AAIDirector::SetAllGods(bool value)
{
	for (TActorIterator<AEnemy> iterator(this->GetWorld()); iterator; ++iterator)
		iterator->SetGodMode(value);
}

void AAIDirector::SetAllPassive(bool value)
{
	for (TActorIterator<AEnemy> iterator(this->GetWorld()); iterator; ++iterator)
		iterator->SetPassive(false);
}

auto AAIDirector::SpawnEnemies() -> void
{
	for (int32 i = 0; i < this->numberOfEnemies; ++i)
		this->SpawnRandomEnemy();
}

auto AAIDirector::GetAllSpawners() -> TArray<AEnemySpawner*>
{
	this->spawnerArray.Empty();

	for (TActorIterator<AEnemySpawner> iterator(this->GetWorld()); iterator; ++iterator)
	{
		this->spawnerArray.Add(*iterator);
	}
	return this->spawnerArray;
}

auto AAIDirector::GetAllEnemies() -> TArray<AEnemy*>
{
	this->enemyArray.Empty();

	for (TActorIterator<AEnemy> iterator(this->GetWorld()); iterator; ++iterator)
		if (!iterator->isDead)
			this->enemyArray.Add(*iterator);
	
	return this->enemyArray;
}

auto AAIDirector::RemoveAllSpawners() -> void
{
	for (int32 i = 0; i != this->spawnerArray.Num(); ++i)
		this->spawnerArray[i]->Destroy();

	this->spawnerArray.Empty();
}

auto AAIDirector::Attack() -> void
{
	this->CancelAttack();

	int32 numberOfEnemies = this->enemyArray.Num();

	if (numberOfEnemies <= 0)
		return;

	int32 theChoosenOne = FMath::RandRange(0, this->enemyArray.Num() - 1);

	if (!enemyArray[theChoosenOne]->GetCharacterMovement()->IsMovingOnGround() || !enemyArray[theChoosenOne]->HasHammer() || enemyArray[theChoosenOne]->isPassive)
	{
		this->enemyArray[theChoosenOne]->attackPhase = false;
		return;
	}
	 
	this->enemyArray[theChoosenOne]->attackPhase = true;
}

auto AAIDirector::CancelAttack() -> void
{
	this->GetAllEnemies();

	for (int32 i = 0; i < this->enemyArray.Num() - 1; ++i)
	{
		this->enemyArray[i]->isAttacking = false;
		this->enemyArray[i]->attackPhase = false;
	}
}

auto AAIDirector::SpawnRandomEnemy() -> void
{
	int32 numberOfSpawners = this->spawnerArray.Num();

	if (numberOfSpawners <= 0)
		return;

	int32 randomSpawn = FMath::RandRange(0, numberOfSpawners - 1);
	this->enemyArray.Add(this->spawnerArray[randomSpawn]->SpawnEnemy());
}

auto AAIDirector::ActivateEnemies(bool state) -> void
{
	for (int32 i = 0; i < this->enemyArray.Num(); ++i)
		this->enemyArray[i]->SetIsInCinematic(state);
}