// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EveAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class HYPERLOOP_API UEveAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UEveAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//good for clmaping to avoid going above max health / armor or below zero 
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//the following 4 lines required per attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Vital Attributes")
	FGameplayAttributeData Armor;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, Armor);
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	/**********************     Armor      ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxArmor, Category = "Vital Attributes")
	FGameplayAttributeData MaxArmor;

	
	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxArmor);

	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor) const;
	/**********************    Max Armor         ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "Vital Attributes")
	FGameplayAttributeData Shield;


	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, Shield);
	
	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData& OldShield) const;

	/**********************    Shield      ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShield, Category = "Vital Attributes")
	FGameplayAttributeData MaxShield;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxShield);
	
	UFUNCTION()
	void OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const;

	/**********************     Max Shield         ***************************/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CPU, Category = "Vital Attributes")
	FGameplayAttributeData CPU;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, CPU);
	
	UFUNCTION()
	void OnRep_CPU(const FGameplayAttributeData& OldCPU) const;

	/**********************    CPU        ***************************/
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxCPU, Category = "Vital Attributes")
	FGameplayAttributeData MaxCPU;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UEveAttributeSet, MaxCPU);
	
	UFUNCTION()
	void OnRep_MaxCPU(const FGameplayAttributeData& OldMaxCPU) const;

	/**********************    CPU        ***************************/
protected:

private:
	
};
