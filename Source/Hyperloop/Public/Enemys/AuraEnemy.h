// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	//for secondary items like shields
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UStaticMeshComponent> StaticShield;
	
	
	virtual void InitializeDefaultAttributes() const override;
	
private:
	
	
};
