// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"


class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
	
protected:
	
private:

	
};
