#pragma once

#include <CoreMinimal.h>
#include <DataValidationCommandlet.h>

#include "DVEDataValidationCommandlet.generated.h"

UCLASS()
class DATAVALIDATIONEXTENSIONSEDITOR_API UDVEDataValidationCommandlet final : public UDataValidationCommandlet
{
    GENERATED_BODY()

public:
    int32 Main( const FString & full_command_line ) override;
};
