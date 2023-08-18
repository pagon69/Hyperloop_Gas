// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraAffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class HYPERLOOP_API AAuraAffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraAffectActor();

protected:
	
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);


	
};
