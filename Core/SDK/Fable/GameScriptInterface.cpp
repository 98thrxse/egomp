#include "GameScriptInterface.h"

void(__thiscall* CGameScriptInterface::OStartSneaking)(CGameScriptInterface*) = nullptr;
void __fastcall CGameScriptInterface::HStartSneaking(CGameScriptInterface* _this, void* _EDX)
{
    OStartSneaking(_this);
}

void CGameScriptInterface::StartSneaking()
{
    OStartSneaking(this);
}

void CGameScriptInterface::Hook()
{
    ADD_HOOK(0x008A1300, HStartSneaking, OStartSneaking);
}
