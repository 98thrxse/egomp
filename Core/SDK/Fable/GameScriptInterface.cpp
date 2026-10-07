#include "GameScriptInterface.h"

std::map<std::string, std::function<void(bool)>> CGameScriptInterface::setTeleportingAsActive;

void(__thiscall* CGameScriptInterface::OStartSneaking)(CGameScriptInterface*) = nullptr;
void __fastcall CGameScriptInterface::HStartSneaking(CGameScriptInterface* _this, void* _EDX)
{
    OStartSneaking(_this);
}

void CGameScriptInterface::StartSneaking()
{
    OStartSneaking(this);
}

void(__thiscall* CGameScriptInterface::OSetTeleportingAsActive)(CGameScriptInterface*, bool) = nullptr;
void __fastcall CGameScriptInterface::HSetTeleportingAsActive(CGameScriptInterface* _this, void* _EDX, bool active)
{
    if (IsMultiplayer())
    {
        for (const auto& pair : setTeleportingAsActive)
        {
            if (pair.second)
                pair.second(active);
        }

        return;
    }

    OSetTeleportingAsActive(_this, active);
}

void CGameScriptInterface::SetTeleportingAsActive(bool active)
{
    OSetTeleportingAsActive(this, active);
}

void CGameScriptInterface::Hook()
{
    ADD_HOOK(0x008A1300, HStartSneaking, OStartSneaking);
    ADD_HOOK(0x0088F410, HSetTeleportingAsActive, OSetTeleportingAsActive);
}
