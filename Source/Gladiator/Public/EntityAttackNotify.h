#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "EntityAttackNotify.generated.h"

UCLASS()
class GLADIATOR_API UEntityAttackNotify : public UAnimNotify
{
	GENERATED_BODY()

	UEntityAttackNotify();
	virtual bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) const;
};
