#pragma once

#include "SimConsolePlugin.h"

namespace SimGui
{
	class Canvas;
}

class FearPlugin : public SimConsolePlugin
{
public:
	void init() override;
	void startFrame() override;
	void endFrame() override;
	const char * consoleCallback(CMDConsole*, int id, int argc, const char *argv[]) override;
};
