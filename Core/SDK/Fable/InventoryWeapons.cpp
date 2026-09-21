#include "InventoryWeapons.h"
#include "InventoryBase.h"

std::map<std::string, std::function<void(CTCInventoryWeapons*, long)>> CTCInventoryWeapons::setThingAsActiveWeaponCallbacks;

void(__thiscall* CTCInventoryWeapons::OSetThingAsActiveWeapon)(CTCInventoryWeapons*, long, NUISystem::CComponent*) = nullptr;
void __fastcall CTCInventoryWeapons::HSetThingAsActiveWeapon(CTCInventoryWeapons* _this, void* _EDX, long weapon_def_index, NUISystem::CComponent* pcomponent)
{
	for (const auto& pair : setThingAsActiveWeaponCallbacks)
	{
		if (pair.second)
			pair.second(_this, weapon_def_index);
	}

	OSetThingAsActiveWeapon(_this, weapon_def_index, pcomponent);
}

void CTCInventoryWeapons::SetThingAsActiveWeapon(long weapon_def_index, NUISystem::CComponent* pcomponent)
{
	OSetThingAsActiveWeapon(this, weapon_def_index, pcomponent);
}

CThing* (__thiscall* CTCInventoryWeapons::OGetItemOfTypeInInventory)(CTCInventoryWeapons*, long) = nullptr;
CThing* __fastcall CTCInventoryWeapons::HGetItemOfTypeInInventory(CTCInventoryWeapons* _this, void* _EDX, long def_index)
{
	return OGetItemOfTypeInInventory(_this, def_index);
}

CThing* CTCInventoryWeapons::GetItemOfTypeInInventory(long def_index)
{
	return OGetItemOfTypeInInventory(this, def_index);
}

void CTCInventoryWeapons::Hook()
{
	ADD_HOOK(0x005CB2B0, HSetThingAsActiveWeapon, OSetThingAsActiveWeapon);
	ADD_HOOK(0x005C311A, HGetItemOfTypeInInventory, OGetItemOfTypeInInventory);
}
