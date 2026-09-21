#pragma once

#include <iostream>
#include <map>
#include <list>

#include "../Utils/Hook.h"

#include "BaseIntelligentPointer.h"
#include "DefIndex.h"
#include "Component.h"
#include "Thing.h"

class CTCInventoryWeapons
{
public:
	char pad0[0x134];

	CBaseIntelligentPointer PActiveMeleeWeapon;
	CDefIndex ActiveMeleeWeaponDefIndex;
	bool MeleeWeaponCarriedOnLoad;
	CBaseIntelligentPointer PActiveRangedWeapon;

	void AddSetThingAsActiveWeaponCallback(const std::string& id, std::function<void(CTCInventoryWeapons*, long)> callback) { setThingAsActiveWeaponCallbacks[id] = callback; }
	void RemoveSetThingAsActiveWeaponCallback(const std::string& id) { setThingAsActiveWeaponCallbacks.erase(id); }

	void SetThingAsActiveWeapon(long weapon_def_index, NUISystem::CComponent* pcomponent);
	CThing* GetItemOfTypeInInventory(long def_index);

	static void Hook();

private:
	static std::map<std::string, std::function<void(CTCInventoryWeapons*, long)>> setThingAsActiveWeaponCallbacks;

	static void(__thiscall* OSetThingAsActiveWeapon)(CTCInventoryWeapons*, long, NUISystem::CComponent*);
	static void __fastcall HSetThingAsActiveWeapon(CTCInventoryWeapons* _this, void* _EDX, long weapon_def_index, NUISystem::CComponent* pcomponent);

	static CThing* (__thiscall* OGetItemOfTypeInInventory)(CTCInventoryWeapons*, long);
	static CThing* __fastcall HGetItemOfTypeInInventory(CTCInventoryWeapons* _this, void* _EDX, long def_index);
};
