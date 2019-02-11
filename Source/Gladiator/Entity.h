
#pragma once

#include "GameFramework/Character.h"
#include "Public/Weapon.h"
#include "Entity.generated.h"

UCLASS()
class GLADIATOR_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	AEntity();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	auto ReceiveHit() -> void;
	auto HitFeedBacksDelay() -> void;
	auto IsFairlyCloseTo(AWeapon* weapon) -> bool;
	auto EntityDeath() -> void;

	auto GetLife() -> int { return this->life; }
	auto GetLifeMax() -> int { return this->lifeMax; }
	auto GetHammer() -> const AWeapon* { return this->hammer; }

	auto GetShield() -> const AWeapon*{ return this->shield; }

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		bool HasHammer() { return this->hasHisHammer; }

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		bool HasShield() { return this->hasHisShield; }

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void SetGodMode(bool value = true) { this->godMode = value; }

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void SetThrowPercentage(int value);

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void DropHammer();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void DropShield();

	auto IsInCinematic() -> bool { return this->isInCinematic; }
	auto SetIsInCinematic(bool state) -> void { this->isInCinematic = state; }

	UFUNCTION(BlueprintCallable, Category = Rotation)
		float GetAnimLenght(UAnimSequence* AnimSequence);

	UFUNCTION(BlueprintCallable, Category = MyInput)
		void EntityAttack();

	UFUNCTION()
		void OnBeginTriggerOverlap(class UPrimitiveComponent* AnOtherComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndTriggerOverlap(class UPrimitiveComponent* AnOtherComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyInput)
		bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyInput)
		bool isPicking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyInput)
		bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MyInput)
		bool isLocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = characteristics)
		float moveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = characteristics)
		float direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = characteristics)
		int life = 5;

	UPROPERTY(EditAnywhere)
		bool godMode = false;

	USkeletalMeshComponent* bodyMesh;
protected:
	AWeapon* hammer;
	AWeapon* shield;
	AEntity* entityWhithinBox;
	USceneComponent* objectWhithinBox;
	bool hasHisShield;
	bool hasHisHammer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = characteristics)
		int lifeMax = 5;
	UPROPERTY(EditAnywhere, Interp, Category = cinematic)
		bool isInCinematic = false;

private:
	UPROPERTY(EditAnywhere, Category = characteristics)
		FVector offsetAttackBox;

	UPROPERTY(EditAnywhere, Category = characteristics)
		FVector boxExtent;
	
	UPROPERTY(EditAnywhere, Category = MyComponent)
		UBoxComponent* attackBox;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float feedBackTime;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float distanceToDropWeapon;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		int weaponDamage;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		int throwPercentage;

	USoundCue* hitAudioCue;
	UAudioComponent* audioComponent;
	UMaterialInstanceConstant* hitMaterialInstance;
	UMaterialInstanceConstant* originMaterialInstance;
	UMaterialInstanceConstant* equipmentMaterialInstance;

	FString hammerPath = "SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/WarHammer.WarHammer'";
	FString shieldPath = "SkeletalMesh'/Game/Characters/DwarfGrunt/SkelMesh/Shield_Skel.Shield_Skel'";
	FName weaponSocket = TEXT("WeaponPoint");
	FName shieldSocket = TEXT("DualWeaponPoint");
};
