#pragma once
#include "WindowBase.h"

class ObjectEditorTool : public FWindowBase
{
public:
	virtual ~ObjectEditorTool() {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;
	virtual void Initialize() override;
	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs) override;
};