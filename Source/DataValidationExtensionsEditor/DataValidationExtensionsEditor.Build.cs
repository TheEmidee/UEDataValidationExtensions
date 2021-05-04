namespace UnrealBuildTool.Rules
{
    public class DataValidationExtensionsEditor : ModuleRules
    {
        public DataValidationExtensionsEditor( ReadOnlyTargetRules Target )
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
                    "AssetRegistry",
                    "DataValidation",
                    "DataValidationExtensions"
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
