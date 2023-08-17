// all rights reserved, Copyright Alleyne Technologies


#include "Actor/AuraAffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


// Sets default values
AAuraAffectActor::AAuraAffectActor()
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
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

}

