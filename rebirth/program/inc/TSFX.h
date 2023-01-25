#pragma once

#include "SoundFX.h"

class GameBase;

namespace TSFX
{
	extern SFX_HANDLE PlayAt(DWORD sfxTag, const TMat3F& transform, const Vector3F& vel);

	extern void serverPlaySound(DWORD, GameBase*, int);
	extern void serverPlaySound(DWORD, Point3F);
}
