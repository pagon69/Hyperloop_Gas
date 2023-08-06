// all rights reserved, Copyright Alleyne Technologies


#include "Character/EvePlayerState.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AbilitySystem/EveAttributeSet.h"

AEvePlayerState::AEvePlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UEveAbilitySystemComponent> ("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	
	AttributeSet = CreateDefaultSubobject<UEveAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AEvePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
