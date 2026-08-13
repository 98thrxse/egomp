#include "ThingCreatureBase.h"

std::map<std::string, std::function<void(CThingCreatureBase*, CCreatureActionBase const&)>> CThingCreatureBase::setCurrentActionCallbacks;

void(__thiscall* CThingCreatureBase::OUpdateAnimation)(CThingCreatureBase*, float) = nullptr;
void __fastcall CThingCreatureBase::HUpdateAnimation(CThingCreatureBase* _this, void* _EDX, float distance_from_player)
{
	OUpdateAnimation(_this, distance_from_player);
}

bool(__thiscall* CThingCreatureBase::OSetCurrentAction)(CThingCreatureBase*, CCreatureActionBase const&) = nullptr;
bool __fastcall CThingCreatureBase::HSetCurrentAction(CThingCreatureBase* _this, void* _EDX, CCreatureActionBase const& action)
{
	for (const auto& pair : setCurrentActionCallbacks)
	{
		if (pair.second)
			pair.second(_this, action);
	}

	return OSetCurrentAction(_this, action);
}

bool CThingCreatureBase::SetCurrentAction(CCreatureActionBase const& action)
{
	return OSetCurrentAction(this, action);
}

void CThingCreatureBase::Hook()
{
	ADD_HOOK(0x00665860, HUpdateAnimation, OUpdateAnimation);
	ADD_HOOK(0x006644F0, HSetCurrentAction, OSetCurrentAction);
}
