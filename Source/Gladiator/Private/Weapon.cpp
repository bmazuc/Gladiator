#include "Gladiator.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	weaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	weaponBox->BodyInstance.SetCollisionProfileName("Weapon");
	weaponBox->bGenerateOverlapEvents = false;
	RootComponent = weaponBox;
	
	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("New Mesh"));
	weaponMesh->SetupAttachment(weaponBox);

	bloodParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Blood Particle"));
	bloodParticle->AttachTo(weaponMesh, "bloodSocket");
	static ConstructorHelpers::FObjectFinder<UParticleSystem> particleSys(TEXT("ParticleSystem'/Game/Environment/Effects/particles/BloodParticle.BloodParticle'"));

	bloodParticle->bAutoActivate = false;
	bloodParticle->SetTemplate(particleSys.Object);
}

auto AWeapon::ThrowWeaponObject() -> void
{
	FTimerHandle unusedHandle;
	FVector randomDirectionVector;
	randomDirectionVector.X = FMath::FRandRange(0, 30);
	randomDirectionVector.Y = FMath::FRandRange(0, 30);
	randomDirectionVector.Z = FMath::FRandRange(0, 30);

	isThrowed = true;
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	weaponBox->SetSimulatePhysics(true);
	weaponBox->AddForce(randomDirectionVector * weaponBox->GetBodyInstance()->GetBodyMass() * 1000);

	GetWorldTimerManager().SetTimer(unusedHandle, this, &AWeapon::EnableToDrop, 2.0f, false);
}

auto AWeapon::GlowAroundPlayerStuff() -> void
{
	weaponMesh->SetRenderCustomDepth(true);
}

auto AWeapon::EnableToDrop() -> void
{
	canDropMyWeapon = true;
}

auto AWeapon::Init(FString path) ->void
{
	USkeletalMesh* meshComp = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), NULL, *path));
	weaponMesh->SetSkeletalMesh(meshComp);
	weaponMesh->CustomDepthStencilValue = 255;
}

auto AWeapon::DropWeaponObject(USkeletalMeshComponent* mesh, FName socket) -> void
{
	weaponBox->SetSimulatePhysics(false);
	AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socket);
	weaponMesh->SetRenderCustomDepth(false);
	canDropMyWeapon = false;
	isThrowed = false;
}

auto AWeapon::PlayBloodParticleEffect() -> void
{
	bloodParticle->ActivateSystem();
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}
