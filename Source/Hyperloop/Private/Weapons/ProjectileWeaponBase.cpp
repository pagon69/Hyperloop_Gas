// all rights reserved, Copyright Alleyne Technologies


#include "Weapons/ProjectileWeaponBase.h"

// Sets default values
AProjectileWeaponBase::AProjectileWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectileWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

