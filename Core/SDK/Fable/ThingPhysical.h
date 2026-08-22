#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CThingPhysical
{
public:
    char pad0[0x98];

    char pad1[0x4]; // std::list<CHealthOverTimeHelper> HealthOverTimeEffects;

    float Scale;

    char pad2[0x8]; // CIntelligentPointer<CThingPhysical> PLastCreator;
    char pad3[0x8]; // CIntelligentPointer<CThingPhysical> POriginalCreator;

    float MaxHealth;
    float Health;
    int CanComeBetweenCameraAndObservedThing;

    uint8_t Damageable : 1;
    uint8_t Killable : 1;
    uint8_t RespondToHits : 1;
    uint8_t EvadeAllHits : 1;
    uint8_t NegateAllHits : 1;
    uint8_t AbleToBeEngagedInCombat : 1;
    uint8_t : 2;

    char pad4[0x3];

    void SetMaxHealth(float max_health, bool update_health);
    void SetHealth(float health);

    static void Hook();

private:
    static void(__thiscall* OSetMaxHealth)(CThingPhysical*, float, bool);
    static void __fastcall HSetMaxHealth(CThingPhysical* _this, void* _EDX, float max_health, bool update_health);


};
