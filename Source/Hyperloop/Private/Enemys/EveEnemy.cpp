// all rights reserved, Copyright Alleyne Technologies


#include "Enemys/EveEnemy.h"
#include "AbilitySystem/EveAbilitySystemComponent.h"
#include "AbilitySystem/EveAttributeSet.h"

AEveEnemy::AEveEnemy()
{
	//setup collision for the swat guy
	StaticShield = CreateDefaultSubobject<UStaticMeshComponent>("ShieldSlot");
	StaticShield->SetupAttachment(GetMesh(), FName("ShieldHandSocket"));
	StaticShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block); // to set visablity channel to block to slow highlight

	//attribute set and ability system declarations
	AbilitySystemComponent = CreateDefaultSubobject<UEveAbilitySystemComponent> ("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UEveAttributeSet>("AttributeSet");
	
}

void AEveEnemy::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComponent); // check for crash here
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AEveEnemy::HighLightActor()
{
	//this works because of the post process volume in the world

	//mesh highlight
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	//base weapons and custom eve weapon highlight
	StaticShield->SetRenderCustomDepth(true);
	StaticShield->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	SkeletalWeapon->SetRenderCustomDepth(true);
	SkeletalWeapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	StaticWeapon->SetRenderCustomDepth(true);
	StaticWeapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	
}

void AEveEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);

	StaticWeapon->SetRenderCustomDepth(false);

	SkeletalWeapon->SetRenderCustomDepth(false);

	StaticShield->SetRenderCustomDepth(false);
}
