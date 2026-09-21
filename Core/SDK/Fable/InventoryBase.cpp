#include "InventoryBase.h"

long(__thiscall* NInventory::CTCInventoryBase::OGetNumberOfItemsOfTypeInInventory)(NInventory::CTCInventoryBase*, long) = nullptr;
long __fastcall NInventory::CTCInventoryBase::HGetNumberOfItemsOfTypeInInventory(NInventory::CTCInventoryBase* _this, void* _EDX, long global_index)
{
	return OGetNumberOfItemsOfTypeInInventory(_this, global_index);
}

long NInventory::CTCInventoryBase::GetNumberOfItemsOfTypeInInventory(long global_index)
{
	return OGetNumberOfItemsOfTypeInInventory(this, global_index);
}

CThing* (__thiscall* NInventory::CTCInventoryBase::OGetItemOfTypeInInventory)(NInventory::CTCInventoryBase*, long) = nullptr;
CThing* __fastcall NInventory::CTCInventoryBase::HGetItemOfTypeInInventory(NInventory::CTCInventoryBase* _this, void* _EDX, long def_index)
{
	return OGetItemOfTypeInInventory(_this, def_index);
}

CThing* NInventory::CTCInventoryBase::GetItemOfTypeInInventory(long def_index)
{
	return OGetItemOfTypeInInventory(this, def_index);
}

void NInventory::CTCInventoryBase::Hook()
{
	ADD_HOOK(0x005BDF08, HGetNumberOfItemsOfTypeInInventory, OGetNumberOfItemsOfTypeInInventory);
	ADD_HOOK(0x005BF3F1, HGetItemOfTypeInInventory, OGetItemOfTypeInInventory);
}
