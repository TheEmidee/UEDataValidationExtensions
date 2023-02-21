#include "DVEDataValidationCommandlet.h"

#include <AssetRegistry/AssetRegistryModule.h>
#include <EditorUtilityBlueprint.h>
#include <EditorValidatorSubsystem.h>

// All this does in addition to the behavior of the parent commandlet, is to register the BP validators

int32 UDVEDataValidationCommandlet::Main( const FString & full_command_line )
{
    auto * editor_validation_subsystem = GEditor->GetEditorSubsystem< UEditorValidatorSubsystem >();
    check( editor_validation_subsystem );

    // Locate all validators (include unloaded)
    const auto & asset_registry_module = FModuleManager::LoadModuleChecked< FAssetRegistryModule >( TEXT( "AssetRegistry" ) );
    TArray< FAssetData > all_bps_asset_data;
    asset_registry_module.Get().GetAssetsByClass( UEditorUtilityBlueprint::StaticClass()->GetClassPathName(), all_bps_asset_data, true );

    for ( auto & bp_asset_data : all_bps_asset_data )
    {
        FString parent_class_name;
        if ( !bp_asset_data.GetTagValue( FBlueprintTags::NativeParentClassPath, parent_class_name ) )
        {
            bp_asset_data.GetTagValue( FBlueprintTags::ParentClassPath, parent_class_name );
        }

        if ( !parent_class_name.IsEmpty() )
        {
            UObject * outer = nullptr;
            ResolveName( outer, parent_class_name, false, false );
            const auto * parent_class = FindObject< UClass >( outer, *parent_class_name );
            if ( !parent_class || !parent_class->IsChildOf( UEditorValidatorBase::StaticClass() ) )
            {
                continue;
            }
        }

        // If this object isn't currently loaded, load it
        auto * validator_object = bp_asset_data.ToSoftObjectPath().ResolveObject();
        if ( validator_object == nullptr )
        {
            FSoftObjectPathSerializationScope serialization_scope( NAME_None, NAME_None, ESoftObjectPathCollectType::EditorOnlyCollect, ESoftObjectPathSerializeType::AlwaysSerialize );
            validator_object = bp_asset_data.ToSoftObjectPath().TryLoad();
        }
        if ( validator_object )
        {
            const auto * validator_blueprint = Cast< UEditorUtilityBlueprint >( validator_object );
            auto * validator = NewObject< UEditorValidatorBase >( GetTransientPackage(), validator_blueprint->GeneratedClass );
            editor_validation_subsystem->AddValidator( validator );
        }
    }

    return Super::Main( full_command_line );
}
