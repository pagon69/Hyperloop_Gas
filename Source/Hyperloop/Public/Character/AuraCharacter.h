// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AAuraCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void BeginPlay() override;

private:

	virtual void InitAbilityActorInfo() override;
};
