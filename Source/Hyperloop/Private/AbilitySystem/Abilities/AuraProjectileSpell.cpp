// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

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


		//TODO: give projectile a gameplay effect spec for casuing damage 
		
		Projectile->FinishSpawning(SpawnTransform); // complete the spawning
		
		
	}

}
