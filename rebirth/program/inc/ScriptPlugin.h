#pragma once

#include "SimConsolePlugin.h"

class ScriptPlugin : public SimConsolePlugin
{
	typedef SimConsolePlugin Parent;

	friend class FearGame;

	ScriptPlugin();

protected:
	void init() override;
	
public:	
	virtual ~ScriptPlugin();
};
