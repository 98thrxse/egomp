#pragma once

#include <iostream>

#include "../../../SDK/Fable/SDK.h"

class NetCreatureAction
{
public:
    static void* CCreatureAction_PlayerInteractionGreet(CThingCreatureBase& creatureBase, CThing* target);
    static void* CCreatureAction_StartBlocking(CThingCreatureBase& creatureBase);
    static void* CCombatAction_ControlledStrafeJump(CThingCreatureBase& creatureBase, CThing* target, const C3DVector& requiredFacing, const C3DVector& originalFacing);
    static void* CCreatureAction_KickThingOnGround(CThingCreatureBase& creatureBase, CThing* target);
    static void* CCreatureAction_InterruptableMidAttackAutoTurn(CThingCreatureBase& creatureBase, CThing* target, CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability);
    static void* CCreatureAction_UnsheatheItemFromInventory(CThingCreatureBase& creatureBase, CThing& unsheathe_item, CCreatureActionBase* pfollow_up_action, long interruption_priority);
    static void* CCreatureAction_SheatheItemToInventory(CThingCreatureBase& creatureBase, CCreatureActionBase* pfollow_up_action, long interruption_group_id);
};
