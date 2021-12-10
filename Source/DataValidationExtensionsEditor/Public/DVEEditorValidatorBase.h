#pragma once

#include <CoreMinimal.h>

#include <EditorValidatorBase.h>

#include "DVEEditorValidatorBase.generated.h"

UCLASS( abstract )
class DATAVALIDATIONEXTENSIONSEDITOR_API UDVEEditorValidatorBase : public UEditorValidatorBase
{
    GENERATED_BODY()

public:

    UDVEEditorValidatorBase();

    bool CanValidateAsset_Implementation( UObject * asset ) const override;

protected:

    EDataValidationResult GetResult( UObject * in_asset, TArray< FText > & validation_errors );

    /* None of those directories will be validated */
    UPROPERTY( EditAnywhere )
    TArray< FDirectoryPath > ExcludedDirectories;

    /* Only these directories will be validated */
    UPROPERTY( EditAnywhere )
    TArray< FDirectoryPath > IncludedDirectories;
};
