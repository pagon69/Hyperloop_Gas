// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{

	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return MyObj;
	
}

void UTargetDataUnderMouse::Activate()
{

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendMouseCurserData();
	}
	else
	{
		//TODO: 
	}
	

	
}

void UTargetDataUnderMouse::SendMouseCurserData()
{

	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	//gets the target data under mouse and broadcast to client but need to handle server
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	//ValidData.Broadcast(CursorHit.Location);

	FGameplayAbilityTargetDataHandle DataHandle;
	
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	//sends mouse target data to the server
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
												 GetActivationPredictionKey(),
												 DataHandle, FGameplayTag(),
												 AbilitySystemComponent->ScopedPredictionKey);


	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);	
	}

	
}
