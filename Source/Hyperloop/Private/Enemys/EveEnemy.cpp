// all rights reserved, Copyright Alleyne Technologies


#include "Enemys/EveEnemy.h"

AEveEnemy::AEveEnemy()
{
	//setup collision for the swat guy
	StaticShield = CreateDefaultSubobject<UStaticMeshComponent>("ShieldSlot");
	StaticShield->SetupAttachment(GetMesh(), FName("ShieldHandSocket"));
	StaticShield->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
