#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CTCHeroMorph
{
public:
    char pad0[0x0C];

    char pad1[0x08]; // CCountedPointer<CTCAppearanceMorphBase::CMeshMorphSet> PMeshMorphSet;
    char pad2[0x04]; // std::list<CIntelligentPointer<CThing>> ParticleEmitters;
    char pad3[0x04]; // std::list<CIntelligentPointer<CThing>> IdleParticleEmitters;
    char pad4[0x0C]; // std::vector<CDefPointer<CThingBaseDef const>> Tattoos;

    int FrameTattoosChanged;
    int FrameHeroBecameIdle;
    bool IdleParticlesAdded;
    bool Changed;

    char pad5[0x02];

    float Strength;
    float Berserk;
    float Will;
    float Skill;
    float Age;
    float Morality;
    float Fatness;
    float Tan;
    bool Teenager;

    char pad6[0x03];

    static void Hook();
};
