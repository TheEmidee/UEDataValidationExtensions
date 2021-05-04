#include "DVEAnimMontageValidationHelpers.h"

#include "DVEDataValidator.h"

#include <Animation/AnimMontage.h>

namespace
{
    FString GetConcatenatedNameArray( const TArray< FName > & names )
    {
        FString values;

        for ( const auto name : names )
        {
            values += name.ToString() + " - ";
        }

        return values;
    }
}

void FDVEAnimMontageValidationHelpers::CheckMontageSlots( TArray< FText > & validation_errors, const UAnimMontage * montage, const TArray< FName > & slots )
{
    FDVEDataValidator( validation_errors )
        .HasNumItems( TEXT( "SlotAnimTracks" ), montage->SlotAnimTracks, slots.Num() );

    for ( const auto & slot : montage->SlotAnimTracks )
    {
        if ( !slots.Contains( slot.SlotName ) )
        {
            validation_errors.Emplace( FText::FromString( FString::Printf( TEXT( "%s is not an allowed slot name. Valid slots : %s" ), *slot.SlotName.ToString(), *GetConcatenatedNameArray( slots ) ) ) );
        }
    }
}

bool FDVEAnimMontageValidationHelpers::CheckMontageSectionCount( TArray< FText > & validation_errors, const UAnimMontage * montage, const int section_count )
{
    const auto previous_errors_count = validation_errors.Num();

    FDVEDataValidator( validation_errors )
        .AreEqual( montage->CompositeSections.Num(), section_count, FText::FromString( FString::Printf( TEXT( "The animation montage must have exactly %i sections" ), section_count ) ) );

    return previous_errors_count == validation_errors.Num();
}

void FDVEAnimMontageValidationHelpers::CheckMontageSectionCountModulo( TArray< FText > & validation_errors, const UAnimMontage * montage, const int section_count )
{
    const auto montage_section_count = montage->CompositeSections.Num();

    if ( montage_section_count % section_count != 0 )
    {
        validation_errors.Emplace( FText::FromString( FString::Printf( TEXT( "The animation montage must have a multiple of %i sections" ), section_count ) ) );
    }
}

void FDVEAnimMontageValidationHelpers::CheckMontageSectionNames( TArray< FText > & validation_errors, const UAnimMontage * montage, const TArray< FName > & section_names )
{
    const auto concatenated_section_names = GetConcatenatedNameArray( section_names );
    const auto section_count = montage->CompositeSections.Num();

    auto sections_not_found = section_names;
    TArray< FName > extra_sections;

    for ( auto section_index = 0; section_index < section_count; section_index++ )
    {
        const auto section_name = montage->CompositeSections[ section_index ].SectionName;

        if ( section_names.Contains( section_name ) )
        {
            sections_not_found.Remove( section_name );
        }
        else
        {
            extra_sections.Add( section_name );
        }
    }

    for ( const auto section_name : extra_sections )
    {
        validation_errors.Emplace( FText::FromString( FString::Printf( TEXT( "Section with name '%s' does not belong to valid sections : %s" ), *section_name.ToString(), *concatenated_section_names ) ) );
    }

    for ( const auto section_name : sections_not_found )
    {
        validation_errors.Emplace( FText::FromString( FString::Printf( TEXT( "The required section '%s' was not found" ), *section_name.ToString() ) ) );
    }
}

int FDVEAnimMontageValidationHelpers::GetSectionIndexFromNotifyEventTime( const UAnimMontage * montage, const FAnimNotifyEvent & notify_event )
{
    const auto time = notify_event.GetTime();
    const auto section_index = montage->GetSectionIndexFromPosition( time );

    return section_index;
}

FName FDVEAnimMontageValidationHelpers::GetSectionNameFromNotifyEventTime( const UAnimMontage * montage, const FAnimNotifyEvent & notify_event )
{
    const auto section_index = GetSectionIndexFromNotifyEventTime( montage, notify_event );
    return montage->GetSectionName( section_index );
}