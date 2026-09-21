#pragma once

#include <iostream>
#include <vector>

#include "../Utils/Hook.h"

#include "Thing.h"

namespace NInventory
{
	enum EInventorySelectionState : int32_t
	{
		INVENTORY_SELECTION_STATE_CATEGORIES = 0x0,
		INVENTORY_SELECTION_STATE_ITEMS = 0x1,
		INVENTORY_SELECTION_STATE_MAX_STATES = 0x2
	};

	enum ESelectionState : int32_t
	{
		SELECTION_STATE_NONE = 0x0,
		SELECTION_STATE_OFF = 0x1,
		SELECTION_STATE_ON = 0x2,
		SELECTION_STATE_SEL = 0x3,
		SELECTION_STATE_MAX = 0x4
	};

	class CTCInventoryBase
	{
	public:
		char pad1[0x6C];

		int GlobalDefIndex;

		char pad2[0xC0];

		long GetNumberOfItemsOfTypeInInventory(long global_index);
		CThing* GetItemOfTypeInInventory(long def_index);

		static void Hook();

	private:
		static long(__thiscall* OGetNumberOfItemsOfTypeInInventory)(CTCInventoryBase*, long);
		static long __fastcall HGetNumberOfItemsOfTypeInInventory(CTCInventoryBase* _this, void* _EDX, long global_index);

		static CThing* (__thiscall* OGetItemOfTypeInInventory)(CTCInventoryBase*, long);
		static CThing* __fastcall HGetItemOfTypeInInventory(CTCInventoryBase* _this, void* _EDX, long def_index);
	};
}