#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

#include "3DVector.h"
#include "CreatureActionBase.h"

class CThingCreatureBase
{
public:
	char pad[0x10C];
	C3DVector MovementVector;

	bool SetCurrentAction(CCreatureActionBase const&);

	void AddSetCurrentActionCallback(const std::string& id, std::function<void(CThingCreatureBase*, CCreatureActionBase const&)> callback) { setCurrentActionCallbacks[id] = callback; }
	void RemoveSetCurrentActionCallback(const std::string& id) { setCurrentActionCallbacks.erase(id); }

    static void Hook();

private:
	static std::map<std::string, std::function<void(CThingCreatureBase*, CCreatureActionBase const&)>> setCurrentActionCallbacks;

	static void(__thiscall* OUpdateAnimation)(CThingCreatureBase*, float);
	static void __fastcall HUpdateAnimation(CThingCreatureBase* _this, void* _EDX, float distance_from_player);

	static bool(__thiscall* OSetCurrentAction)(CThingCreatureBase*, CCreatureActionBase const&);
	static bool __fastcall HSetCurrentAction(CThingCreatureBase* _this, void* _EDX, CCreatureActionBase const& action);
};
