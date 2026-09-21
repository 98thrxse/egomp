#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CGame
{
public:
    char pad0[0x8];

    char pad1[0x4]; // CGameComponent* CurrentGameComponent;

    uint8_t ParameterBuffer[512];
    bool Quit;

    char pad2[0x3];

    static CGame* GetInstance();

    static void Hook();

private:
    static void(__thiscall* OInitialise)(CGame*);
    static void __fastcall HInitialise(CGame* _this, void* _EDX);
};

