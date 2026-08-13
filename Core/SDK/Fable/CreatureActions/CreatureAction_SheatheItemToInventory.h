#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../CharString.h"
#include "../CreatureActionBase.h"
#include "../ThingCreatureBase.h"

class CCreatureAction_SheatheItemToInventory
{
public:
    char pad[0xB0];

    CCreatureAction_SheatheItemToInventory(CThingCreatureBase& creature, CCreatureActionBase* pfollow_up_action, long interruption_group_id);
    CCreatureAction_SheatheItemToInventory(CThingCreatureBase& creature, const CCharString& anim_name, CCreatureActionBase* pfollow_up_action, long interruption_group_id);
    CCreatureAction_SheatheItemToInventory(const CCreatureAction_SheatheItemToInventory& __that);

    static void Hook();

private:
    static void (__thiscall* OSheatheItemToInventory_1)(CCreatureAction_SheatheItemToInventory*, CThingCreatureBase&, CCreatureActionBase*, long);
    static void __fastcall HSheatheItemToInventory_1(CCreatureAction_SheatheItemToInventory* _this, void* _EDX, CThingCreatureBase& creature, CCreatureActionBase* pfollow_up_action, long interruption_group_id);

    static void (__thiscall* OSheatheItemToInventory_2)(CCreatureAction_SheatheItemToInventory*, CThingCreatureBase&, const CCharString&, CCreatureActionBase*, long);
    static void __fastcall HSheatheItemToInventory_2(CCreatureAction_SheatheItemToInventory* _this, void* _EDX, CThingCreatureBase& creature, const CCharString& anim_name, CCreatureActionBase* pfollow_up_action, long interruption_group_id);
    
    static void (__thiscall* OSheatheItemToInventory_3)(CCreatureAction_SheatheItemToInventory*, const CCreatureAction_SheatheItemToInventory&);
    static void __fastcall HSheatheItemToInventory_3(CCreatureAction_SheatheItemToInventory* _this, void* _EDX, const CCreatureAction_SheatheItemToInventory& __that);
};
