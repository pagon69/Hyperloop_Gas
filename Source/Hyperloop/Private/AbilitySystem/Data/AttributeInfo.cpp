// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/Data/AttributeInfo.h"

#include "Hyperloop/AuraLogChannels.h"


//checks for the tag 
FAuraAttributeInfo UAttributeInfo::FindAttributeInfoFromTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{

	for(const FAuraAttributeInfo& info : AttributeInformation)
	{
		if(info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return info;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Cant find Info for attributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(),*GetNameSafe(this));
	}
	

	return FAuraAttributeInfo();
}
