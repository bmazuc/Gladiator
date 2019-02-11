#include "Gladiator.h"
#include "Entity.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceConstant.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	bodyMesh = GetMesh();

	static ConstructorHelpers::FObjectFinder<USoundCue> audioCue(TEXT("SoundCue'/Game/Sounds/Weapons/HandToHand/FightSwordsCue.FightSwordsCue'"));
	hitAudioCue = audioCue.Object;
	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	audioComponent->bAutoActivate = false;
	audioComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	audioComponent->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	offsetAttackBox = FVector(70.0f, 0.0f, 0.0f);
	boxExtent = FVector(40.0f, 40.0f, 40.0f);

	attackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Box"));
	attackBox->SetRelativeLocation(offsetAttackBox);
	attackBox->SetBoxExtent(boxExtent, true);
	attackBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	if (!attackBox->OnComponentBeginOverlap.IsAlreadyBound(this, &AEntity::OnBeginTriggerOverlap))
		attackBox->OnComponentBeginOverlap.AddDynamic(this, &AEntity::OnBeginTriggerOverlap);

	if (!attackBox->OnComponentEndOverlap.IsAlreadyBound(this, &AEntity::OnEndTriggerOverlap))
		attackBox->OnComponentEndOverlap.AddDynamic(this, &AEntity::OnEndTriggerOverlap);

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> material(TEXT("MaterialInstanceConstant'/Game/PLA/Materials/M_TargetVisual.M_TargetVisual'"));
	hitMaterialInstance = material.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> originMaterial(TEXT("MaterialInstanceConstant'/Game/AnimStarterPack/UE4_Mannequin/Materials/M_UE4Man_Body.M_UE4Man_Body'"));
	originMaterialInstance = originMaterial.Object;
}

void AEntity::OnBeginTriggerOverlap(class UPrimitiveComponent* owner, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	objectWhithinBox = OtherComp;
	AEntity* hitActor = Cast<AEntity>(OtherActor);
	if (hitActor)
		if (!hitActor->isDead)
			if (entityWhithinBox == nullptr)
				entityWhithinBox = hitActor;
}

void AEntity::OnEndTriggerOverlap(class UPrimitiveComponent* AnOtherComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (objectWhithinBox == OtherComp)
		objectWhithinBox = nullptr;

	AEntity* hitActor = Cast<AEntity>(OtherActor);
	if (hitActor)
	{
		if (entityWhithinBox == hitActor)
		{
			TArray<AActor*> entities;
			attackBox->GetOverlappingActors(entities, TSubclassOf<AEntity>());
			if (entities.Num() > 0)
				entityWhithinBox = Cast<AEntity>(entities[0]);
			else
				entityWhithinBox = nullptr;
		}
	}
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;

	if (hitAudioCue->IsValidLowLevelFast())
		audioComponent->SetSound(hitAudioCue);

	hammer = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), spawnParams);
	hammer->Init(hammerPath);
	hammer->AttachToComponent(bodyMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, weaponSocket);
	hasHisHammer = true;

	shield = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), spawnParams);
	shield->Init(shieldPath);
	shield->AttachToComponent(bodyMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, shieldSocket);
	hasHisShield = true;

	bodyMesh->CustomDepthStencilValue = 254;

	objectWhithinBox = nullptr;
	entityWhithinBox = nullptr;
	lifeMax = life;
}

void AEntity::SetThrowPercentage(int value) { this->throwPercentage = value; }

void AEntity::DropHammer()
{
	if (!this->hasHisHammer)
		return;

	AWeapon* weaponToThrow = this->hammer;
	if (!weaponToThrow->isThrowed)
	{
		weaponToThrow->ThrowWeaponObject();
		if (this->GetName().Contains("Player"))
			weaponToThrow->GlowAroundPlayerStuff();

		this->hasHisHammer = false;
	}
}

void AEntity::DropShield()
{
	if (!this->hasHisShield)
		return;

	AWeapon* weaponToThrow = this->shield;
	if (!weaponToThrow->isThrowed)
	{
		weaponToThrow->ThrowWeaponObject();
		if (this->GetName().Contains("Player"))
			weaponToThrow->GlowAroundPlayerStuff();

		this->hasHisShield = false;
	}
}

auto AEntity::IsFairlyCloseTo(AWeapon* weapon) -> bool
{
	float distanceToWeapon = (GetActorLocation() - weapon->GetActorLocation()).Size();
	if (distanceToWeapon <= distanceToDropWeapon && weapon->canDropMyWeapon)
		return true;

	return false;
}

void AEntity::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (isInCinematic)
		return;

	moveSpeed = FVector::DotProduct(GetVelocity(), GetActorRotation().Vector());

	if (isPicking)
	{
		if (!hasHisHammer)
			if (IsFairlyCloseTo(hammer))
			{
				hammer->DropWeaponObject(bodyMesh, weaponSocket);
				hasHisHammer = true;
			}

		if (!hasHisShield)
			if (IsFairlyCloseTo(shield))
			{
				shield->DropWeaponObject(bodyMesh, shieldSocket);
				hasHisShield = true;
			}
	}

	if (isLocked)
	{
		if (GetVelocity().GetSafeNormal() != FVector(0.f))
		{
			float dot = FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorForwardVector());
			if (dot > 1.f)
				dot = 1.f;

			direction = FMath::RadiansToDegrees(acosf(dot));

			float dot2 = FVector::DotProduct(GetVelocity().GetSafeNormal(), GetActorRightVector());
			if (dot2 < 0.f)
				direction *= -1;
		}
		else
			direction = 0.f;
	}

}

void AEntity::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
}

void AEntity::EntityAttack()
{
	if (objectWhithinBox != nullptr)
		audioComponent->Play();

	if (entityWhithinBox)
	{
		if (!entityWhithinBox->isDead)
		{
			hammer->PlayBloodParticleEffect();
			entityWhithinBox->ReceiveHit();
		}
	}
}

auto AEntity::ReceiveHit() -> void
{
	FTimerHandle unusedHandle;

	if (!this->godMode)
	{
		if (hasHisShield)
			life -= weaponDamage;
		else
			life -= weaponDamage * 2;

		if (life <= 0)
		{
			life = 0;
			EntityDeath();
		}
	}

	bodyMesh->SetMaterial(0, hitMaterialInstance);
	bodyMesh->SetMaterial(1, hitMaterialInstance);
	GetWorldTimerManager().SetTimer(unusedHandle, this, &AEntity::HitFeedBacksDelay, feedBackTime, false);

	bool shouldThrow = false;

	if (throwPercentage > 0)
		shouldThrow = FMath::RandRange(1, 100 / throwPercentage) == 1 ? true : false;

	if (shouldThrow && !this->godMode)
	{
		AWeapon* weaponToThrow = FMath::RandRange(1, 2) == 1 ? hammer : shield;
		if (!weaponToThrow->isThrowed)
		{
			weaponToThrow->ThrowWeaponObject();
			if (this->GetName().Contains("Player"))
				weaponToThrow->GlowAroundPlayerStuff();			

			if (weaponToThrow == hammer)
				hasHisHammer = false;
			else
				hasHisShield = false;
		}
	}
	
}

auto AEntity::EntityDeath() ->void
{
	isDead = true;
	SetActorEnableCollision(false);
	this->bodyMesh->SetEnableGravity(false);

	UPlayerCharacterAnimInstance* animInstance = (UPlayerCharacterAnimInstance*)GetMesh()->GetAnimInstance();
	if (!animInstance)
		return;

	animInstance->bIsCharacterDead = true;
}

auto AEntity::HitFeedBacksDelay() -> void
{
	bodyMesh->SetMaterial(0, originMaterialInstance);
	bodyMesh->SetMaterial(1, equipmentMaterialInstance);
}

auto AEntity::GetAnimLenght(UAnimSequence* AnimSequence) ->float
{
	float Length = 0.f;

	if (AnimSequence)
		if (AnimSequence->RateScale != 0)
			Length = AnimSequence->SequenceLength / AnimSequence->RateScale;

	return Length;
}
