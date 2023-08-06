// all rights reserved, Copyright Alleyne Technologies


#include "Character/CharacterBase.h"


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



