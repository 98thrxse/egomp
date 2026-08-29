#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "DefinitionManager.h"
#include "DefPointeeBase.h"
#include "DefPointer.h"
#include "CharString.h"
#include "DefStringTable.h"

class CTCHeroMorph
{
public:
    char pad0[0x0C];

    char pad1[0x08]; // CCountedPointer<CTCAppearanceMorphBase::CMeshMorphSet> PMeshMorphSet;
    char pad2[0x04]; // std::list<CIntelligentPointer<CThing>> ParticleEmitters;
    char pad3[0x04]; // std::list<CIntelligentPointer<CThing>> IdleParticleEmitters;

    std::vector<CDefPointer> Tattoos;

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

    std::vector<long> GetAllTattooIndexes();
    void SetTattooIndexes(const std::vector<long>& indexes);

    long GetTattooIndex(CDefPointeeBase* tattoo);
    void AddTattoo(long);
    void DoMorphUpdate();

    void AddFrameUpdateCallback(const std::string& id, std::function<void()> callback) { frameUpdateCallbacks[id] = callback; }
    void RemoveFrameUpdateCallback(const std::string& id) { frameUpdateCallbacks.erase(id); }

    static void Hook();

private:
    static std::map<std::string, std::function<void()>> frameUpdateCallbacks;

    static void(__thiscall* OAddTattoo)(CTCHeroMorph*, long);
    static void __fastcall HAddTattoo(CTCHeroMorph* _this, void* _EDX, long tattoo_def_index);

    static void(__thiscall* OFrameUpdate)(CTCHeroMorph*);
    static void __fastcall HFrameUpdate(CTCHeroMorph* _this, void* _EDX);

    static void(__thiscall* ODoMorphUpdate)(CTCHeroMorph*);
    static void __fastcall HDoMorphUpdate(CTCHeroMorph* _this, void* _EDX);
};
