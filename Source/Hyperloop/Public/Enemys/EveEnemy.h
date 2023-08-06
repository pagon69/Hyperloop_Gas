// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/MouseTargetInterface.h"
#include "EveEnemy.generated.h"

/**
 * 
 */
UCLASS()
class HYPERLOOP_API AEveEnemy : public ACharacterBase, public IMouseTargetInterface
{
	GENERATED_BODY()

public:
	AEveEnemy();

	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	
protected:
	//for secondary items like shields
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UStaticMeshComponent> StaticShield;
	
private:

	
	
};
