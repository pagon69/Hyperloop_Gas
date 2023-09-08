// all rights reserved, Copyright Alleyne Technologies


#include "Character/CharacterBase.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/************************ Create weapons slots for static and skeletal mesh, no collision ************/
	
	StaticWeapon = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshWeapon");
	StaticWeapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	StaticWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SkeletalWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshWeapon");
	SkeletalWeapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	SkeletalWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::InitAbilityActorInfo()
{
}

//this function generates the needed components for a base character to use the ability system effect handle
void ACharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent())); // do we have an ability system component ?
	check(DefaultPrimaryAttributes); //checks if this has been set on the character
	
	 FGameplayEffectContextHandle MyContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	 FGameplayEffectSpecHandle MySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f,MyContextHandle);

	//remember that to get the Spec from the spec handle you have to go to Data.Get() and dereference so *
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*MySpecHandle.Data.Get(),GetAbilitySystemComponent());
}



