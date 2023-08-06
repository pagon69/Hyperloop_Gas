// all rights reserved, Copyright Alleyne Technologies


#include "Character/EvePlayerState.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AbilitySystem/EveAttributeSet.h"

AEvePlayerState::AEvePlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UEveAbilitySystemComponent> ("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	//replication mode - adjust as needed
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UEveAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AEvePlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
