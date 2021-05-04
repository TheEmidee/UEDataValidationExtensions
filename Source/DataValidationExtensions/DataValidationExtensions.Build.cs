namespace UnrealBuildTool.Rules
{
    public class DataValidationExtensions : ModuleRules
    {
        public DataValidationExtensions( ReadOnlyTargetRules Target )
            : base( Target )
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
            bEnforceIWYU = true;

            PublicDependencyModuleNames.AddRange(
                new string[] { 
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "TargetPlatform",
                    "AssetRegistry"
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "Slate",
                    "SlateCore",
                    "UnrealEd",
                    "AssetRegistry",
                    "EditorStyle",
                    "Blutility"
                }
            );
        }
    }
}
