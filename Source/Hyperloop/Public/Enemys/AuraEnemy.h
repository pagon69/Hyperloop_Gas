// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/MouseTargetInterface.h"
#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class HYPERLOOP_API AAuraEnemy : public ACharacterBase, public IMouseTargetInterface
{
	GENERATED_BODY()

	AAuraEnemy();
	
public:

	

	//enemy interfaces 
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	
protected:

	virtual void BeginPlay() override;
	
private:
	//int CustomStenceilValue = 250;
};
