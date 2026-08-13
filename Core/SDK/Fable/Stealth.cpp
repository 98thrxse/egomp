#include "Stealth.h"

void(__thiscall* CTCStealth::OStartSneaking)(CTCStealth*) = nullptr;
void __fastcall CTCStealth::HStartSneaking(CTCStealth* _this, void* _EDX)
{
	OStartSneaking(_this);
}

void CTCStealth::StartSneaking()
{
	OStartSneaking(this);
}

void CTCStealth::Hook()
{
	ADD_HOOK(0x00747560, HStartSneaking, OStartSneaking);
}
