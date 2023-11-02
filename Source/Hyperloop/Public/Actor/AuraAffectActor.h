// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraAffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	AppluOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
	
};


UENUM(BlueprintType)
enum class EEffectRemovePolicy
{
	
	RemoveOnEndOverlap,
	DoNotRemove
	
};


UCLASS()
class HYPERLOOP_API AAuraAffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraAffectActor();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	float ActorLevel = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bApplyEffectsToEnemies = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bDestroyOnEffectApplications = false;
	

	/*          Instance variables                         */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	EEffectApplicationPolicy InstanceEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TArray<TSubclassOf<UGameplayEffect>> InstanceEffectsList;
	
	/*         duration items          */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy  = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TArray<TSubclassOf<UGameplayEffect>> DurationEffectsList;


	/*            Infinite variable       */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	EEffectRemovePolicy InfiniteEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TArray<TSubclassOf<UGameplayEffect>> InfiniteEffectsList;
	
	/*            my functions                */
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable) //helper function that tells you when yo overlap or not
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	//a TMap is like a table in sql have one thing tied to another
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
};
