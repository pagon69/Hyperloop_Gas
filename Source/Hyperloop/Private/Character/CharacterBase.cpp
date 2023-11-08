// all rights reserved, Copyright Alleyne Technologies


#include "Character/CharacterBase.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Hyperloop/Hyperloop.h"

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

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true); //needed for players and enemys
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap); // is this correct ?

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


UAnimMontage* ACharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

//handles hwta happens only on server
void ACharacterBase::Die()
{
	if(StaticWeapon) // checks to make sure a weapon is made
	{
		StaticWeapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	
	if(SkeletalWeapon) // what happens if nothing is attached ?
	{
		//will this run if they dont have anythign attached ?
		SkeletalWeapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}

	MulticastHandleDeath();
}

TArray<FTaggedMontage> ACharacterBase::GetAttackMontages_Implementation()
{
	return AttackMontages;
}

//what happens on client and server
void ACharacterBase::MulticastHandleDeath_Implementation()
{
    //drops weapons properties
	SkeletalWeapon->SetSimulatePhysics(true);
	SkeletalWeapon->SetEnableGravity(true);
	SkeletalWeapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	
	StaticWeapon->SetSimulatePhysics(true);
	StaticWeapon->SetEnableGravity(true);
	StaticWeapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	//rag dolls mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//todo: add impluse coming from impact of fireball to knock back body after death

	//makes the capsule not block me for death enemys
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();

	bDead = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ACharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	//check(SkeletalWeapon); no longer needed

	//todo: return correct tag

	const FAuraGameplayTags& GameplayTag = FAuraGameplayTags::Get();

	if(MontageTag.MatchesTagExact(GameplayTag.Montage_Attack_Weapon) && IsValid(SkeletalWeapon))
	{
		return SkeletalWeapon->GetSocketLocation(WeaponTipSocketNameSkeletal);
	}
	
	if(MontageTag.MatchesTagExact(GameplayTag.Montage_Attack_LeftHand) )
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	
	if(MontageTag.MatchesTagExact(GameplayTag.Montage_Attack_RightHand) )
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}

	return FVector();
	
}

bool ACharacterBase::isDead_Implementation() const
{
	return bDead;
}

AActor* ACharacterBase::GetAvator_Implementation() 
{
	return this;
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
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

//grants abilities
void ACharacterBase::AddCharacterAbilities()
{

	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	
	if(!HasAuthority()) return;

	AuraASC->AddCharacterAbilities(StartUpAbilities);
	
}

void ACharacterBase::Dissolve()
{

	if(IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst); //if i have mutilple materials on the Mixamo objects then i have to make multiple dynamicMatInst

		GetMesh()->SetMaterial(1, DynamicMatInst); //if i have mutilple materials on the Mixamo objects then i have to make multiple dynamicMatInst

		StartDissolveTimeline(DynamicMatInst);
		
	}
	
	if(IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		SkeletalWeapon->SetMaterial(0, DynamicMatInst); //if i have mutilple materials on the Mixamo objects then i have to make multiple dynamicMatInst

		
		StartWeaponDissolveTimeline(DynamicMatInst);
	}

	if(IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		StaticWeapon->SetMaterial(0, DynamicMatInst); //if i have mutilple materials on the Mixamo objects then i have to make multiple dynamicMatInst

	
		StartWeaponDissolveTimeline(DynamicMatInst);
	}
	
}





