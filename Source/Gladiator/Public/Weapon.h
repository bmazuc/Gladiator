#pragma once

#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "Weapon.generated.h"

UCLASS()
class GLADIATOR_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	auto Init(FString path) ->void;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	auto EnableToDrop() -> void;
	auto GlowAroundPlayerStuff() -> void;

	auto ThrowWeaponObject() -> void;
	auto DropWeaponObject(USkeletalMeshComponent* mesh, FName socket) -> void;
	auto PlayBloodParticleEffect() -> void;

	bool isThrowed;
	bool canDropMyWeapon;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* weaponMesh;

	UBoxComponent* weaponBox;

private:
	UParticleSystemComponent* bloodParticle;
};
