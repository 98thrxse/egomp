#include "CreatureAction_PlayerInteractionGreet.h"

CCreatureAction_PlayerInteractionGreet::CCreatureAction_PlayerInteractionGreet(CThingCreatureBase& creature, CThing* target)
{
    OPlayerInteractionGreet_1(this, creature, target);
}

void (__thiscall* CCreatureAction_PlayerInteractionGreet::OPlayerInteractionGreet_1)(CCreatureAction_PlayerInteractionGreet*, CThingCreatureBase&, CThing*) = nullptr;
void __fastcall CCreatureAction_PlayerInteractionGreet::HPlayerInteractionGreet_1(CCreatureAction_PlayerInteractionGreet* _this, void* _EDX, CThingCreatureBase& creature, CThing* target)
{
    OPlayerInteractionGreet_1(_this, creature, target);
}

CCreatureAction_PlayerInteractionGreet::CCreatureAction_PlayerInteractionGreet(const CCreatureAction_PlayerInteractionGreet& __that)
{
    OPlayerInteractionGreet_2(this, __that);
}

void (__thiscall* CCreatureAction_PlayerInteractionGreet::OPlayerInteractionGreet_2)(CCreatureAction_PlayerInteractionGreet*, const CCreatureAction_PlayerInteractionGreet&) = nullptr;
void __fastcall CCreatureAction_PlayerInteractionGreet::HPlayerInteractionGreet_2(CCreatureAction_PlayerInteractionGreet* _this, void* _EDX, const CCreatureAction_PlayerInteractionGreet& __that)
{
    OPlayerInteractionGreet_2(_this, __that);
}

void CCreatureAction_PlayerInteractionGreet::Hook()
{
    ADD_HOOK(0x0062DAD0, HPlayerInteractionGreet_1, OPlayerInteractionGreet_1);
    ADD_HOOK(0x0062EF60, HPlayerInteractionGreet_2, OPlayerInteractionGreet_2);
}
