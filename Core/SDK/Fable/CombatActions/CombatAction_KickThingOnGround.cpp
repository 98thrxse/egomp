#include "CombatAction_KickThingOnGround.h"

CCombatAction_KickThingOnGround::CCombatAction_KickThingOnGround(CThingCreatureBase& creature, CThing& target)
{
    OKickThingOnGround_1(this, creature, target);
}

void (__thiscall* CCombatAction_KickThingOnGround::OKickThingOnGround_1)(CCombatAction_KickThingOnGround*, CThingCreatureBase&, CThing&) = nullptr;
void __fastcall CCombatAction_KickThingOnGround::HKickThingOnGround_1(CCombatAction_KickThingOnGround* _this, void* _EDX, CThingCreatureBase& creature, CThing& target)
{
    OKickThingOnGround_1(_this, creature, target);
}

CCombatAction_KickThingOnGround::CCombatAction_KickThingOnGround(const CCombatAction_KickThingOnGround& __that)
{
    OKickThingOnGround_2(this, __that);
}

void (__thiscall* CCombatAction_KickThingOnGround::OKickThingOnGround_2)(CCombatAction_KickThingOnGround*, const CCombatAction_KickThingOnGround&) = nullptr;
void __fastcall CCombatAction_KickThingOnGround::HKickThingOnGround_2(CCombatAction_KickThingOnGround* _this, void* _EDX, const CCombatAction_KickThingOnGround& __that)
{
    OKickThingOnGround_2(_this, __that);
}

void CCombatAction_KickThingOnGround::Hook()
{
    ADD_HOOK(0x0087FD20, HKickThingOnGround_1, OKickThingOnGround_1);
    ADD_HOOK(0x00880120, HKickThingOnGround_2, OKickThingOnGround_2);
}
