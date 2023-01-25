#pragma once

#include "SimConsolePlugin.h"
#include "FearMissionEditor.h"

class FearMissionPlugin : public SimConsolePlugin
{
	enum
	{
		Create,
		RegisterType,
		SetGrabMask,
		SetPlaceMask,
		SetDefaultPlaceMask,
		GetConsoleOptions,
		ObjectToCamera,
		CameraToObject,
		ObjectToSC,
		CreateObject,
		onSelected,
		onUnselected,
		onSelectionCleared,
		onUseTerrainGrid,
		DeleteSelection,
		CopySelection,
		PasteFile,
		CutSelection,
		PasteSelection,
		DuplicateSelection,
		DropSelection,
		CreateGroup,
		PlaceBookmark,
		GotoBookmark,
		Undo,
		Redo,
		Save,
		MissionLight,
		RebuildCommandMap
	};

	void init() override;
	const char * consoleCallback(CMDConsole *, int id, int argc, const char * argv[]) override;
};
