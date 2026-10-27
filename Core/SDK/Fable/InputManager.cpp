#include "InputManager.h"

void(__thiscall* CInputManager::OSetHasInputFocus)(CInputManager*, bool) = nullptr;
void __fastcall CInputManager::HSetHasInputFocus(CInputManager* _this, void*, bool on)
{
    if (IsNetworkActive())
    {
        CSystemManager* systemManager = CSystemManager::GFGetSystemManager();
        HWND gameWindow = *reinterpret_cast<HWND*>(reinterpret_cast<std::uintptr_t>(systemManager) + 0x94);

        OSetHasInputFocus(_this, on && GetOriginalForegroundWindow() == gameWindow);
        return;
    }

    OSetHasInputFocus(_this, on);
}

void CInputManager::Hook()
{
    ADD_HOOK(0x009F4E20, HSetHasInputFocus, OSetHasInputFocus);
}
