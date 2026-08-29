#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

#include "World.h"
#include "PlayerManager.h"
#include "DisplayEngine.h"

class CMainGameComponent
{
public:
    static CMainGameComponent* Get();

    CPlayerManager* GetPlayerManager();
    CWorld* GetWorld();
    CDisplayEngine* GetDisplayEngine();

    void AddPostInitCallback(const std::string& id, std::function<void()> callback) { postInitCallbacks[id] = callback; }
    void RemovePostInitCallback(const std::string& id) { postInitCallbacks.erase(id); }

    void AddUpdateCallback(const std::string& id, std::function<void()> callback) { updateCallbacks[id] = callback; }
    void RemoveUpdateCallback(const std::string& id) { updateCallbacks.erase(id); }

    void AddShutdownCallback(const std::string& id, std::function<void()> callback) { shutdownCallbacks[id] = callback; }
    void RemoveShutdownCallback(const std::string& id) { shutdownCallbacks.erase(id); }

    static void Hook();

private:
    static std::map<std::string, std::function<void()>> postInitCallbacks;
    static std::map<std::string, std::function<void()>> updateCallbacks;
    static std::map<std::string, std::function<void()>> shutdownCallbacks;

    static void(__thiscall* OInit)(CMainGameComponent*);
    static void __fastcall HInit(CMainGameComponent* _this, void* _EDX);

    static void(__thiscall* OPostInit)(CMainGameComponent*);
    static void __fastcall HPostInit(CMainGameComponent* _this, void* _EDX);

    static void(__thiscall* OUpdate)(CMainGameComponent*);
    static void __fastcall HUpdate(CMainGameComponent* _this, void* _EDX);

    static void(__thiscall* OShutdown)(CMainGameComponent*);
    static void __fastcall HShutdown(CMainGameComponent* _this, void* _EDX);
};
