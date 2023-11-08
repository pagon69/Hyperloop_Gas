// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/CharacterBase.h"
#include "Interaction/MouseTargetInterface.h"
#include "UI/Widget/Overlay_AuraWidgetController.h"
#include "AuraEnemy.generated.h"


class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class HYPERLOOP_API AAuraEnemy : public ACharacterBase, public IMouseTargetInterface
{
	GENERATED_BODY()

public:

	AAuraEnemy();

	virtual void PossessedBy(AController* NewController) override;

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

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 350.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 3.f;

	//responds when the tag changes - overrides a function that declared deligates
	void HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount);

	virtual void Die() override;

	UPROPERTY(BlueprintReadWrite, Category= "Combat")
	TObjectPtr<AActor> CombatTarget;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;

	virtual AActor* GetCombatTarget_Implementation() override;
	
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

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;

	
private:
	
	
};
