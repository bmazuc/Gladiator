// Fill out your copyright notice in the Description page of Project Settings.

#include "Gladiator.h"
#include "AIController.h"
#include "WidgetComponent.h"
#include "HealthBar.h"
#include "Enemy.h"
#include "BasePlayer.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	this->Controller->GetCharacter()->GetCharacterMovement()->SetAvoidanceEnabled(true);

	UWidgetComponent* widgetComp = this->FindComponentByClass<UWidgetComponent>();
	if (!widgetComp)
		return;

	UHealthBar* healthBar = Cast<UHealthBar>(widgetComp->GetUserWidgetObject());
	if (!healthBar)
		return;

	healthBar->SetOwner(this);
}

auto AEnemy::MoveToPlayer() -> void
{

}

auto AEnemy::MoveToTarget(FVector position) -> void
{

}

void AEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UWorld * world = this->GetWorld();
	FCollisionQueryParams traceParameters(FName(TEXT("AITrace")));

	APawn * playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	FVector startLocation = this->GetActorLocation() + UKismetMathLibrary::GetForwardVector(this->GetActorRotation()) * 150.f;
	FVector endLocation = this->GetActorLocation() + UKismetMathLibrary::GetForwardVector(this->GetActorRotation()) * 300.f;
	FRotator targetRotation = (playerPawn->GetActorLocation() - this->GetActorLocation()).Rotation();
	FHitResult hitResult;

	if (world->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_WorldStatic, traceParameters))
	{
		if (hitResult.GetActor()->GetClass()->IsChildOf(AEnemy::StaticClass()))
		{
			this->isAvoidingEnemy = true;
		}
		else
			this->isAvoidingEnemy = false;
	}
	else
		this->isAvoidingEnemy = false;

	if (this->hasHisHammer && this->hasHisShield && !this->isDead)
		this->GetController()->ClientSetRotation(targetRotation);
}

auto AEnemy::AvoidEnemy() -> void
{
	FVector leftDirection = this->GetActorLocation() + (UKismetMathLibrary::GetRightVector(this->GetActorRotation()) * -1.f) * 150.f;
	FVector rightDirection = this->GetActorLocation() + UKismetMathLibrary::GetRightVector(this->GetActorRotation()) * 150.f;

	bool randomResult = FMath::RandBool();
	FVector directionResult = randomResult ? leftDirection : rightDirection;
	AAIController * controller = Cast<AAIController>(this->GetOwner());

	if (controller)
		controller->MoveToLocation(leftDirection);
}