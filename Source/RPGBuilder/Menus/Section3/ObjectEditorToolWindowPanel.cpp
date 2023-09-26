#include "ObjectEditorToolWindowPanel.h"

void ObjectEditorToolWindowPanel::Construct(const FArguments& InArgs)
{
	tool = InArgs._Tool;
	if (tool.IsValid())
	{
		// Add some stuff here probably
		//FOnClicked::CreateSP(this, &ObjectEditorToolWindowPanel::OnClicked);  //Don't need this but leaving it here until I finish just in case I do
	}

	ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot().VAlign(VAlign_Top).Padding(15.f)
		[
			SNew(SBorder).BorderBackgroundColor(FColor(192, 192, 192, 255))
			[
				SNew(SButton).Text(FText::FromString(TEXT("Edit Party System"))).OnClicked(this, &ObjectEditorToolWindowPanel::OnClicked)
			]

		]
		];

}

FReply ObjectEditorToolWindowPanel::OnClicked(/**const FGeometry& MyGeometry, const FPointerEvent& MouseEvent*/)
{
		FGlobalTabmanager::Get()->TryInvokeTab(FTabId("Party System"));
		UE_LOG(LogTemp, Warning, TEXT("OnClicked()"))
		return FReply::Handled();
}

TSharedRef<SDockTab> ObjectEditorToolWindowPanel::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			SNew(WindowPanelBase).Tool(tool)
		];
	//TODO: Add switch to log returned Enum
	//UE_LOG(LogClass, Log, TEXT("Opened %s"), *ToolTipText.ToString());

	return SpawnedTab;
}