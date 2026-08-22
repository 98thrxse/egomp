#include "PhysicsStandard.h"

CRightHandedSet* (__thiscall* CTCPhysicsStandard::OGetRHSet)(CTCPhysicsStandard*) = nullptr;
CRightHandedSet* __fastcall CTCPhysicsStandard::HGetRHSet(CTCPhysicsStandard* _this, void* _EDX)
{
    return OGetRHSet(_this);
}

CRightHandedSet* CTCPhysicsStandard::GetRHSet()
{
    return OGetRHSet(this);
}

void(__thiscall* CTCPhysicsStandard::OSetRHSet)(CTCPhysicsStandard*, CRightHandedSet const&) = nullptr;
void __fastcall CTCPhysicsStandard::HSetRHSet(CTCPhysicsStandard* _this, void* _EDX, CRightHandedSet const& rhset)
{
    OSetRHSet(_this, rhset);
}

void CTCPhysicsStandard::SetRHSet(CRightHandedSet const& rhset)
{
    OSetRHSet(this, rhset);
}

float(__thiscall* CTCPhysicsStandard::OGetFacingAngleXY)(CTCPhysicsStandard*) = nullptr;
float __fastcall CTCPhysicsStandard::HGetFacingAngleXY(CTCPhysicsStandard* _this, void* _EDX)
{
    return OGetFacingAngleXY(_this);
}

float CTCPhysicsStandard::GetFacingAngleXY()
{
    return OGetFacingAngleXY(this);
}

void(__thiscall* CTCPhysicsStandard::OSetFacingAngleXY)(CTCPhysicsStandard*, float) = nullptr;
void __fastcall CTCPhysicsStandard::HSetFacingAngleXY(CTCPhysicsStandard* _this, void* _EDX, float xy)
{
    OSetFacingAngleXY(_this, xy);
}

void CTCPhysicsStandard::SetFacingAngleXY(float xy)
{
    OSetFacingAngleXY(this, xy);
}

void CTCPhysicsStandard::Hook()
{
    ADD_HOOK(0x00724BD0, HGetRHSet, OGetRHSet);
	ADD_HOOK(0x007238E0, HSetRHSet, OSetRHSet);
    ADD_HOOK(0x00723B30, HGetFacingAngleXY, OGetFacingAngleXY);
    ADD_HOOK(0x00723760, HSetFacingAngleXY, OSetFacingAngleXY);
}
