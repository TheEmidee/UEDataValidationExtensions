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

void FDVEAnimMontageValidationHelpers::CheckMontageSlots( FDataValidationContext & context, const UAnimMontage * montage, const TArray< FName > & slots )
{
    FDVEDataValidator( context )
        .HasNumItems( TEXT( "SlotAnimTracks" ), montage->SlotAnimTracks, slots.Num() );

    for ( const auto & slot : montage->SlotAnimTracks )
    {
        if ( !slots.Contains( slot.SlotName ) )
        {
            context.AddError( FText::FromString( FString::Printf( TEXT( "%s is not an allowed slot name. Valid slots : %s" ), *slot.SlotName.ToString(), *GetConcatenatedNameArray( slots ) ) ) );
        }
    }
}

bool FDVEAnimMontageValidationHelpers::CheckMontageSectionCount( FDataValidationContext & context, const UAnimMontage * montage, const int section_count )
{
    const auto previous_errors_count = context.GetNumErrors();

    FDVEDataValidator( context )
        .AreEqual( montage->CompositeSections.Num(), section_count, FText::FromString( FString::Printf( TEXT( "The animation montage must have exactly %i sections" ), section_count ) ) );

    return previous_errors_count == context.GetNumErrors();
}

void FDVEAnimMontageValidationHelpers::CheckMontageSectionCountModulo( FDataValidationContext & context, const UAnimMontage * montage, const int section_count )
{
    const auto montage_section_count = montage->CompositeSections.Num();

    if ( montage_section_count % section_count != 0 )
    {
        context.AddError( FText::FromString( FString::Printf( TEXT( "The animation montage must have a multiple of %i sections" ), section_count ) ) );
    }
}

void FDVEAnimMontageValidationHelpers::CheckMontageSectionNames( FDataValidationContext & context, const UAnimMontage * montage, const TArray< FName > & section_names )
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
        context.AddError( FText::FromString( FString::Printf( TEXT( "Section with name '%s' does not belong to valid sections : %s" ), *section_name.ToString(), *concatenated_section_names ) ) );
    }

    for ( const auto section_name : sections_not_found )
    {
        context.AddError( FText::FromString( FString::Printf( TEXT( "The required section '%s' was not found" ), *section_name.ToString() ) ) );
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