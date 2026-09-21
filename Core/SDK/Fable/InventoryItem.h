#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "InventoryBase.h"

class CTCInventoryItem
{
public:
	char pad[0x28];

	bool AddToInventory(
		NInventory::CTCInventoryBase& inventory,
		bool add_selected,
		bool add_quick_access,
		long price_bought_for,
		bool silent,
		bool persist_item
	);

	static bool IsWeapon(long def_index);
	static bool IsTrophy(long def_index);

	static void Hook();

private:
	static bool(__thiscall* OAddToInventory)(
		CTCInventoryItem*,
		NInventory::CTCInventoryBase&,
		bool,
		bool,
		long,
		bool,
		bool
		);

	static bool __fastcall HAddToInventory(
		CTCInventoryItem* _this,
		void* _EDX,
		NInventory::CTCInventoryBase& inventory,
		bool add_selected,
		bool add_quick_access,
		long price_bought_for,
		bool silent,
		bool persist_item
	);

	static bool(__fastcall* OIsWeapon)(
		long
		);

	static bool __fastcall HIsWeapon(
		long def_index
	);

	static bool(__fastcall* OIsTrophy)(
		long
		);

	static bool __fastcall HIsTrophy(
		long def_index
	);
};
