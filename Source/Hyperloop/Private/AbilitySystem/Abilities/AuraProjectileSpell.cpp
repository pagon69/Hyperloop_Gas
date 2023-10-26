// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Hyperloop/Public/AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//how to use printstring from C++
	//UKismetSystemLibrary::PrintString(this, FString("Activate Ability- C++"), true, true, FLinearColor::Yellow, 3);

	

//	SpawnProjectile();
	
}


//spawns a projectile
void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	
	if(!bIsServer) return; //return iof not on the server

	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if(CombatInterface)
	{
		const FVector  SocketLocation = CombatInterface->GetCombatSocketLocation(); // uses the getter on the combat interface to get the socket name and location

		FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation(); // minus two location vectors to get a rotation

		Rotation.Pitch = 0.f; // make it parallel by removing pitch
		
		FTransform SpawnTransform;

		SpawnTransform.SetLocation(SocketLocation); // decides where to send from
		
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		//TODO: set the rotation
		
		//will spawn an actor at this transform location
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);	


		//TODO: give projectile a gameplay effect spec for casuing damage - done

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

		const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel()); // gets the level at this level

		//removed a on screen debug
		//GEngine->AddOnScreenDebugMessage(-1, 3.f,FColor::Red, FString::Printf(TEXT("firebolt damage: %f"), ScaledDamage)); // scales damage based on level and curve table ct_firedamage
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage); // to use set by caller versus scale float or other options
		
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform); // complete the spawning
		
		//PlaySoundInTransit();
		
	}


	
}

/*
void UAuraProjectileSpell::PlaySoundInTransit()
{

	
	//todo: after spawning add sound to it as it travels

	//UGameplayStatics::PlaySoundAtLocation(this, TravelingSound, GetActorLocation());
}
*/