#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

#include "3DVector.h"
#include "DefString.h"
#include "PhysicsBase.h"
#include "InterfaceType.h"
#include "Base.h"

extern bool (*IsMultiplayer)();

class CThing
{
public:
    char pad0[0x18];
    uint64_t UniqueID;
    char pad1[0x40];
    CTCPhysicsBase* PhysicsTC;
    char pad2[0x28];
    uint16_t DefGlobalIndex;

    bool IsInLimbo();
    void SetInLimbo(bool on);

    bool IsToKillOnLevelUnload();
    void SetToKillOnLevelUnload(bool on);

    C3DVector* GetPos();
    CDefString* GetDefName(CDefString* result);

    CTCBase* GetTC(ETCInterfaceType id);

    static void Hook();

private:
    static C3DVector* (__thiscall* OGetPos)(CThing*);
    static C3DVector* __fastcall HGetPos(CThing*, void*);

    static int (__thiscall* OGetJoystickDeviceNumber)(CThing*);
    static int __fastcall HGetJoystickDeviceNumber(CThing* _this, void* _EDX);

    static CDefString* (__thiscall* OGetDefName)(CThing*, CDefString*);
    static CDefString* __fastcall HGetDefName(CThing* _this, void* _EDX, CDefString* result);

    static void (__thiscall* OSetToKillOnLevelUnload)(CThing*, bool);
    static void __fastcall HSetToKillOnLevelUnload(CThing* _this, void* _EDX, bool on);

    static void(__thiscall* OSetInLimbo)(CThing*, bool);
    static void __fastcall HSetInLimbo(CThing* _this, void* _EDX, bool on);
};
