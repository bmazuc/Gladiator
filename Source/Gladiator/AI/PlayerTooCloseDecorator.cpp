// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "PlayerTooCloseDecorator.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UPlayerTooCloseDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AController * controller = Cast<AController>(OwnerComp.GetOwner());

	if (!controller)
		return false;

	AActor * ai = controller->GetPawn();
	UBlackboardComponent * blackBoard = OwnerComp.GetBlackboardComponent();
	ACharacter * player_character = UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0);

	if (!ai || !blackBoard || !player_character)
		return false;

	FVector player_location = player_character->GetActorLocation();
	FVector my_location = ai->GetActorLocation();
	float distanceClose = blackBoard->GetValueAsFloat(this->targetKey.SelectedKeyName);
	float distance = FVector::Dist(my_location, player_location);

	if (distance < distanceClose)
		return true;
	else
		return false;
}


