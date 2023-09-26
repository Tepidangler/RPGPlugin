#pragma once
#include "Modules/ModuleManager.h"

class IRPGBuilderListenerInterface
{
public:
    virtual void OnStartupModule() {};
    virtual void OnShutdownModule() {};

};

class IRPGBuilderModuleInterface : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    void StartupModule() override
    {
        if (!IsRunningCommandlet())
        {
            AddModuleListeners();
            for (int32 x = 0; x < ModuleListeners.Num(); ++x)
            {
                ModuleListeners[x]->OnStartupModule();
            }
        }
    }
    void ShutdownModule() override
    {
        for (int32 x = 0; x < ModuleListeners.Num(); ++x)
        {
            ModuleListeners[x]->OnShutdownModule();
        }
    }

    virtual void AddModuleListeners() {};

protected:

    TArray<TSharedRef<IRPGBuilderListenerInterface>> ModuleListeners;
};