#include "DataValidationExtensionsModule.h"

class FDataValidationExtensionsModule final : public IDataValidationExtensionsModule
{
public:
    void StartupModule() override;
    void ShutdownModule() override;
};

IMPLEMENT_MODULE( FDataValidationExtensionsModule, DataValidationExtensions )

void FDataValidationExtensionsModule::StartupModule()
{
}

void FDataValidationExtensionsModule::ShutdownModule()
{
}