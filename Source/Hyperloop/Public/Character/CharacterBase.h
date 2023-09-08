// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"

#include "CharacterBase.generated.h"

#define CUSTOM_DEPTH_RED 250

struct FGameplayEffectSpec;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class HYPERLOOP_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ACharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; //system required getter for ability system componenbt

	UAttributeSet* GetAttributeSet() const { return AttributeSet; } // getter for the attribute set
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> SkeletalWeapon;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UStaticMeshComponent> StaticWeapon;

	//attribute set and ability system - not full built out
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= " Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//initializes the attributes
	void InitializePrimaryAttributes() const ;
	
};
