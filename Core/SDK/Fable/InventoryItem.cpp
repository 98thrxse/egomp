#include "InventoryItem.h"

bool(__thiscall* CTCInventoryItem::OAddToInventory)(
	CTCInventoryItem*,
	NInventory::CTCInventoryBase&,
	bool,
	bool,
	long,
	bool,
	bool
	) = nullptr;

bool __fastcall CTCInventoryItem::HAddToInventory(
	CTCInventoryItem* _this,
	void* _EDX,
	NInventory::CTCInventoryBase& inventory,
	bool add_selected,
	bool add_quick_access,
	long price_bought_for,
	bool silent,
	bool persist_item
)
{
	return OAddToInventory(_this, inventory, add_selected, add_quick_access, price_bought_for, silent, persist_item);
}

bool CTCInventoryItem::AddToInventory(
	NInventory::CTCInventoryBase& inventory,
	bool add_selected,
	bool add_quick_access,
	long price_bought_for,
	bool silent,
	bool persist_item
)
{
	return OAddToInventory(this, inventory, add_selected, add_quick_access, price_bought_for, silent, persist_item);
}

bool(__fastcall* CTCInventoryItem::OIsWeapon)(
	long
	) = nullptr;

bool __fastcall CTCInventoryItem::HIsWeapon(
	long def_index
)
{
	return OIsWeapon(def_index);
}

bool(__fastcall* CTCInventoryItem::OIsTrophy)(
	long
	) = nullptr;

bool __fastcall CTCInventoryItem::HIsTrophy(
	long def_index
)
{
	return OIsTrophy(def_index);
}

bool CTCInventoryItem::IsWeapon(long def_index)
{
	return OIsWeapon(def_index);
}

bool CTCInventoryItem::IsTrophy(long def_index)
{
	return OIsTrophy(def_index);
}

void CTCInventoryItem::Hook()
{
	ADD_HOOK(0x005D8D50, HAddToInventory, OAddToInventory);
	ADD_HOOK(0x005D97F0, HIsWeapon, OIsWeapon);
	ADD_HOOK(0x005D9930, HIsTrophy, OIsTrophy);
}
