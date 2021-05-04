#include "DVEEditorValidatorBase.h"

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
