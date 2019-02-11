#pragma once

#include "Entity.h"
#include "AI/AIDirector.h"
#include "BasePlayer.generated.h"

UCLASS()
class GLADIATOR_API ABasePlayer : public AEntity
{
	GENERATED_BODY()

public:
	ABasePlayer();
	~ABasePlayer();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	auto MouseVertical(float Value) -> void;
	auto MouseHorizontal(float Value) ->void;
	auto MoveVertical(float Value) ->void;
	auto MoveHorizontal(float Value) ->void;
	auto AttackButtonPressed() -> void;
	auto AttackButtonReleased() -> void;
	auto PickButtonPressed() -> void;
	auto PickButtonReleased() -> void;
	auto LockButtonPressed() -> void;
	auto MouseWheelUpPressed() ->void;
	auto MouseWheelDownPressed() ->void;

	auto LockTheClosestEnemy() ->void;
	auto LockTheNext() ->void;
	auto LockThePrev() ->void;

	UFUNCTION(BlueprintCallable, Category = Rotation)
		void LookAt(AActor* Target, float Duration);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotation)
		float RotationInterpSpeed = 50.0f;

private:
	auto UpdateRotation(float DeltaSeconds) -> void;

	AAIDirector* AiDirector;
	AEnemy* enemyLocked = nullptr;
	AActor*	LookAtTarget = nullptr;
	float	LookAtDuration = 0.0f;
	ACameraActor* camera;
};
