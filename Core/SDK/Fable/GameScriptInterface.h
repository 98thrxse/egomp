#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CGameScriptInterface
{
public:
    static void Hook();

    void StartSneaking();

private:
    static void(__thiscall* OStartSneaking)(CGameScriptInterface*);
    static void __fastcall HStartSneaking(CGameScriptInterface* _this, void* _EDX);
};
