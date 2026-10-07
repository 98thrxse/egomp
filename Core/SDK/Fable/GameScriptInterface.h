#pragma once

#include <iostream>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

extern bool (*IsMultiplayer)();

class CGameScriptInterface
{
public:
    char pad[0x4C];

    static void Hook();

    void StartSneaking();
    void SetTeleportingAsActive(bool active);

    void AddSetTeleportingAsActiveCallback(const std::string& id, std::function<void(bool)> callback) { setTeleportingAsActive[id] = callback; }
    void RemoveSetTeleportingAsActiveCallback(const std::string& id) { setTeleportingAsActive.erase(id); }

private:
    static std::map<std::string, std::function<void(bool)>> setTeleportingAsActive;

    static void(__thiscall* OStartSneaking)(CGameScriptInterface*);
    static void __fastcall HStartSneaking(CGameScriptInterface* _this, void* _EDX);

    static void(__thiscall* OSetTeleportingAsActive)(CGameScriptInterface*, bool);
    static void __fastcall HSetTeleportingAsActive(CGameScriptInterface* _this, void* _EDX, bool active);
};
