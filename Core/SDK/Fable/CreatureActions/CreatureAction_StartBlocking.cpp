#include "CreatureAction_StartBlocking.h"

CCreatureAction_StartBlocking::CCreatureAction_StartBlocking(CThingCreatureBase& creature)
{
    OStartBlocking(this, creature);
}

void (__thiscall* CCreatureAction_StartBlocking::OStartBlocking)(CCreatureAction_StartBlocking*, CThingCreatureBase&) = nullptr;
void __fastcall CCreatureAction_StartBlocking::HStartBlocking(CCreatureAction_StartBlocking* _this, void* _EDX, CThingCreatureBase& creature)
{
    OStartBlocking(_this, creature);
}

void CCreatureAction_StartBlocking::Hook()
{
    ADD_HOOK(0x00855BE0, HStartBlocking, OStartBlocking);
}
