// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"


struct FGameplayEffectModCallbackData;


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature); declared a delegate


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {};

	FGameplayEffectContextHandle EffectContextHandle;
	
	//source data
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	
	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter*  SourceCharacter = nullptr;
	
// target data
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter*  TargetCharacter = nullptr;

	
};

//creates an alais for a hard to look at function calls
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;

//another way to do an alais but also a template
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */

UCLASS()
class HYPERLOOP_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//good for clmaping to avoid going above max health / armor or below zero 
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//good for logic after a change ?>
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


	//TMap<FGameplayTag, FAttributeSignature> TagsToAttributes;
	/*
	 * templates , typedef, alais and function pointers are below and suck for understandability 
	 */
	
    //not sure about this but basically code for function pointers
	//can store a pointer to a function that we create
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	
	
	/**********************     Health      ***************************/
	//the following 4 lines required per attribute
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	

	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/**********************    Mana      ***************************/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;

	//can remove later when we learn about gameplay affects
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	
	/**********************     Ghost Health - trailing health bar       ***************************
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_GhostHealth, Category = "Vital Attributes")
	FGameplayAttributeData GhostHealth;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, GhostHealth);
	
	UFUNCTION()
	void OnRep_GhostHealth(const FGameplayAttributeData& OldGhostHealth) const;
*/
	
	/**********************     Max Ghost Health         ***************************
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxGhostHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxGhostHealth;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxGhostHealth);
	
	UFUNCTION()
	void OnRep_MaxGhostHealth(const FGameplayAttributeData& OldMaxGhostHealth) const;
*/
	

	/**********************     Ghost mana - trailing health bar       ***************************
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_GhostMana, Category = "Vital Attributes")
	FGameplayAttributeData GhostMana;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, GhostMana);
	
	UFUNCTION()
	void OnRep_GhostMana(const FGameplayAttributeData& OldGhostMana) const;
*/
	
	/**********************     Max Ghost mana         ***************************
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxGhostMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxGhostMana;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxGhostMana);
	
	UFUNCTION()
	void OnRep_MaxGhostMana(const FGameplayAttributeData& OldMaxGhostMana) const;

	*/

	/*
	 * Primary Attributes
	 */

	//Strenght attribute boiler plate
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strenght, Category = "Primary Attributes")
	FGameplayAttributeData Strenght;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strenght);

	UFUNCTION()
	void OnRep_Strenght(const FGameplayAttributeData& OldStrenght) const;


	//Intelligence attribute boiler plate
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;


	//Dexterity attribute boiler plate
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;


	//Resilence attribute boiler plate
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilence, Category = "Primary Attributes")
	FGameplayAttributeData Resilence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilence);

	UFUNCTION()
	void OnRep_Resilence(const FGameplayAttributeData& OldResilence) const;

	/*********************** Secondary Stats */

	//Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	//ArmorPenetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	
	//BlockChance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	
	//CriticalHitChance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	
	//CriticalHitDamage
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	
	//CriticalHitResistance
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	
	//HealthRegeneration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	
	//ManaRegeneration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	
	//MaxHealth
	/**********************    Max Health         ***************************/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	/**********************      Max Mana -          ***************************/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;

	//can remove later when we learn about accessors
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	
protected:
	
	
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
};
