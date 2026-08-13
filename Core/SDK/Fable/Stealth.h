#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CTCStealth
{
public:
    static void Hook();

    void StartSneaking();

private:
    static void(__thiscall* OStartSneaking)(CTCStealth*);
    static void __fastcall HStartSneaking(CTCStealth* _this, void* _EDX);
};
