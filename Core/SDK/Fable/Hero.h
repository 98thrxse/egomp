#pragma once

#include <iostream>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "Thing.h"

class CTCHero
{
public:
    char pad[0xC];
    bool WeaponsUsable;
    bool WillUsable;

    void SetTeleportParticle(CThing&);
    void SetWeaponsAsUsable(bool);
    bool GetWeaponUseOverriddenByScripts() const;
    void SetWeaponUseOverriddenByScripts(bool value);
    void SetWillAsUsable(bool);

    void AddFrameUpdateCallback(const std::string& id, std::function<void()> callback) { frameUpdateCallbacks[id] = callback; }
    void RemoveFrameUpdateCallback(const std::string& id) { frameUpdateCallbacks.erase(id); }

    static void Hook();

private:
    static std::map<std::string, std::function<void()>> frameUpdateCallbacks;

    static void(__thiscall* OSetTeleportParticle)(CTCHero*, CThing&);
    static void __fastcall HSetTeleportParticle(CTCHero* _this, void* _EDX, CThing& particle);

    static void(__thiscall* OSetWeaponsAsUsable)(CTCHero*, bool on);
    static void __fastcall HSetWeaponsAsUsable(CTCHero* _this, void* _EDX, bool on);

    static void(__thiscall* OFrameUpdate)(CTCHero*);
    static void __fastcall HFrameUpdate(CTCHero* _this, void* _EDX);
};
