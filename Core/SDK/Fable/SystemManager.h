#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CSystemManager
{
public:
    static CSystemManager* GFGetSystemManager();

    static void Hook();

private:
    static CSystemManager* (__fastcall* OGFGetSystemManager)();
    static CSystemManager* __fastcall HGFGetSystemManager();

    static bool(__thiscall* OIsApplicationActive)(CSystemManager*);
    static bool __fastcall HIsApplicationActive(CSystemManager* _this, void* _EDX);

    static void(__thiscall* OUpdateActive)(CSystemManager*);
    static void __fastcall HUpdateActive(CSystemManager* _this, void* _EDX);
};
