#pragma once

#include "simConsolePlugin.h"
#include "AIObj.h"


class AIPlugin : public SimConsolePlugin
{
	typedef const char* (AIPlugin::*HandleCmdFunc)(AIObj* ai, int argc, const char* argv[]);
	
	AIManager* aim;

	AIObj* getAI(const char* aiName);

	const char* onGetId(int argc, const char** argv);
	const char* onGetTarget(int argc, const char** argv);
	const char* onFetchObject(int argc, const char** argv);
	const char* onList(int, const char**);
	const char* onSpawnAI(int argc, const char** argv);
	const char* onAttackPlayer(AIObj * ai, int argc, const char * argv[]);
	const char* onDeleteAI(AIObj* ai, int, const char**);
	const char* onGetAICount(int, const char**);
	const char* onFollowDirective(AIObj * ai, int argc, const char * argv[]);
	const char* onWaypointDirective(AIObj * ai, int argc, const char * argv[]);
	const char* onTargetDirective(AIObj * ai, int argc, const char * argv[]);
	const char* onTargetDirectiveLaser(AIObj * ai, int argc, const char * argv[]);
	const char* onTargetDirectivePoint(AIObj * ai, int argc, const char * argv[]);
	const char* onGuardDirective(AIObj * ai, int argc, const char * argv[]);
	const char* onRemoveDirective(AIObj * ai, int argc, const char * argv[]);
	const char* onListDirectives(AIObj * ai, int argc, const char * argv[]);
	const char* onCallbackDied(AIObj * ai, int argc, const char * argv[]);
	const char* onCallbackBored(AIObj * ai, int argc, const char * argv[]);
	const char* onCallbackAmbient(AIObj * ai, int argc, const char * argv[]);
	const char* onCallbackPeriodic(AIObj * ai, int argc, const char * argv[]);
	const char* installDCB(AIObj * ai, int whichDCB, int argc, const char * argv[]);
	const char* onDirectiveCallback1(AIObj * ai, int argc, const char * argv[]);
	const char* onDirectiveCallback2(AIObj * ai, int argc, const char * argv[]);
	const char* onDirectiveCallback3(AIObj * ai, int argc, const char * argv[]);
	const char* onDirectiveCallback4(AIObj * ai, int argc, const char * argv[]);
	const char* onSetVariable(AIObj * ai, int argc, const char * argv[]);
	const char* onCallWithId(AIObj * ai, int argc, const char * argv[]);
	const char* onSetAutomaticTargets(AIObj* ai, int, const char**);
	const char* onSetSciptedTargets(AIObj* ai, int, const char**);

protected:
	void startFrame() override;
	void endFrame() override;
	void init() override;
	const char * consoleCallback(CMDConsole *, int id, int argc, const char * argv[]) override;

public:
	AIPlugin();
	virtual ~AIPlugin();
};
