#include "Gladiator.h"
#include "BasePlayer.h"
#include "EngineUtils.h"

ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}

ABasePlayer::~ABasePlayer()
{}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AAIDirector> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		AiDirector = *ActorItr;

	for (TActorIterator<ACameraActor> camItr(GetWorld()); camItr; ++camItr)
		camera = *camItr;
}

auto ABasePlayer::LockThePrev() ->void
{
	TArray<AEnemy*> enemies = AiDirector->GetAllEnemies();

	if (enemies.Num() <= 1)
		return;

	int idx = 0;
	int size = enemies.Num();
	enemyLocked->bodyMesh->SetRenderCustomDepth(false);
	for (int i = 0; i < size; ++i)
	{
		if (enemies[i] == enemyLocked)
		{
			idx = i - 1;

			if (idx > 0)
			{
				enemyLocked = enemies[idx];
				break;
			}
			else
			{
				enemyLocked = enemies[size - 1];
				break;
			}
		}
	}
	enemyLocked->bodyMesh->SetRenderCustomDepth(true);
	LookAt(enemyLocked, 1.0f);
}

auto ABasePlayer::LockTheNext() ->void
{
	TArray<AEnemy*> enemies = AiDirector->GetAllEnemies();

	if (enemies.Num() <= 1)
		return;
	
	int idx = 0;
	int size = enemies.Num();
	enemyLocked->bodyMesh->SetRenderCustomDepth(false);
	for (int i = 0; i < size; ++i)
	{
		if (enemies[i] == enemyLocked)
		{
			idx = i + 1;

			if (idx < size)
			{
				enemyLocked = enemies[idx];
				break;
			}
			else
			{
				enemyLocked = enemies[0];
				break;
			}
		}
	}
	enemyLocked->bodyMesh->SetRenderCustomDepth(true);
}

auto ABasePlayer::LockTheClosestEnemy() ->void
{
	TArray<AEnemy*> enemies = AiDirector->GetAllEnemies();

	if (enemies.Num() < 1)
		return;

	AEnemy* theClosest = enemies[0];
	float distance = (theClosest->GetActorLocation() - GetActorLocation()).Size();

	for (int i = 1; i < enemies.Num(); ++i)
	{
		float newDistance = (enemies[i]->GetActorLocation() - GetActorLocation()).Size();
		if (newDistance < distance)
		{
			theClosest = enemies[i];
		}
	}
	enemyLocked = theClosest;
	enemyLocked->bodyMesh->SetRenderCustomDepth(true);
}

void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateRotation(DeltaTime);

	if (enemyLocked)
	{
		if (!enemyLocked->isDead)
		{
			LookAt(enemyLocked, 1.0f);
			FRotator TargetRotation = (enemyLocked->GetActorLocation() - GetActorLocation()).Rotation();
			TargetRotation.Pitch = 0.0f;
			
			FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationInterpSpeed);
			GetController()->SetControlRotation(SmoothRotation);
		}
		else
		{
			enemyLocked->bodyMesh->SetRenderCustomDepth(false);
			LookAtTarget = nullptr;
			enemyLocked = nullptr;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			isLocked = false;
		}
		
	}

}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveVertical", this, &ABasePlayer::MoveVertical);
	InputComponent->BindAxis("MoveHorizontal", this, &ABasePlayer::MoveHorizontal);
	InputComponent->BindAxis("MouseVertical", this, &ABasePlayer::MouseVertical);
	InputComponent->BindAxis("MouseHorizontal", this, &ABasePlayer::MouseHorizontal);
	InputComponent->BindAction("Attack",IE_Pressed, this, &ABasePlayer::AttackButtonPressed);
	InputComponent->BindAction("Attack", IE_Released, this ,&ABasePlayer::AttackButtonReleased);
	InputComponent->BindAction("Pick", IE_Pressed, this, &ABasePlayer::PickButtonPressed);
	InputComponent->BindAction("Pick", IE_Released, this, &ABasePlayer::PickButtonReleased);
	InputComponent->BindAction("Lock", IE_Pressed, this, &ABasePlayer::LockButtonPressed);
	InputComponent->BindAction("Next", IE_Pressed, this, &ABasePlayer::MouseWheelUpPressed);
	InputComponent->BindAction("Prev", IE_Pressed, this, &ABasePlayer::MouseWheelDownPressed);
}

auto ABasePlayer::MouseWheelUpPressed() ->void
{
	if (isInCinematic)
		return;

	if (isLocked)
		LockTheNext();
}

auto ABasePlayer::MouseWheelDownPressed() ->void
{
	if (isInCinematic)
		return;

	if (isLocked)
		LockThePrev();
}

auto ABasePlayer::LockButtonPressed() -> void
{
	if (isInCinematic)
		return;

	if (isLocked)
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		isLocked = false;
		LookAtTarget = nullptr;
		if (enemyLocked)
		{
			enemyLocked->bodyMesh->SetRenderCustomDepth(false);
			enemyLocked = nullptr;
		}
	}
	else
	{
		TArray<AEnemy*> enemies = AiDirector->GetAllEnemies();
		if (enemies.Num() > 0)
		{
			GetCharacterMovement()->bOrientRotationToMovement = false;
			isLocked = true;
			LockTheClosestEnemy();
		}
	}
}

auto ABasePlayer::PickButtonPressed() -> void
{
	if (isInCinematic)
		return;

	isPicking = true;
}

auto ABasePlayer::PickButtonReleased() -> void
{
	if (isInCinematic)
		return;

	isPicking = false;
}

auto ABasePlayer::AttackButtonPressed() -> void
{
	if (isInCinematic)
		return;

	if(hasHisHammer)
		isAttacking = true;
}

auto ABasePlayer::AttackButtonReleased() -> void
{
	if (isInCinematic)
		return;

	isAttacking = false;
}

auto ABasePlayer::MouseVertical(float Value) -> void
{
	if (isInCinematic)
		return;

	float Input = Value * 100.0f * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(Input);
}

auto ABasePlayer::MouseHorizontal(float Value) -> void
{
	if (isInCinematic)
		return;

	float Input = Value * 100.0f * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Input);
}

auto ABasePlayer::MoveVertical(float Value) -> void
{
	if (isDead || isInCinematic)
		return;

	FRotator CamRot = GetControlRotation();
	CamRot.Pitch = 0.0f;
	FVector MoveDir = CamRot.Vector();

	GetCharacterMovement()->AddInputVector(MoveDir * Value);
}

auto ABasePlayer::MoveHorizontal(float Value) -> void
{
	if (isDead || isInCinematic)
		return;

	FRotator CamRot = GetControlRotation();
	CamRot.Pitch = 0.0f;
	FVector MoveDir = CamRot.RotateVector(FVector::RightVector);

	GetCharacterMovement()->AddInputVector(MoveDir * Value);
}

auto ABasePlayer::LookAt(AActor* Target, float Duration) -> void
{
	LookAtTarget = Target;
	LookAtDuration = Duration;
}

auto ABasePlayer::UpdateRotation(float DeltaSeconds) -> void
{
	if (LookAtTarget == nullptr || LookAtDuration <= 0.0f)
	{
		return;
	}

	FRotator TargetRotation = (LookAtTarget->GetActorLocation() - GetActorLocation()).Rotation();
	TargetRotation.Pitch = 0.0f;

	FRotator SmoothRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaSeconds, RotationInterpSpeed);
	SetActorRotation(SmoothRotation);

	LookAtDuration -= DeltaSeconds;
}