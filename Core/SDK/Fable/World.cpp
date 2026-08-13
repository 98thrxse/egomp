#include "World.h"

std::map<std::string, std::function<void()>> CWorld::updateRegionLoadCallbacks;

CWorldMap* CWorld::GetWorldMap()
{
    return *(CWorldMap**)((char*)this + 0x14);
}

void (__thiscall* CWorld::OEAMoveHeroToRegion)(CWorld*, CGameEvent const*) = nullptr;
void __fastcall CWorld::HEAMoveHeroToRegion(CWorld* _this, void* _EDX, CGameEvent const* event)
{
    OEAMoveHeroToRegion(_this, event);
}

void CWorld::EAMoveHeroToRegion(CGameEvent const* event)
{
    OEAMoveHeroToRegion(this, event);
}

void(__thiscall* CWorld::OHandleMoveHeroToRegionGameEvent)(CWorld*, CGameEvent const&) = nullptr;
void __fastcall CWorld::HHandleMoveHeroToRegionGameEvent(CWorld* _this, void* _EDX, CGameEvent const& game_event)
{
    OHandleMoveHeroToRegionGameEvent(_this, game_event);
}

void CWorld::HandleMoveHeroToRegionGameEvent(CGameEvent const& game_event)
{
    OHandleMoveHeroToRegionGameEvent(this, game_event);
}

void(__thiscall* CWorld::OSetAsLoadingRegion)(CWorld*, C3DVector const&, float, bool, bool, bool) = nullptr;
void __fastcall CWorld::HSetAsLoadingRegion(CWorld* _this, void* _EDX, C3DVector const& region_start_pos, float facing_angle_xy, bool via_teleporter, bool allow_during_cut_scenes, bool via_door)
{
    OSetAsLoadingRegion(_this, region_start_pos, facing_angle_xy, via_teleporter, allow_during_cut_scenes, via_door);
}

void CWorld::SetAsLoadingRegion(C3DVector const& region_start_pos, float facing_angle_xy, bool via_teleporter, bool allow_during_cut_scenes, bool via_door)
{
    OSetAsLoadingRegion(this, region_start_pos, facing_angle_xy, via_teleporter, allow_during_cut_scenes, via_door);
}

void(__thiscall* CWorld::OUpdateRegionLoad)(CWorld*) = nullptr;
void __fastcall CWorld::HUpdateRegionLoad(CWorld* _this, void* _EDX)
{
    OUpdateRegionLoad(_this);

    for (const auto& pair : updateRegionLoadCallbacks)
    {
        if (pair.second)
            pair.second();
    }
}

void(__thiscall* CWorld::OSetAsPaused)(CWorld*, bool) = nullptr;
void __fastcall CWorld::HSetAsPaused(CWorld* _this, void* _EDX, bool paused)
{
    OSetAsPaused(_this, paused);
}

void(__thiscall* CWorld::OEAControlledCreatureStartSneaking)(CWorld*, const CGameEvent*) = nullptr;
void __fastcall CWorld::HEAControlledCreatureStartSneaking(CWorld* _this, void* _EDX, const CGameEvent* event)
{
    OEAControlledCreatureStartSneaking(_this, event);
}

void CWorld::Hook()
{
    ADD_HOOK(0x00629260, HEAMoveHeroToRegion, OEAMoveHeroToRegion);
    ADD_HOOK(0x0049EAF0, HHandleMoveHeroToRegionGameEvent, OHandleMoveHeroToRegionGameEvent);
    ADD_HOOK(0x0049E2C0, HSetAsLoadingRegion, OSetAsLoadingRegion);
    ADD_HOOK(0x004A3740, HUpdateRegionLoad, OUpdateRegionLoad);
    ADD_HOOK(0x0049D8F0, HSetAsPaused, OSetAsPaused);
    ADD_HOOK(0x0062AA70, HEAControlledCreatureStartSneaking, OEAControlledCreatureStartSneaking);
}
