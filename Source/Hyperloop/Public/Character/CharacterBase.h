// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS(Abstract)
class HYPERLOOP_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	
	ACharacterBase();

protected:
	
	virtual void BeginPlay() override;

};
