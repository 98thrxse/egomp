#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CGameScriptInterface
{
public:
    char pad[0x4C];

    static void Hook();

    void StartSneaking();

private:
    static void(__thiscall* OStartSneaking)(CGameScriptInterface*);
    static void __fastcall HStartSneaking(CGameScriptInterface* _this, void* _EDX);
};
