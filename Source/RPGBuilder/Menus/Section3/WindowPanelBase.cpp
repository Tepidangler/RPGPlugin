#include "WindowPanelBase.h"
#include "ObjectEditorTool.h"


void WindowPanelBase::Construct(const FArguments& InArgs)
{
	tool = InArgs._Tool;
	if (tool.IsValid())
	{
		// Add some stuff here probably
	}
}