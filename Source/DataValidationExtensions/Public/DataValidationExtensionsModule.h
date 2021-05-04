#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <Stats/Stats.h>

class DATAVALIDATIONEXTENSIONS_API IDataValidationExtensionsModule : public IModuleInterface
{

public:
    static IDataValidationExtensionsModule & Get()
    {
        QUICK_SCOPE_CYCLE_COUNTER( STAT_IDataValidationExtensionsModule_Get );
        static auto & singleton = FModuleManager::LoadModuleChecked< IDataValidationExtensionsModule >( "MapCheckValidation" );
        return singleton;
    }

    static bool IsAvailable()
    {
        QUICK_SCOPE_CYCLE_COUNTER( STAT_IDataValidationExtensionsModule_IsAvailable );
        return FModuleManager::Get().IsModuleLoaded( "MapCheckValidation" );
    }
};
