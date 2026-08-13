#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../3DVector.h"
#include "../Thing.h"
#include "../ThingCreatureBase.h"

class CCombatAction_ControlledStrafeJump
{
public:
    char pad[0x130];

    CCombatAction_ControlledStrafeJump(CThingCreatureBase& creature, CThing& target, const C3DVector& required_facing, const C3DVector& original_facing);
    CCombatAction_ControlledStrafeJump(const CCombatAction_ControlledStrafeJump& __that);

    static void Hook();

private:
    static void (__thiscall* OControlledStrafeJump_1)(CCombatAction_ControlledStrafeJump*, CThingCreatureBase&, CThing&, const C3DVector&, const C3DVector&);
    static void __fastcall HControlledStrafeJump_1(CCombatAction_ControlledStrafeJump* _this, void* _EDX, CThingCreatureBase& creature, CThing& target, const C3DVector& required_facing, const C3DVector& original_facing);

    static void (__thiscall* OControlledStrafeJump_2)(CCombatAction_ControlledStrafeJump*, const CCombatAction_ControlledStrafeJump&);
    static void __fastcall HControlledStrafeJump_2(CCombatAction_ControlledStrafeJump* _this, void* _EDX, const CCombatAction_ControlledStrafeJump& __that);
};
