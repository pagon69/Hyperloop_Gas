// all rights reserved, Copyright Alleyne Technologies


#include "Enemys/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Hyperloop/Hyperloop.h"
#include "UI/Widget/AuraUserWidget.h"
#include "Hyperloop/Public/AuraGameplayTags.h"


AAuraEnemy::AAuraEnemy()
{

	//setup collision for the swat guy
	StaticShield = CreateDefaultSubobject<UStaticMeshComponent>("ShieldSlot");
	StaticShield->SetupAttachment(GetMesh(), FName("ShieldHandSocket"));
	StaticShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap); // is this correct ?
	GetMesh()->SetGenerateOverlapEvents(true); //needed for players and enemys
	
	//attribute set and ability system - not full built out
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent> ("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	


	
}

void AAuraEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!HasAuthority()) return; // check if on the server
	AuraAIController = Cast<AAuraAIController>(NewController);

	AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset); // set and get blackboard setup
	AuraAIController->RunBehaviorTree(BehaviorTree);
	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	
	if(CharacterClass != ECharacterClass::Warrior)
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), true);
	}
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	check(AbilitySystemComponent); // first place to check for crash
	
	InitAbilityActorInfo();

	if(HasAuthority())
	{
		UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}
	

	UAuraUserWidget* AuraUserWidget =  Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject());
	if(AuraUserWidget)
	{
		AuraUserWidget->SetWidgetController(this);
	}
	
	//binds to the delegates for healths and mana changes
	UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet);
	if(AuraAS)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnHeathChanged.Broadcast(Data.NewValue)	;	
			}

		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHeathChanged.Broadcast(Data.NewValue)	;	
			}

		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue)	;	
			}

		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue)	;	
			}

		);

		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		
		AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTags.Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		this,
		&AAuraEnemy::HitReactTagChanged
		
		);
		
		
		OnHeathChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHeathChanged.Broadcast(AuraAS->GetMaxHealth());
		OnManaChanged.Broadcast(AuraAS->GetMana());
		OnMaxManaChanged.Broadcast(AuraAS->GetMaxMana());
		
	}
	
}


void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0 ;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f :BaseWalkSpeed;

	if(AuraAIController && AuraAIController->GetBlackboardComponent())
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
	
	
}

void AAuraEnemy::Die()
{
	
	SetLifeSpan(LifeSpan);

	if(AuraAIController)
	{
		AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("dead"), true);
	}
	
	Super::Die();
}

void AAuraEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* AAuraEnemy::GetCombatTarget_Implementation()
{
	return CombatTarget;
}


void AAuraEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if(HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	
	
}

void AAuraEnemy::InitializeDefaultAttributes() const
{

	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
	
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
