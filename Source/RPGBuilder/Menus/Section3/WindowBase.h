#pragma once
#include "RPGBuilder.h"
#include "RPGBuilderInterface.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Docking/SDockTab.h"

class FWindowBase : public IRPGBuilderListenerInterface, public TSharedFromThis<FWindowBase>
{
public:
	
	virtual ~FWindowBase() {}; // The compiler keeps crying about virtual destructors "warning C2465" if you know a better way to dry the tears feel free to let me know

	virtual void OnStartupModule() override
	{
		Initialize();
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(WindowName, FOnSpawnTab::CreateRaw(this, &FWindowBase::SpawnTab)).SetGroup(FRPGBuilderModule::Get().GetMenuRoot()).SetDisplayName(WindowDisplayName).SetTooltipText(ToolTipText);
	}

	virtual void OnShutdownModule() override
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(WindowName);
	}

	virtual void Initialize() {};

	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) { return SNew(SDockTab); }

	virtual void MakeMenuEntry(FMenuBuilder& MenuBuilder)
	{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(MenuBuilder, WindowName);
	}

protected:
	
	FName WindowName;
	FText WindowDisplayName;
	FText ToolTipText;

};