#include "DVEEditorValidatorBase.h"

UDVEEditorValidatorBase::UDVEEditorValidatorBase()
{
}

bool UDVEEditorValidatorBase::CanValidateAsset_Implementation( UObject * asset ) const
{
    const auto path_name = asset->GetPathName();

    for ( const auto & included_directory : IncludedDirectories )
    {
        if ( !path_name.StartsWith( included_directory.Path ) )
        {
            return false;
        }
    }

    for ( const auto & excluded_directory : ExcludedDirectories )
    {
        if ( path_name.StartsWith( excluded_directory.Path ) )
        {
            return false;
        }
    }

    return true;
}

EDataValidationResult UDVEEditorValidatorBase::GetResult( UObject * in_asset, TArray< FText > & validation_errors )
{
    if ( validation_errors.Num() == 0 )
    {
        AssetPasses( in_asset );
    }
    else
    {
        AssetFails( in_asset, FText::GetEmpty(), validation_errors );
    }

    return validation_errors.Num() > 0 ? EDataValidationResult::Invalid : EDataValidationResult::Valid;
}
