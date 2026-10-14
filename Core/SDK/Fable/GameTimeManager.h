#pragma once

#include <iostream>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

class CGameTimeManager
{
public:
	char pad0[0x8];
	float Time;
	char pad1[0x30];

	void AddUpdateCallback(const std::string& id, std::function<void()> callback) { updateCallbacks[id] = callback; }
	void RemoveUpdateCallback(const std::string& id) { updateCallbacks.erase(id); }

    static void Hook();

private:
	static std::map<std::string, std::function<void()>> updateCallbacks;

	static void(__thiscall* OUpdate)(CGameTimeManager*, float);
	static void __fastcall HUpdate(CGameTimeManager* _this, void* _EDX, float elapsed_time_secs);
};
