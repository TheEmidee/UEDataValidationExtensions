#pragma once

#include <CoreMinimal.h>

#include <EditorValidatorBase.h>

#include "DVEEditorValidatorBase.generated.h"

UCLASS( abstract )
class DATAVALIDATIONEXTENSIONSEDITOR_API UDVEEditorValidatorBase : public UEditorValidatorBase
{
    GENERATED_BODY()

protected:

    EDataValidationResult GetResult( UObject * in_asset, TArray< FText > & validation_errors );
};
