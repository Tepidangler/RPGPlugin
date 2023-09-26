#pragma once
#include "RPGBuilderInterface.h"
#include "GameProjectGenerationModule.h"

class MenuTool : public IRPGBuilderListenerInterface, public TSharedFromThis<MenuTool>
{
public:
	virtual ~MenuTool() {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	void MakeMenuEntry(FMenuBuilder& MenuBuilder);

	void MakeSubMenu(FMenuBuilder& MenuBuilder);

protected:
	
	TSharedPtr<FUICommandList> CommandList;


	void MapCommands();

	void MenuCommand1();

	void MenuCommand2();

	void MenuCommand3();
};