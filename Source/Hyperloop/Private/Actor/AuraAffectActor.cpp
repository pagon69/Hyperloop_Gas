// all rights reserved, Copyright Alleyne Technologies


#include "Actor/AuraAffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"



// Sets default values
AAuraAffectActor::AAuraAffectActor() //best way to make basic class i think
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//make a simple root component so you can later add to the class
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

	
}




void AAuraAffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraAffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{

	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if(TargetAbilitySystemComponent == nullptr) //if no ability system component on the thing that overlapped
	{
		return;
	}

	check(GameplayEffectClass); // the effect we will do when overlapping
	
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	//what object caused the effect can be stored like below
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy ==EGameplayEffectDurationType::Infinite;

	if(bIsInfinite && InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
	}
	
	/* code for an array of context effects */

	/* can i make an array out of this ?
	 *
	TArray<FGameplayEffectContextHandle> EffectContextHandleList;
	
	EffectContextHandleList.Add(TargetAbilitySystemComponent->MakeEffectContext());

	if(EffectContextHandleList.IsEmpty()) return;
	
	
	for (auto ContextHandleList : EffectContextHandleList)
	{
		ContextHandleList = TargetAbilitySystemComponent->MakeEffectContext();
	}
	*/
	

	
}

void AAuraAffectActor::OnOverlap(AActor* TargetActor)
{
	if(InstanceEffectApplicationPolicy == EEffectApplicationPolicy::AppluOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGameplayEffectClass);
	}

	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::AppluOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::AppluOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	
}

void AAuraAffectActor::OnEndOverlap(AActor* TargetActor)
{
	if(InstanceEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstanceGameplayEffectClass);
	}

	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if(InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetActor)) return;


	/*
	 * start way to do for loop below
	 *for(auto variableName : variable to search through)
	 *{
	 * code
	 *}
	 * for (auto HandlePair : values)
	 * {}
	 */
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if( TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

	for (auto& Handle : HandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
	}
		
	}
	
}

