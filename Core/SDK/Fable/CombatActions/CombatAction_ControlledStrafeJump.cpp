#include "CombatAction_ControlledStrafeJump.h"

CCombatAction_ControlledStrafeJump::CCombatAction_ControlledStrafeJump(CThingCreatureBase& creature, CThing& target, const C3DVector& vec1, const C3DVector& vec2)
{
    OControlledStrafeJump_1(this, creature, target, vec1, vec2);
}

void (__thiscall* CCombatAction_ControlledStrafeJump::OControlledStrafeJump_1)(CCombatAction_ControlledStrafeJump*, CThingCreatureBase&, CThing&, const C3DVector&, const C3DVector&) = nullptr;
void __fastcall CCombatAction_ControlledStrafeJump::HControlledStrafeJump_1(CCombatAction_ControlledStrafeJump* _this, void* _EDX, CThingCreatureBase& creature, CThing& target, const C3DVector& required_facing, const C3DVector& original_facing)
{
    OControlledStrafeJump_1(_this, creature, target, required_facing, original_facing);
}

CCombatAction_ControlledStrafeJump::CCombatAction_ControlledStrafeJump(const CCombatAction_ControlledStrafeJump& __that)
{
    OControlledStrafeJump_2(this, __that);
}

void (__thiscall* CCombatAction_ControlledStrafeJump::OControlledStrafeJump_2)(CCombatAction_ControlledStrafeJump*, const CCombatAction_ControlledStrafeJump&) = nullptr;
void __fastcall CCombatAction_ControlledStrafeJump::HControlledStrafeJump_2(CCombatAction_ControlledStrafeJump* _this, void* _EDX, const CCombatAction_ControlledStrafeJump& __that)
{
    OControlledStrafeJump_2(_this, __that);
}

void CCombatAction_ControlledStrafeJump::Hook()
{
    ADD_HOOK(0x0085C190, HControlledStrafeJump_1, OControlledStrafeJump_1);
    ADD_HOOK(0x0085C360, HControlledStrafeJump_2, OControlledStrafeJump_2);
}
