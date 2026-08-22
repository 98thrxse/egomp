#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

#include "3DVector.h"
#include "RightHandedSet.h"

class CTCPhysicsStandard
{
public:
    char pad[0x44];

    C3DVector OffsetVector3D;
    CRightHandedSet RHSet;
    CRightHandedSet OldRHSet;
    int RHSetLastFrameSet;

    CRightHandedSet* GetRHSet();
    void SetRHSet(CRightHandedSet const&);

    float GetFacingAngleXY();
    void SetFacingAngleXY(float);

    static void Hook();
private:
    static CRightHandedSet* (__thiscall* OGetRHSet)(CTCPhysicsStandard*);
    static CRightHandedSet* __fastcall HGetRHSet(CTCPhysicsStandard* _this, void* _EDX);

    static void(__thiscall* OSetRHSet)(CTCPhysicsStandard*, CRightHandedSet const&);
    static void __fastcall HSetRHSet(CTCPhysicsStandard* _this, void* _EDX, CRightHandedSet const& rhset);

    static float (__thiscall* OGetFacingAngleXY)(CTCPhysicsStandard*);
    static float __fastcall HGetFacingAngleXY(CTCPhysicsStandard* _this, void* _EDX);

    static void(__thiscall* OSetFacingAngleXY)(CTCPhysicsStandard*, float);
    static void __fastcall HSetFacingAngleXY(CTCPhysicsStandard* _this, void* _EDX, float xy);
};
