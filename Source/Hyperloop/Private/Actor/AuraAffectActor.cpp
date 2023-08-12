// all rights reserved, Copyright Alleyne Technologies


#include "Actor/AuraAffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraAffectActor::AAuraAffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());

	
	
}

//required overloaded function for components overlapping
void AAuraAffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: change this to apply a gameplay affect, for now using const cast as Hack
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);

	if(ASCInterface)
	{

		const UAuraAttributeSet* AuraAttributesSet =	Cast<UAuraAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributesSet);
		
		MutableAuraAttributeSet->SetHealth(AuraAttributesSet->GetHealth() + 25.f );

		//remove this later
		MutableAuraAttributeSet->SetMana(AuraAttributesSet->GetMana() + 50.f);
		
		Destroy();
	}
	
}

//custom code for what to do on a overlap
void AAuraAffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


void AAuraAffectActor::BeginPlay()
{
	Super::BeginPlay();

	//how to bind and use the function 
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraAffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraAffectActor::EndOverlap);
}


