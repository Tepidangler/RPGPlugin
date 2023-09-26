#pragma once
#include "RPGBuilderInterface.h"
#include "GameProjectGenerationModule.h"

class CharTools : public IRPGBuilderListenerInterface, public TSharedFromThis<CharTools>
{
public:
	virtual ~CharTools() {}

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
	
	void MenuCommand4();
	
	void MenuCommand5();

	void MenuCommand6();

	void MenuCommand7();

	void MenuCommand8();
};