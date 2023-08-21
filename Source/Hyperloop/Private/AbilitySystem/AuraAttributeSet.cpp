// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth( 25.F);
	InitMaxHealth( 100.F);
	InitMana( 50.F);
	InitMaxMana( 150.F);
}

//required for replication - register variables
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//add variables i wnat to replicate below
	
	//registering health to be replicated, mp condition and always replicate 
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	
}

//ideal place to clamp stuff
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxHealth()); // clamps health to maxhealth
	}
	
	if(Attribute == GetMaxHealthAttribute())
	{
		
	}
	
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxMana());
	}
	
	if(Attribute == GetMaxManaAttribute())
	{
		
	}
	
	
}

void UAuraAttributeSet::PostGameplayEffectExecute( const FGameplayEffectModCallbackData &Data)
{
	Super::PostGameplayEffectExecute(Data);

	UE_LOG(LogTemp, Warning, TEXT("whats in Data: %f"), GetHealth());
	UE_LOG(LogTemp, Warning, TEXT("whats in Data: %f"), Data.EvaluatedData.Magnitude);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// This Gameplay Effect is changing Health. Apply it, but restrict the value first.
		// In this case, Health's base value must be non-negative.
		SetHealth(FMath::Max(GetHealth(), 0.0f));
	}
	
}


//required boiler plate code
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldMaxMana);
}
