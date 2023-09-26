#include "ObjectEditorTool.h"
#include "RPGBuilder.h"
#include "ObjectEditorToolWindowPanel.h"
#include "WindowPanelBase.h"


#define LOCTEXT_NAMESPACE "ObjectEditorTool"

void ObjectEditorTool::OnStartupModule()
{
	FWindowBase::OnStartupModule(); //Super::OnStartupModule() would probably work here as well. You know, in an effort to keep everything UE-y
	FRPGBuilderModule::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &ObjectEditorTool::MakeMenuEntry), FName("Edit Objects"));

}
void ObjectEditorTool::OnShutdownModule()
{
	FWindowBase::OnShutdownModule();
}


void ObjectEditorTool::Initialize()
{
	WindowName = "ObjectVariableEditor";
	WindowDisplayName = FText::FromString("Object Variable Editor");
	ToolTipText = FText::FromString("Object Variable Editor Window");
}

TSharedRef<SDockTab> ObjectEditorTool::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			SNew(WindowPanelBase).Tool(SharedThis(this))
		];
	//TODO: Add switch to log returned Enum
	UE_LOG(LogClass, Log, TEXT("Opened %s"), *ToolTipText.ToString());

	return SpawnedTab;
}



#undef LOCTEXT_NAMESPACE