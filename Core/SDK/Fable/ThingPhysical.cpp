#include "ThingPhysical.h"

void(__thiscall* CThingPhysical::OSetMaxHealth)(CThingPhysical*, float, bool) = nullptr;
void __fastcall CThingPhysical::HSetMaxHealth(CThingPhysical* _this, void* _EDX, float max_health, bool update_health)
{
    OSetMaxHealth(_this, max_health, update_health);
}

void CThingPhysical::SetMaxHealth(float max_health, bool update_health)
{
    OSetMaxHealth(this, max_health, update_health);
}

void CThingPhysical::SetHealth(float health)
{
    *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0xB4) = health;
}

void CThingPhysical::Hook()
{
	ADD_HOOK(0x006A5260, HSetMaxHealth, OSetMaxHealth);
}
