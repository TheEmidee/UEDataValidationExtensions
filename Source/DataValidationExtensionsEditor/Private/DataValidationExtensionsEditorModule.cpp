#include "DataValidationExtensionsEditorModule.h"

class FDataValidationExtensionsEditorModule final : public IDataValidationExtensionsEditorModule
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};

IMPLEMENT_MODULE( FDataValidationExtensionsEditorModule, DataValidationExtensionsEditor )

void FDataValidationExtensionsEditorModule::StartupModule()
{
}

void FDataValidationExtensionsEditorModule::ShutdownModule()
{
}