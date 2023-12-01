#pragma once

#include <CoreMinimal.h>
#include <Misc/DataValidation.h>
#include <Templates/SubclassOf.h>
#include <UObject/ObjectPtr.h>

#if WITH_EDITOR

#define VALIDATOR_GET_PROPERTY( PropertyName ) #PropertyName, PropertyName

struct DATAVALIDATIONEXTENSIONS_API FDVEDataValidator
{
    explicit FDVEDataValidator( FDataValidationContext & context ) :
        Context( context )
    {
    }

    FDVEDataValidator & IsFalse( const FName property_name, const bool value )
    {
        if ( value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must be false" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    FDVEDataValidator & IsTrue( const FName property_name, const bool value )
    {
        if ( !value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must be false" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & AreEqual( const FName first_property_name, const _TYPE_ first_value, const FName second_property_name, const _TYPE_ second_value )
    {
        if ( first_value != second_value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must be equal to %s. Current value : %s. Expected value : %s" ),
                        *first_property_name.ToString(),
                        *second_property_name.ToString(),
                        *GetValueToString( first_value ),
                        *GetValueToString( second_value ) ) ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & AreEqual( const _TYPE_ first_value, const _TYPE_ second_value, FText error_message )
    {
        if ( first_value != second_value )
        {
            Context.AddError( MoveTemp( error_message ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & AreEqual( const FName property_name, const _TYPE_ property_value, const _TYPE_ expected_value )
    {
        if ( property_value != expected_value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must be equal to %s. Current value : %s" ),
                        *property_name.ToString(),
                        *GetValueToString( expected_value ),
                        *GetValueToString( property_value ) ) ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & AreNotEqual( const FName first_property_name, const _TYPE_ first_value, const FName second_property_name, const _TYPE_ second_value )
    {
        if ( first_value == second_value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be equal to %s. Current value : %s. Expected value : %s )" ),
                        *first_property_name.ToString(),
                        *second_property_name.ToString(),
                        *GetValueToString( first_value ),
                        *GetValueToString( second_value ) ) ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & AreNotEqual( const _TYPE_ first_value, const _TYPE_ second_value, FText error_message )
    {
        if ( first_value == second_value )
        {
            Context.AddError( MoveTemp( error_message ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & AreNotEqual( const FName property_name, const _TYPE_ property_value, const _TYPE_ not_expected_value )
    {
        if ( property_value == not_expected_value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be equal to %s" ),
                        *property_name.ToString(),
                        *GetValueToString( not_expected_value ) ) ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & IsGreaterThan( const FName property_name, const _TYPE_ value, const _TYPE_ threshold )
    {
        if ( value <= threshold )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must be greater than %s. Current value : %s" ),
                        *property_name.ToString(),
                        *GetValueToString( threshold ),
                        *GetValueToString( value ) ) ) );
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & IsValid( const FName property_name, const _TYPE_ value )
    {
        if ( !value.IsValid() )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must be valid" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    FDVEDataValidator & NotNone( const FName property_name, const FName value )
    {
        if ( value == NAME_None )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be None" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    template < typename _CONTAINER_TYPE_ >
    FDVEDataValidator & NoNoneItem( const FName property_name, const _CONTAINER_TYPE_ & container )
    {
        for ( const auto & item : container )
        {
            if ( item == NAME_None )
            {
                Context.AddError(
                    FText::FromString(
                        FString::Printf( TEXT( "%s must not contain a none item" ),
                            *property_name.ToString() ) ) );
                break;
            }
        }
        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & NotNull( const FName property_name, const _TYPE_ value )
    {
        if ( IsValueNull( value ) )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be null" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    template < typename _CONTAINER_TYPE_ >
    FDVEDataValidator & NoNullItem( const FName property_name, const _CONTAINER_TYPE_ & container )
    {
        for ( const auto & item : container )
        {
            if ( IsValueNull( item ) )
            {
                Context.AddError(
                    FText::FromString(
                        FString::Printf( TEXT( "%s must not contain a null item" ),
                            *property_name.ToString() ) ) );
                break;
            }
        }
        return *this;
    }

    template < typename _CONTAINER_TYPE_ >
    FDVEDataValidator & NotEmpty( const FName property_name, const _CONTAINER_TYPE_ & container )
    {
        if ( container.Num() == 0 )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be empty" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    FDVEDataValidator & NotEmpty( const FName property_name, const FString & string )
    {
        if ( string.IsEmpty() )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be empty" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    FDVEDataValidator & NotEmpty( const FName property_name, const FText & text )
    {
        if ( text.IsEmpty() )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must not be empty" ),
                        *property_name.ToString() ) ) );
        }
        return *this;
    }

    template < typename _CONTAINER_TYPE_ >
    FDVEDataValidator & NoEmptyItem( const FName property_name, const _CONTAINER_TYPE_ & container )
    {
        for ( const auto & item : container )
        {
            if ( item.IsEmpty() )
            {
                Context.AddError(
                    FText::FromString(
                        FString::Printf( TEXT( "%s must not contain an empty item" ),
                            *property_name.ToString() ) ) );
                break;
            }
        }
        return *this;
    }

    template < typename _CONTAINER_TYPE_ >
    FDVEDataValidator & HasNumItems( const FName property_name, const _CONTAINER_TYPE_ & container, int expected_value )
    {
        if ( container.Num() != expected_value )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must have %i items" ),
                        *property_name.ToString(),
                        expected_value ) ) );
        }
        return *this;
    }

    template < typename _TAG_CONTAINER_TYPE_, typename _TAG_TYPE_ >
    FDVEDataValidator & HasTag( const FName property_name, const _TAG_CONTAINER_TYPE_ & tag_container, const _TAG_TYPE_ expected_tag )
    {
        if ( !tag_container.HasTag( expected_tag ) )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must have the tag %s" ),
                        *property_name.ToString(),
                        *expected_tag.ToString() ) ) );
        }

        return *this;
    }

    template < typename _TAG_CONTAINER_TYPE_ >
    FDVEDataValidator & HasAllTags( const FName property_name, const _TAG_CONTAINER_TYPE_ & tag_container, const _TAG_CONTAINER_TYPE_ & expected_tags )
    {
        if ( !tag_container.HasAll( expected_tags ) )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must have all the tags %s" ),
                        *property_name.ToString(),
                        *expected_tags.ToString() ) ) );
        }

        return *this;
    }

    template < typename _KEY_TYPE_, typename _VALUE_TYPE_ >
    FDVEDataValidator & MapHasNoNullKey( const FName property_name, const TMap< _KEY_TYPE_, _VALUE_TYPE_ > & map )
    {
        TArray< _KEY_TYPE_ > keys;
        map.GenerateKeyArray( keys );

        for ( const auto * key : keys )
        {
            if ( IsValueNull( key ) )
            {
                Context.AddError(
                    FText::FromString(
                        FString::Printf( TEXT( "%s must not contain a null key" ),
                            *property_name.ToString() ) ) );
                break;
            }
        }

        return *this;
    }

    template < typename _KEY_TYPE_, typename _VALUE_TYPE_ >
    FDVEDataValidator & MapHasNoNullValue( const FName property_name, const TMap< _KEY_TYPE_, _VALUE_TYPE_ > & map )
    {
        TArray< _VALUE_TYPE_ > values;
        map.GenerateValueArray( values );

        for ( const auto * value : values )
        {
            if ( IsValueNull( value ) )
            {
                Context.AddError(
                    FText::FromString(
                        FString::Printf( TEXT( "%s must not contain a null value" ),
                            *property_name.ToString() ) ) );
                break;
            }
        }

        return *this;
    }

    template < typename _TYPE_ >
    FDVEDataValidator & CustomValidation( _TYPE_ value, TFunctionRef< void( FDataValidationContext &, _TYPE_ ) > custom_validator )
    {
        custom_validator( Context, value );
        return *this;
    }

    template < typename _PARENT_TYPE_, typename _VALUE_TYPE_ >
    FDVEDataValidator & IsSubclassChildOf( const FName property_name, const TSubclassOf< _VALUE_TYPE_ > & value )
    {
        if ( value == nullptr || !value->template IsChildOf< _PARENT_TYPE_ >() )
        {
            Context.AddError(
                FText::FromString(
                    FString::Printf( TEXT( "%s must have be a child of %s" ),
                        *property_name.ToString(),
                        *GetNameSafe( _PARENT_TYPE_::StaticClass() ) ) ) );
        }

        return *this;
    }

    FDVEDataValidator & CombineWith( const UObject * other_object )
    {
        other_object->IsDataValid( Context );
        return *this;
    }

    EDataValidationResult Result() const
    {
        return Context.GetNumErrors() + Context.GetNumWarnings() > 0 ? EDataValidationResult::Invalid : EDataValidationResult::Valid;
    }

private:
    template < typename _VALUE_TYPE_, typename TEnableIf< TIsEnum< _VALUE_TYPE_ >::Value, int >::Type = 0 >
    static FString GetValueToString( _VALUE_TYPE_ value )
    {
        return StaticEnum< _VALUE_TYPE_ >()->GetValueAsString( value );
    }

    template < typename _VALUE_TYPE_, typename TEnableIf< TIsFloatingPoint< _VALUE_TYPE_ >::Value, int >::Type = 0 >
    static FString GetValueToString( _VALUE_TYPE_ value )
    {
        return FString::SanitizeFloat( value, 2 );
    }

    template < typename _VALUE_TYPE_, typename TEnableIf< TIsIntegral< _VALUE_TYPE_ >::Value && TIsSame< bool, _VALUE_TYPE_ >::Value, int >::Type = 0 >
    static FString GetValueToString( _VALUE_TYPE_ value )
    {
        return value ? TEXT( "true" ) : TEXT( "false" );
    }

    template < typename _VALUE_TYPE_, typename TEnableIf< TIsIntegral< _VALUE_TYPE_ >::Value, int >::Type = 0 >
    static FString GetValueToString( _VALUE_TYPE_ value )
    {
        return FString::FromInt( value );
    }

    template < typename _VALUE_TYPE_, typename TEnableIf< TIsPointer< _VALUE_TYPE_ >::Value, int >::Type = 0 >
    static bool IsValueNull( _VALUE_TYPE_ value )
    {
        return value == nullptr;
    }

    template < typename _VALUE_TYPE_, typename TEnableIf< TIsWeakPointerType< _VALUE_TYPE_ >::Value, int >::Type = 0 >
    static bool IsValueNull( _VALUE_TYPE_ value )
    {
        return value.IsNull();
    }

    template < typename _VALUE_TYPE_ >
    static bool IsValueNull( TSubclassOf< _VALUE_TYPE_ > value )
    {
        return value == nullptr;
    }

    template < typename _VALUE_TYPE_ >
    static bool IsValueNull( TObjectPtr< _VALUE_TYPE_ > value )
    {
        return value == nullptr;
    }

    FDataValidationContext & Context;
};

#endif