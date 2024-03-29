#pragma once

#include "DVEEditorValidatorBase.h"

#include <CoreMinimal.h>
#include <Engine/Texture.h>

#include "DVEEditorValidatorTexturesBase.generated.h"

UCLASS( Abstract )
class DATAVALIDATIONEXTENSIONSEDITOR_API UDVEEditorValidatorTexturesBase : public UDVEEditorValidatorBase
{
    GENERATED_BODY()

public:
    UDVEEditorValidatorTexturesBase();

    bool CanValidateAsset_Implementation( UObject * in_asset ) const override;
    EDataValidationResult ValidateLoadedAsset_Implementation( UObject * in_asset, TArray< FText > & validation_errors ) override;

protected:
    enum class ECheckFlag : uint8
    {
        DontCheck,
        CheckItIsOn,
        CheckItIsOff
    };

    struct FTextureSettings
    {
        ECheckFlag GetCheckSRGB() const
        {
            return CheckSRGB;
        }

        ECheckFlag GetCheckNeverStream() const
        {
            return CheckNeverStream;
        }

        TextureGroup RequiredTextureGroup = TEXTUREGROUP_World;
        TArray< TextureCompressionSettings > RequiredCompressionSettings = { TC_Default };
        TOptional< TextureMipGenSettings > OptionalMipGenSettings;

        void SetCheckSRGB( const ECheckFlag new_value )
        {
            CheckSRGB = new_value;
        }

        void SetCheckNeverStream( const ECheckFlag new_value )
        {
            CheckNeverStream = new_value;
        }

    private:
        ECheckFlag CheckSRGB = ECheckFlag::DontCheck;
        ECheckFlag CheckNeverStream = ECheckFlag::DontCheck;
    };

    struct FTextureSettingsApplicator
    {
        FTextureSettingsApplicator( const TFunction< bool( const FString &, const FString & ) > & predicate, const TFunction< void( FTextureSettings & ) > & update_settings ) :
            FTextureSettingsApplicator( predicate, update_settings, 0, false )
        {}

        FTextureSettingsApplicator( const TFunction< bool( const FString &, const FString & ) > & predicate, const TFunction< void( FTextureSettings & ) > & update_settings, const int priority, const bool is_exclusive ) :
            Predicate( predicate ),
            UpdateSettings( update_settings ),
            Priority( priority ),
            bIsExclusive( is_exclusive )
        {}

        TFunction< bool( const FString &, const FString & ) > Predicate;
        TFunction< void( FTextureSettings & ) > UpdateSettings;
        int Priority;
        bool bIsExclusive;
    };

    void RegisterTextureSettingsApplicator( const FTextureSettingsApplicator & applicator );

private:
    TArray< FTextureSettingsApplicator > TextureSettingsApplicators;
    bool bHasSortedApplicators;
};
