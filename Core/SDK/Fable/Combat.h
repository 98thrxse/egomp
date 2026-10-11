#pragma once

#include <iostream>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

class CTCCombat
{
public:
    void SetBlocking();
    void UnsetBlocking();

    void AddUnsetBlockingCallback(const std::string& id, std::function<void()> callback) { unsetBlockingCallbacks[id] = callback; }
    void RemoveUnsetBlockingCallback(const std::string& id) { unsetBlockingCallbacks.erase(id); }

    static void Hook();

private:
    static std::map<std::string, std::function<void()>> unsetBlockingCallbacks;

    static void(__thiscall* OSetBlocking)(CTCCombat*);
    static void __fastcall HSetBlocking(CTCCombat* _this, void* _EDX);

    static void(__thiscall* OUnsetBlocking)(CTCCombat*);
    static void __fastcall HUnsetBlocking(CTCCombat* _this, void* _EDX);
};
