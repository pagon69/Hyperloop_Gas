// all rights reserved, Copyright Alleyne Technologies

using UnrealBuildTool;
using System.Collections.Generic;

public class HyperloopTarget : TargetRules
{
	public HyperloopTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Hyperloop" } );
	}
}
