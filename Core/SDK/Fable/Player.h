#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "CharString.h"
#include "ThingPlayerCreature.h"

class CPlayer
{
public:
    char pad[0x218];

    void InitCharacterAs(CCharString const& def_name);
    void CreateCharacter(CCharString const& def_name);
    CThingPlayerCreature* GetPControlledCreature();
    void SetControlledCreature(CThingPlayerCreature* creature);
    void InitInterfaces();
    void Uninitialise();
    void UninitCharacter();

    static void Hook();

private:
    static void(__thiscall* OInitCharacterAs)(CPlayer*, CCharString const &);
    static void __fastcall HInitCharacterAs(CPlayer* _this, void* _EDX, CCharString const &def_name);

    static void(__thiscall* OCreateCharacter)(CPlayer*, CCharString const&);
    static void __fastcall HCreateCharacter(CPlayer* _this, void* _EDX, CCharString const& def_name);

    static CThingPlayerCreature* (__thiscall* OGetPControlledCreature)(CPlayer*);
    static CThingPlayerCreature* __fastcall HGetPControlledCreature(CPlayer*, void* _EDX);

    static void (__thiscall* OSetControlledCreature)(CPlayer*, CThingPlayerCreature*);
    static void __fastcall HSetControlledCreature(CPlayer*, void* _EDX, CThingPlayerCreature* creature);

    static void(__thiscall* OInitInterfaces)(CPlayer*);
    static void __fastcall HInitInterfaces(CPlayer*, void* _EDX);

    static void(__thiscall* OUninitialise)(CPlayer*);
    static void __fastcall HUninitialise(CPlayer* _this, void* _EDX);

    static void(__thiscall* OUninitCharacter)(CPlayer*);
    static void __fastcall HUninitCharacter(CPlayer* _this, void* _EDX);
};
