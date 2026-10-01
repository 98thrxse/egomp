#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

#include "WorldMap.h"
#include "3DVector.h"
#include "GameEvent.h"

extern bool (*IsMultiplayer)();

class CWorld
{
public:
    enum ERegionLoadStatus
    {
        NOT_LOADING_REGION = 0x0,
        WAITING_FOR_LOCKED_REGION_CONFIRMATION = 0x1,
        WAITING_FOR_CONFIRMATION = 0x2,
        WAITING_FOR_TELEPORT_EFFECT = 0x3,
        READY_TO_BEGIN_FADE_OUT = 0x4,
        WAITING_FOR_FADE_OUT = 0x5,
        LOADING_NEW_REGION = 0x6,
        LOADING_RESOURCES = 0x7,
        READY_FOR_FADE_IN = 0x8,
        WAITING_FOR_FADE_IN = 0x9
    };

    char pad[0x198];

    C3DVector GetSaveGameMarkerPos();
    float GetSaveGameMarkerAngleXY();
    CWorld::ERegionLoadStatus GetRegionLoadStatus();

    CWorldMap* GetWorldMap();

    void AddUpdateRegionLoadCallback(const std::string& id, std::function<void()> callback) { updateRegionLoadCallbacks[id] = callback; }
    void RemoveUpdateRegionLoadCallback(const std::string& id) { updateRegionLoadCallbacks.erase(id); }

    void AddSetAsLoadingRegionCallback(const std::string& id, std::function<void(C3DVector const&, float, bool, bool, bool)> callback) { setAsLoadingRegionCallbacks[id] = callback; }
    void RemoveSetAsLoadingRegionCallback(const std::string& id) { setAsLoadingRegionCallbacks.erase(id); }

    void EAMoveHeroToRegion(CGameEvent const* event);
    void HandleMoveHeroToRegionGameEvent(CGameEvent const& game_event);
    void SetAsLoadingRegion(C3DVector const& region_start_pos, float facing_angle_xy, bool via_teleporter, bool allow_during_cut_scenes, bool via_door);

    static void Hook();

private:
    static std::map<std::string, std::function<void()>> updateRegionLoadCallbacks;
    static std::map<std::string, std::function<void(C3DVector const&, float, bool, bool, bool)>> setAsLoadingRegionCallbacks;

    static void(__thiscall* OEAMoveHeroToRegion)(CWorld*, CGameEvent const*);
    static void __fastcall HEAMoveHeroToRegion(CWorld* _this, void* _EDX, CGameEvent const* event);

    static void(__thiscall* OHandleMoveHeroToRegionGameEvent)(CWorld*, CGameEvent const&);
    static void __fastcall HHandleMoveHeroToRegionGameEvent(CWorld* _this, void* _EDX, CGameEvent const& game_event);

    static void(__thiscall* OSetAsLoadingRegion)(CWorld*, C3DVector const&, float, bool, bool, bool);
    static void __fastcall HSetAsLoadingRegion(CWorld* _this, void* _EDX, C3DVector const& region_start_pos, float facing_angle_xy, bool via_teleporter, bool allow_during_cut_scenes, bool via_door);

    static void(__thiscall* OUpdateRegionLoad)(CWorld*);
    static void __fastcall HUpdateRegionLoad(CWorld* _this, void* _EDX);

    static void(__thiscall* OSetAsPaused)(CWorld*, bool);
    static void __fastcall HSetAsPaused(CWorld* _this, void* _EDX, bool paused);

    static void(__thiscall* OEAControlledCreatureStartSneaking)(CWorld*, const CGameEvent*);
    static void __fastcall HEAControlledCreatureStartSneaking(CWorld* _this, void* _EDX, const CGameEvent* event);
};
