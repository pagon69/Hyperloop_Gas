// all rights reserved, Copyright Alleyne Technologies

using UnrealBuildTool;
using System.Collections.Generic;

public class HyperloopEditorTarget : TargetRules
{
	public HyperloopEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Hyperloop" } );
	}
}
