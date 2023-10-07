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

void ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent())); // do we have an ability system component ?
	check(GameplayEffectClass); //checks if this has been set on the character
	
	FGameplayEffectContextHandle MyContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	
	MyContextHandle.AddSourceObject(this); // adds the source object which is the interface holding object
	
	FGameplayEffectSpecHandle MySpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, level,MyContextHandle);

	//remember that to get the Spec from the spec handle you have to go to Data.Get() and dereference so *
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*MySpecHandle.Data.Get(),GetAbilitySystemComponent());
	
}

void ACharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
}





