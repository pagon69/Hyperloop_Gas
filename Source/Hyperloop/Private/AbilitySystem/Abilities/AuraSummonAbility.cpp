// all rights reserved, Copyright Alleyne Technologies


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{

	const float DeltaSpread = SpawnSpreed /NumMinions;

	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector(); // forwrad vector
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation(); // actor location

	//all posiable locatiosn for spawning
	const FVector LeftOfSpread = Forward.RotateAngleAxis(SpawnSpreed / 2.f, FVector::UpVector); // a point infront to the left of actor
	const FVector RightOfSpread = Forward.RotateAngleAxis(-SpawnSpreed / 2.f, FVector::UpVector); // a point in front to right of actor
	
	TArray<FVector> SpawnLocations;
	
	for (int32 i =0; i <NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);

		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 18.f, 12, FColor::Cyan, false, 3.f);

		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Black, 3.f);
		
		DrawDebugSphere(GetWorld(), Location + Direction * MaxSpawnDistance, 5.f, 12, FColor::Purple, false, 3.f);
		DrawDebugSphere(GetWorld(), Location + Direction * MinSpawnDistance, 5.f, 12, FColor::Purple, false, 3.f);

		SpawnLocations.AddUnique(ChosenSpawnLocation);
	}
	
	return  SpawnLocations;
	
}
