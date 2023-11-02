// all rights reserved, Copyright Alleyne Technologies


#include "AI/BTService_FindNearestPlayer.h"

#include <string>

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, *AIOwner->GetName());
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Green, *ActorOwner->GetName());


	APawn* OwningPawn = AIOwner->GetPawn();
	
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player"); //checks if they have tag player..

	TArray<AActor*> ActorsWithTag; // makes an array of actors
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag); // using the above 3 lines to get all actors in the world with the player tag

	
	//checks for closest actor and distance
	float ClosestDistance = TNumericLimits<float>::Max();
	AActor* ClosestActor = nullptr;

	for (AActor* Actor : ActorsWithTag)
	{
		if(IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor); 
			if(Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
			
		}
		
	}

	//have to select the correct function float , object etc on each item
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, ClosestDistance);
	
}
