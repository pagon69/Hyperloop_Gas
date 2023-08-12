// all rights reserved, Copyright Alleyne Technologies


#include "Actor/EveAffectActor.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/EveAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AEveAffectActor::AEveAffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);

	ItemCollisionSphere = CreateDefaultSubobject<USphereComponent>("ItemCollisionSphere");
	ItemCollisionSphere->SetupAttachment(GetRootComponent());
	
	
}



void AEveAffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//TODO: change this to apply a gameplay affect, for now using const cast as Hack
	IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor);

	if(ASCInterface)
	{

		const UEveAttributeSet* EveAttributesSet =	Cast<UEveAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UEveAttributeSet::StaticClass()));

		UEveAttributeSet* MutableEveAttributeSet = const_cast<UEveAttributeSet*>(EveAttributesSet);
		
		MutableEveAttributeSet->SetArmor(EveAttributesSet->GetArmor() + 25.f );
		
		MutableEveAttributeSet->SetCPU(EveAttributesSet->GetCPU() + 25.f );
	
		MutableEveAttributeSet->SetCPU(EveAttributesSet->GetCPU() + 25.f );

		Destroy();
	}
	
}



void AEveAffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



// Called when the game starts or when spawned
void AEveAffectActor::BeginPlay()
{
	Super::BeginPlay();


	//how to bind and use the function 
	ItemCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AEveAffectActor::OnOverlap);
	ItemCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AEveAffectActor::EndOverlap);
	
}


