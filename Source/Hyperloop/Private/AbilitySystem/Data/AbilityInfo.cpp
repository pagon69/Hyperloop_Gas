// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/Data/AbilityInfo.h"

#include "Hyperloop/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for( const FAuraAbilityInfo& Info : AbilityInformation)
	{
			if(Info.AbilityTag == AbilityTag)
			{
				return Info;
			}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Cant find info for ABILITYTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}
	
	
	return FAuraAbilityInfo();
}
