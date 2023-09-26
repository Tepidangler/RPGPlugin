#pragma once
#include "WindowPanelBase.h"

class ObjectEditorToolWindowPanel : public WindowPanelBase
{
	SLATE_BEGIN_ARGS(ObjectEditorToolWindowPanel)
	{}
	SLATE_ARGUMENT(TWeakPtr<class ObjectEditorTool>, Tool)
		SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	FReply OnClicked(/**const FGeometry& MyGeometry, const FPointerEvent& MouseEvent*/);
	TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs);

protected:

	TWeakPtr<ObjectEditorTool> tool;
};