// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/MouseTargetInterface.h"
#include "UI/Widget/Overlay_AuraWidgetController.h"
#include "AuraEnemy.generated.h"


class UWidgetComponent;
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

	/*
	 * setup the Combat interface 
	 */
	virtual int32 GetPlayerLevel() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHeathChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHeathChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxManaChanged;
	
protected:

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	//int CustomStenceilValue = 250;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	
private:
	
	
};
