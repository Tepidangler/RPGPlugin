#pragma once
#include "Widgets/Docking/SDockTab.h"
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 2
#else
#include "Widgets/Docking/SDockableTab.h"
#include "Widgets/Docking/SDockTabStack.h"
#endif
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Workflow/SWizard.h"
#include "Framework/Application/SWindowTitleBar.h"
#include "Widgets/Input/SDirectoryPicker.h"
#include "GameProjectGenerationModule.h"
#include "ObjectEditorTool.h"

class WindowPanelBase : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(WindowPanelBase)
	{}
	SLATE_ARGUMENT(TWeakPtr<class ObjectEditorTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:

	TWeakPtr<ObjectEditorTool> tool;
};