#include "GameTimeManager.h"

std::map<std::string, std::function<void()>> CGameTimeManager::updateCallbacks;

void(__thiscall* CGameTimeManager::OUpdate)(CGameTimeManager*, float) = nullptr;
void CGameTimeManager::HUpdate(CGameTimeManager* _this, void* _EDX, float elapsed_time_secs)
{
	for (const auto& pair : updateCallbacks)
	{
		if (pair.second)
			pair.second();
	}

	OUpdate(_this, elapsed_time_secs);
}

void CGameTimeManager::Hook()
{
	ADD_HOOK(0x006BB990, HUpdate, OUpdate);
}
