// all rights reserved, Copyright Alleyne Technologies

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"

#include "CharacterBase.generated.h"

#define CUSTOM_DEPTH_RED 250

class UGameplayAbility;
struct FGameplayEffectSpec;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UAnimMontage;

UCLASS(Abstract)
class HYPERLOOP_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	
	ACharacterBase();

	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<FTaggedMontage> AttackMontages;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; //system required getter for ability system componenbt

	UAttributeSet* GetAttributeSet() const { return AttributeSet; } // getter for the attribute set

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;


	/*            Combat Interface       */
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;

	virtual bool isDead_Implementation() const override;

	virtual AActor* GetAvator_Implementation() override;
	
	virtual void Die() override;
	/*             end    combat interface      */
	
	
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();
	
protected:

	virtual void BeginPlay() override;

	bool bDead = false;
	
	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<USkeletalMeshComponent> SkeletalWeapon;

	UPROPERTY(EditAnywhere, Category= "Combat")
	TObjectPtr<UStaticMeshComponent> StaticWeapon;

	

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketNameSkeletal;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketNameStatic;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;

	

	//attribute set and ability system - not full built out
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= " Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= " Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= " Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const ;

	//initializes the attributes
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Materials") // used to switch out the material used from default to dissolving material
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Materials") // used to switch out the material used from default to dissolving material
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
private:
	
	UPROPERTY(EditAnywhere, Category= "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	UPROPERTY(EditAnywhere, Category= "Abilities")
	TObjectPtr<UAnimMontage> HitReactMontage;

	
};
