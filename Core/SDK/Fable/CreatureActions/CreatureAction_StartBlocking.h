#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../ThingCreatureBase.h"

class CCreatureAction_StartBlocking
{
public:
    char pad[0x114];

    CCreatureAction_StartBlocking(CThingCreatureBase& creature);
    static void Hook();

private:
    static void (__thiscall* OStartBlocking)(CCreatureAction_StartBlocking*, CThingCreatureBase&);
    static void __fastcall HStartBlocking(CCreatureAction_StartBlocking* _this, void* _EDX, CThingCreatureBase& creature);
};
