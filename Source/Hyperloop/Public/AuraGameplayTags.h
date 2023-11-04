// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


/**
 * AuraGameplay tags and singleton -
 * Singletons only exist once
 */

struct FAuraGameplayTags
{
public:

	static const FAuraGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();


	//primarys
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	//secondarys
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxHealth;
	
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	
	//resistances type
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Electric;
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Acid;
	FGameplayTag Attributes_Resistance_Physical;
	
	// inputTags used to mapping actions for movement or abilities
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_Num1;
	FGameplayTag InputTag_Num2;
	FGameplayTag InputTag_Num3;
	FGameplayTag InputTag_Num4;

	//custom abilitys

	FGameplayTag InputTag_M;
	FGameplayTag InputTag_SpaceBar;

	// damage related tags
	FGameplayTag Damage;

	//types of damage received or spells do
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Electric;
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Acid;
	FGameplayTag Damage_Physical;
	
	
	//list of damage types
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	
	//hit react related tags
	FGameplayTag Effects_HitReact;

	//abilities tag - will start with just attack but can grow
	FGameplayTag Abilities_Attack;

	
protected:

private:

	static FAuraGameplayTags GameplayTags;

	
};
