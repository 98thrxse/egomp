#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../Thing.h"
#include "../ThingCreatureBase.h"

class CCreatureAction_PlayerInteractionGreet
{
public:
    char pad[0xB0];

    CCreatureAction_PlayerInteractionGreet(CThingCreatureBase& creature, CThing* target);
    CCreatureAction_PlayerInteractionGreet(const CCreatureAction_PlayerInteractionGreet& __that);

    static void Hook();

private:
    static void (__thiscall* OPlayerInteractionGreet_1)(CCreatureAction_PlayerInteractionGreet*, CThingCreatureBase&, CThing*);
    static void __fastcall HPlayerInteractionGreet_1(CCreatureAction_PlayerInteractionGreet* _this, void* _EDX, CThingCreatureBase& creature, CThing* target);

    static void (__thiscall* OPlayerInteractionGreet_2)(CCreatureAction_PlayerInteractionGreet*, const CCreatureAction_PlayerInteractionGreet&);
    static void __fastcall HPlayerInteractionGreet_2(CCreatureAction_PlayerInteractionGreet* _this, void* _EDX, const CCreatureAction_PlayerInteractionGreet& __that);
};
