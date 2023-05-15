namespace UnrealBuildTool.Rules
{
    public class DataValidationExtensions : ModuleRules
    {
        public DataValidationExtensions( ReadOnlyTargetRules Target )
            : base( Target )
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicDependencyModuleNames.AddRange(
                new string[] { 
                    "Core",
                    "CoreUObject",
                    "Engine"
                }
            );
        }
    }
}
