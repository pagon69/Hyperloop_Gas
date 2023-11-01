// all rights reserved, Copyright Alleyne Technologies


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{

	//primarys

	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage"));
	
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases Magical damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increase armor and armor penetration"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increase health"));

	
	//secondarys
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken and improves block chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("How much you penetrate enemy armor"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to take half damage"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to land a critical hit"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("extra damage done when landing a critical hit"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Chance to resist getting a critical hit"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("How fast mana regenerates"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("How fast health regenerates"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Maximum mana "));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Maximum health"));
	
	// inputTags used to mapping actions for movement or abilities

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("responds when left mouse button is clicked"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB "), FString("responds when right mouse button is clicked"));
	GameplayTags.InputTag_Num1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Num1"), FString("responds when the nbumber 1 key is clicked"));
	GameplayTags.InputTag_Num2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Num2"), FString("responds when the nbumber 2 key is clicked"));
	GameplayTags.InputTag_Num3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Num3"), FString("responds when the nbumber 3 key is clicked"));
	GameplayTags.InputTag_Num4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Num4"), FString("responds when the nbumber 4 key is clicked"));

	// custom ability types
	GameplayTags.InputTag_M = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.M"), FString("responds when the M key key is clicked"));
	GameplayTags.InputTag_SpaceBar = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Space"), FString("responds when the space bar 4 key is clicked"));

	
	//the tag for damage abilities
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("The damage done"));

	//damage types below
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage"));
	GameplayTags.Damage_Acid = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Acid"), FString("Acid Damage"));
	GameplayTags.Damage_Electric = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Electric"), FString("Electric Damage"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"), FString("Arcane Damage"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage"));
	
	//resistances
	GameplayTags.Attributes_Resistance_Acid = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Acid"), FString("Resistance to Acid damage"));
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to fire damage"));
	GameplayTags.Attributes_Resistance_Electric = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Electric"), FString("Resistance to electric damage"));
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"), FString("Resistance to Arcane damage"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to Physical damage"));
	
	// container of damage types --> and resistance add any new type below
	/*
	 * Map of damage type to resistance
	 */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Acid, GameplayTags.Attributes_Resistance_Acid);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Electric, GameplayTags.Attributes_Resistance_Electric);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	
	//the tags for effects and hit reacts can also hold long lasting tags

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("When hit a reaction to that effect playing"));
	
}
