// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/EveAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


UEveAttributeSet::UEveAttributeSet()
{
	
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
