// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EveAffectActor.generated.h"

class UGameplayEffect;


UCLASS()
class HYPERLOOP_API AEveAffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEveAffectActor();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Applied Affects")
	TSubclassOf<UGameplayEffect> InstanceGameplayEffectClass;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
private:

	

};
