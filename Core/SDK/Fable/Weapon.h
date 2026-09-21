#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CTCWeapon
{
public:
    bool IsMeleeWeapon();
    bool IsProjectileWeapon();

    static void Hook();

private:
    static bool(__thiscall* OIsMeleeWeapon)(CTCWeapon*);
    static bool __fastcall HIsMeleeWeapon(CTCWeapon* _this, void* _EDX);

    static bool(__thiscall* OIsProjectileWeapon)(CTCWeapon*);
    static bool __fastcall HIsProjectileWeapon(CTCWeapon* _this, void* _EDX);
};
