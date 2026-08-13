#include "CreatureAction_UnsheatheItemFromInventory.h"

CCreatureAction_UnsheatheItemFromInventory::CCreatureAction_UnsheatheItemFromInventory(CThingCreatureBase& creature, CThing& unsheathe_item, CCreatureActionBase* pfollow_up_action, long interruption_priority)
{
    OUnsheatheItemFromInventory_1(this, creature, unsheathe_item, pfollow_up_action, interruption_priority);
}

void (__thiscall* CCreatureAction_UnsheatheItemFromInventory::OUnsheatheItemFromInventory_1)(CCreatureAction_UnsheatheItemFromInventory*, CThingCreatureBase&, CThing&, CCreatureActionBase*, long) = nullptr;
void __fastcall CCreatureAction_UnsheatheItemFromInventory::HUnsheatheItemFromInventory_1(CCreatureAction_UnsheatheItemFromInventory* _this, void* _EDX, CThingCreatureBase& creature, CThing& unsheathe_item, CCreatureActionBase* pfollow_up_action, long interruption_priority)
{
    OUnsheatheItemFromInventory_1(_this, creature, unsheathe_item, pfollow_up_action, interruption_priority);
}

CCreatureAction_UnsheatheItemFromInventory::CCreatureAction_UnsheatheItemFromInventory(CThingCreatureBase& creature, const CCharString& anim_name, CThing& unsheathe_item, long interruption_group_id, long interruption_priority, CCreatureActionBase* pfollow_up_action)
{
    OUnsheatheItemFromInventory_2(this, creature, anim_name, unsheathe_item, interruption_group_id, interruption_priority, pfollow_up_action);
}

void (__thiscall* CCreatureAction_UnsheatheItemFromInventory::OUnsheatheItemFromInventory_2)(CCreatureAction_UnsheatheItemFromInventory*, CThingCreatureBase&, const CCharString&, CThing&, long, long, CCreatureActionBase*) = nullptr;
void __fastcall CCreatureAction_UnsheatheItemFromInventory::HUnsheatheItemFromInventory_2(CCreatureAction_UnsheatheItemFromInventory* _this, void* _EDX, CThingCreatureBase& creature, const CCharString& anim_name, CThing& unsheathe_item, long interruption_group_id, long interruption_priority, CCreatureActionBase* pfollow_up_action)
{
    OUnsheatheItemFromInventory_2(_this, creature, anim_name, unsheathe_item, interruption_group_id, interruption_priority, pfollow_up_action);
}

CCreatureAction_UnsheatheItemFromInventory::CCreatureAction_UnsheatheItemFromInventory(const CCreatureAction_UnsheatheItemFromInventory& __that)
{
    OUnsheatheItemFromInventory_3(this, __that);
}

void (__thiscall* CCreatureAction_UnsheatheItemFromInventory::OUnsheatheItemFromInventory_3)(CCreatureAction_UnsheatheItemFromInventory*, const CCreatureAction_UnsheatheItemFromInventory&) = nullptr;
void __fastcall CCreatureAction_UnsheatheItemFromInventory::HUnsheatheItemFromInventory_3(CCreatureAction_UnsheatheItemFromInventory* _this, void* _EDX, const CCreatureAction_UnsheatheItemFromInventory& __that)
{
    OUnsheatheItemFromInventory_3(_this, __that);
}

void CCreatureAction_UnsheatheItemFromInventory::Hook()
{
    ADD_HOOK(0x006A0150, HUnsheatheItemFromInventory_1, OUnsheatheItemFromInventory_1);
    ADD_HOOK(0x0069F0F0, HUnsheatheItemFromInventory_2, OUnsheatheItemFromInventory_2);
    ADD_HOOK(0x006A0E80, HUnsheatheItemFromInventory_3, OUnsheatheItemFromInventory_3);
}
