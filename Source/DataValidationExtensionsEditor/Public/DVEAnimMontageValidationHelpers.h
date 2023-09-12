#pragma once

#include <CoreMinimal.h>

struct FAnimNotifyEvent;
class UAnimMontage;

struct DATAVALIDATIONEXTENSIONSEDITOR_API FDVEAnimMontageValidationHelpers
{
    static void CheckMontageSlots( FDataValidationContext & context, const UAnimMontage * montage, const TArray< FName > & slots );
    static bool CheckMontageSectionCount( FDataValidationContext & context, const UAnimMontage * montage, const int section_count );
    static void CheckMontageSectionCountModulo( FDataValidationContext & context, const UAnimMontage * montage, const int section_count );
    static void CheckMontageSectionNames( FDataValidationContext & context, const UAnimMontage * montage, const TArray< FName > & section_names );
    static int GetSectionIndexFromNotifyEventTime( const UAnimMontage * montage, const FAnimNotifyEvent & notify_event );
    static FName GetSectionNameFromNotifyEventTime( const UAnimMontage * montage, const FAnimNotifyEvent & notify_event );
};