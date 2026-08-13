#include "CreatureAction_SheatheItemToInventory.h"

CCreatureAction_SheatheItemToInventory::CCreatureAction_SheatheItemToInventory(CThingCreatureBase& creature, CCreatureActionBase* pfollow_up_action, long interruption_group_id)
{
    OSheatheItemToInventory_1(this, creature, pfollow_up_action, interruption_group_id);
}

void (__thiscall* CCreatureAction_SheatheItemToInventory::OSheatheItemToInventory_1)(CCreatureAction_SheatheItemToInventory*, CThingCreatureBase&, CCreatureActionBase*, long) = nullptr;
void __fastcall CCreatureAction_SheatheItemToInventory::HSheatheItemToInventory_1(CCreatureAction_SheatheItemToInventory* _this, void* _EDX, CThingCreatureBase& creature, CCreatureActionBase* pfollow_up_action, long interruption_group_id)
{
    OSheatheItemToInventory_1(_this, creature, pfollow_up_action, interruption_group_id);
}

CCreatureAction_SheatheItemToInventory::CCreatureAction_SheatheItemToInventory(CThingCreatureBase& creature, const CCharString& anim_name, CCreatureActionBase* pfollow_up_action, long interruption_group_id)
{
    OSheatheItemToInventory_2(this, creature, anim_name, pfollow_up_action, interruption_group_id);
}

void (__thiscall* CCreatureAction_SheatheItemToInventory::OSheatheItemToInventory_2)(CCreatureAction_SheatheItemToInventory*, CThingCreatureBase&, const CCharString&, CCreatureActionBase*, long) = nullptr;
void __fastcall CCreatureAction_SheatheItemToInventory::HSheatheItemToInventory_2(CCreatureAction_SheatheItemToInventory* _this, void* _EDX, CThingCreatureBase& creature, const CCharString& anim_name, CCreatureActionBase* pfollow_up_action, long interruption_group_id)
{
    OSheatheItemToInventory_2(_this, creature, anim_name, pfollow_up_action, interruption_group_id);
}

CCreatureAction_SheatheItemToInventory::CCreatureAction_SheatheItemToInventory(const CCreatureAction_SheatheItemToInventory& __that)
{
    OSheatheItemToInventory_3(this, __that);
}

void (__thiscall* CCreatureAction_SheatheItemToInventory::OSheatheItemToInventory_3)(CCreatureAction_SheatheItemToInventory*, const CCreatureAction_SheatheItemToInventory&) = nullptr;
void __fastcall CCreatureAction_SheatheItemToInventory::HSheatheItemToInventory_3(CCreatureAction_SheatheItemToInventory* _this, void* _EDX, const CCreatureAction_SheatheItemToInventory& __that)
{
    OSheatheItemToInventory_3(_this, __that);
}

void CCreatureAction_SheatheItemToInventory::Hook()
{
    ADD_HOOK(0x0069FFD0, HSheatheItemToInventory_1, OSheatheItemToInventory_1);
    ADD_HOOK(0x0069EF80, HSheatheItemToInventory_2, OSheatheItemToInventory_2);
    ADD_HOOK(0x006A0C50, HSheatheItemToInventory_3, OSheatheItemToInventory_3);
}
