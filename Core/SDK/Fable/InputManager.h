#pragma once

#include <iostream>

#include "../Utils/Hook.h"
#include "../Utils/Window.h"

#include "SystemManager.h"

extern bool (*IsMultiplayer)();

class CInputManager
{
public:
    static void Hook();

private:
    static void(__thiscall* OSetHasInputFocus)(CInputManager*, bool);
    static void __fastcall HSetHasInputFocus(CInputManager* _this, void* _EDX, bool on);
};
