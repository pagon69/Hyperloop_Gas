// all rights reserved, Copyright Alleyne Technologies


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetPlayerLevel()
{
	return 0;
}

//returns the socket to launch the effect from
FVector ICombatInterface::GetCombatSocketLocation()
{
	return FVector();
}
