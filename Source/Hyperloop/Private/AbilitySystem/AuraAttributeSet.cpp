// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth( 25.F);
	InitMaxHealth( 100.F);
	InitMana( 50.F);
	InitMaxMana( 150.F);
	
	InitGhostHealth(50.f);
	InitMaxGhostHealth(100.f);
	InitGhostMana(75.f);
	InitMaxGhostMana(150.f);

	//GetGhostHealth();

	
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

	//primary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strenght, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilence, COND_None, REPNOTIFY_Always);
}

//ideal place to clamp stuff
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	
	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxHealth()); // clamps health to maxhealth
	}
	
	
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxMana());
	}

	if(Attribute == GetGhostHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f,GetMaxGhostHealth()); // clamps health to maxhealth

		NewValue = FMath::InterpEaseInOut(GetGhostHealth(), GetHealth(),.5f,.5f);
	}
	
	
}



void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//source = causer of the effect
	//target = target of the effect (owner of this effect)
	//can use auto to figure out the type of something
	
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if(IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		
		if(Props.SourceController  == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController  = Pawn->GetController();
			}
		}

		if(Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
		
	}

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get(); //get the avator
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get(); // get the controller for the above actor
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor); //cast to a specific type of character
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);  //get the ability system component
		
	}

	
}


//do clamps here also
void UAuraAttributeSet::PostGameplayEffectExecute( const FGameplayEffectModCallbackData &Data)
{
	Super::PostGameplayEffectExecute(Data);

	//UE_LOG(LogTemp, Warning, TEXT("whats in Data: %f"), GetHealth());
	//UE_LOG(LogTemp, Warning, TEXT("whats in Data: %f"), Data.EvaluatedData.Magnitude);

	FEffectProperties Props;
	
	SetEffectProperties(Data, Props);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//GEngine->AddOnScreenDebugMessage(1,3.f,FColor::Red, FString::Printf(TEXT("Health: %f"), GetHealth()));

		SetHealth(FMath::Clamp(GetHealth(), 0.f,GetMaxMana()));
	}


	if(Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
		
	}
	

	
	//below can be used to monitor what is happening and a good view into code
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// This Gameplay Effect is changing Health. Apply it, but restrict the value first.
		// In this case, Health's base value must be non-negative.
		//SetHealth(FMath::Max(GetHealth(), 0.0f));
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
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}



void UAuraAttributeSet::OnRep_GhostHealth(const FGameplayAttributeData& OldGhostHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, GhostHealth, OldGhostHealth);
}

void UAuraAttributeSet::OnRep_MaxGhostHealth(const FGameplayAttributeData& OldMaxGhostHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxGhostHealth, OldMaxGhostHealth);
}

void UAuraAttributeSet::OnRep_GhostMana(const FGameplayAttributeData& OldGhostMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, GhostMana, OldGhostMana);
}

void UAuraAttributeSet::OnRep_MaxGhostMana(const FGameplayAttributeData& OldMaxGhostMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxGhostMana, OldMaxGhostMana);
}


// Primary attributes

void UAuraAttributeSet::OnRep_Strenght(const FGameplayAttributeData& OldStrenght) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strenght, OldStrenght);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Resilence(const FGameplayAttributeData& OldResilence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilence, OldResilence);
}
