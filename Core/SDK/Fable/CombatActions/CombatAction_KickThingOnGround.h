#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../Thing.h"
#include "../ThingCreatureBase.h"

class CCombatAction_KickThingOnGround
{
public:
    char pad[0x130];

    CCombatAction_KickThingOnGround(CThingCreatureBase& creature, CThing& target);
    CCombatAction_KickThingOnGround(const CCombatAction_KickThingOnGround& __that);

    static void Hook();

private:
    static void (__thiscall* OKickThingOnGround_1)(CCombatAction_KickThingOnGround*, CThingCreatureBase&, CThing&);
    static void __fastcall HKickThingOnGround_1(CCombatAction_KickThingOnGround* _this, void* _EDX, CThingCreatureBase& creature, CThing& target);

    static void (__thiscall* OKickThingOnGround_2)(CCombatAction_KickThingOnGround*, const CCombatAction_KickThingOnGround&);
    static void __fastcall HKickThingOnGround_2(CCombatAction_KickThingOnGround* _this, void* _EDX, const CCombatAction_KickThingOnGround& __that);
};
