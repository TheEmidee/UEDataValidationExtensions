#pragma once

#include <CoreMinimal.h>

#include "DataValidator.generated.h"

#define VALIDATOR_GET_PROPERTY( PropertyName ) #PropertyName, PropertyName

class DATAVALIDATIONEXTENSIONS_API FDataValidator
{
public:
    FDataValidator( TArray< FText > & validation_errors ) :
        ValidationErrors( validation_errors )
    {
    }

    template <typename _TYPE_>
    FDataValidator & IsGreaterThan( const FName property_name, _TYPE_ value, _TYPE_ threshold )
    {
        if ( value <= threshold )
        {
            ValidationErrors.Emplace( FText::FromString( FString::Printf( TEXT( "%s must be greater than %i" ), *property_name.ToString(), threshold ) ) );
        }
        return *this;
    }

    FDataValidator & NotNone( const FName property_name, FName value )
    {
        if ( value == NAME_None )
        {
            ValidationErrors.Emplace( FText::FromString( FString::Printf( TEXT( "%s must not be None" ), *property_name.ToString() ) ) );
        }
        return *this;
    }

    template <typename _TYPE_>
    FDataValidator & NotNull( const FName property_name, _TYPE_ value )
    {
        if ( value == nullptr )
        {
            ValidationErrors.Emplace( FText::FromString( FString::Printf( TEXT( "%s must not be null" ), *property_name.ToString() ) ) );
        }
        return *this;
    }

    template <typename _TYPE_>
    FDataValidator & NoNullItem( const FName property_name, _TYPE_ value )
    {
        for ( const auto & item : value )
        {
            if ( item == nullptr )
            {
                ValidationErrors.Emplace( FText::FromString( FString::Printf( TEXT( "%s must not contain a null item" ), *property_name.ToString() ) ) );
                break;
            }   
        }
        return *this;
    }

    EDataValidationResult Result() const
    {
        return ValidationErrors.Num() > 0 ? EDataValidationResult::Invalid : EDataValidationResult::Valid;
    }

private:
    TArray< FText > & ValidationErrors;
};

#undef VALIDATOR_GET_PROPERTY