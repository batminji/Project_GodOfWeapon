using UnrealBuildTool;

public class Project_GodOfWeaponServerTarget : TargetRules
{
    public Project_GodOfWeaponServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add( "Project_GodOfWeapon" );
    }
}