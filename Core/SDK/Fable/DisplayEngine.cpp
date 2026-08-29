#include "DisplayEngine.h"

CIEngine* CDisplayEngine::Get3DEngine()
{
	return *(CIEngine**)((char*)this + 0x2C);
}

void CDisplayEngine::Hook()
{
}
