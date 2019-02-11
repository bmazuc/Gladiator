
#include "Gladiator.h"
#include "EntityAttackNotify.h"


UEntityAttackNotify::UEntityAttackNotify()
{
}

bool UEntityAttackNotify::Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This is an on screen message!"));

	return true;
}