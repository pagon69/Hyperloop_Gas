// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EveEnemy.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AEveEnemy : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEveEnemy();

protected:
	//for secondary items like shields
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UStaticMeshComponent> StaticShield;
	

	
};
