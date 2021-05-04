#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleInterface.h>
#include <Modules/ModuleManager.h>
#include <Stats/Stats.h>

class IDataValidationExtensionsEditorModule : public IModuleInterface
{

public:
    static IDataValidationExtensionsEditorModule & Get()
    {
        static auto & singleton = FModuleManager::LoadModuleChecked< IDataValidationExtensionsEditorModule >( "DataValidationExtensionsEditor" );
        return singleton;
    }

    static bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded( "DataValidationExtensionsEditor" );
    }
};
