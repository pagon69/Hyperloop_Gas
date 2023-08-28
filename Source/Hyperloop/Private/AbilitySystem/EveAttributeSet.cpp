// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/EveAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UEveAttributeSet::UEveAttributeSet()
{
	
	InitArmor(60.f);
	InitMaxArmor(100.f);
	InitShield(50.f);
	InitMaxShield(150.f);
	InitCPU(10.f);
	InitMaxCPU(100.f);
	
}

void UEveAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, Shield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxShield, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, CPU, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEveAttributeSet, MaxCPU, COND_None, REPNOTIFY_Always);
	
}

//ideal place to clamp stuff

void UEveAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxArmor()); // clamps health to maxhealth
	}
	
	if(Attribute == GetMaxArmorAttribute())
	{
		
	}
	
	if(Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxShield());
	}
	
	if(Attribute == GetMaxShieldAttribute())
	{
		
	}
	
}

/**                              Armor                                                  */
void UEveAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, Armor, OldArmor);
}

void UEveAttributeSet::OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxArmor, OldMaxArmor);
}

/**                              Shield                                                  */
void UEveAttributeSet::OnRep_Shield(const FGameplayAttributeData& OldShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, Shield, OldShield);
}

void UEveAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& OldMaxShield) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxShield, OldMaxShield);
}

/**                              CPU                                                  */
void UEveAttributeSet::OnRep_CPU(const FGameplayAttributeData& OldCPU) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, CPU, OldCPU);
}

void UEveAttributeSet::OnRep_MaxCPU(const FGameplayAttributeData& OldMaxCPU) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEveAttributeSet, MaxCPU, OldMaxCPU);
}

