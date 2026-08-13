#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../CharString.h"
#include "../CreatureActionBase.h"
#include "../Thing.h"
#include "../ThingCreatureBase.h"

class CCreatureAction_UnsheatheItemFromInventory
{
public:
    char pad[0xB8];

    CCreatureAction_UnsheatheItemFromInventory(CThingCreatureBase& creature, CThing& unsheathe_item, CCreatureActionBase* pfollow_up_action, long interruption_priority);
    CCreatureAction_UnsheatheItemFromInventory(CThingCreatureBase& creature, const CCharString& anim_name, CThing& unsheathe_item, long interruption_group_id, long interruption_priority, CCreatureActionBase* pfollow_up_action);
    CCreatureAction_UnsheatheItemFromInventory(const CCreatureAction_UnsheatheItemFromInventory& __that);

    static void Hook();

private:
    static void (__thiscall* OUnsheatheItemFromInventory_1)(CCreatureAction_UnsheatheItemFromInventory*, CThingCreatureBase&, CThing&, CCreatureActionBase*, long);
    static void __fastcall HUnsheatheItemFromInventory_1(CCreatureAction_UnsheatheItemFromInventory* _this, void* _EDX, CThingCreatureBase& creature, CThing& unsheathe_item, CCreatureActionBase* pfollow_up_action, long interruption_priority);

    static void (__thiscall* OUnsheatheItemFromInventory_2)(CCreatureAction_UnsheatheItemFromInventory*, CThingCreatureBase&, const CCharString&, CThing&, long, long, CCreatureActionBase*);
    static void __fastcall HUnsheatheItemFromInventory_2(CCreatureAction_UnsheatheItemFromInventory* _this, void* _EDX, CThingCreatureBase& creature, const CCharString& anim_name, CThing& unsheathe_item, long interruption_group_id, long interruption_priority, CCreatureActionBase* pfollow_up_action);

    static void (__thiscall* OUnsheatheItemFromInventory_3)(CCreatureAction_UnsheatheItemFromInventory*, const CCreatureAction_UnsheatheItemFromInventory&);
    static void __fastcall HUnsheatheItemFromInventory_3(CCreatureAction_UnsheatheItemFromInventory* _this, void* _EDX, const CCreatureAction_UnsheatheItemFromInventory& __that);
};
