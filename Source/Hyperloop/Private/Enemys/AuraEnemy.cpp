// all rights reserved, Copyright Alleyne Technologies


#include "Enemys/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Hyperloop/Hyperloop.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap); // is this correct ?
	GetMesh()->SetGenerateOverlapEvents(true); //needed for players and enemys
	
	//attribute set and ability system - not full built out
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent> ("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComponent); // first place to check for crash
	
	InitAbilityActorInfo();
}

void AAuraEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}



void AAuraEnemy::HighLightActor()
{
	//this works because of the post process volume in the world
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	//base weapons highlight
	SkeletalWeapon->SetRenderCustomDepth(true);
	SkeletalWeapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
	StaticWeapon->SetRenderCustomDepth(true);
	StaticWeapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AAuraEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);

	StaticWeapon->SetRenderCustomDepth(false);

	SkeletalWeapon->SetRenderCustomDepth(false);
	
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}
