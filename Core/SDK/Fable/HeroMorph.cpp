#include "HeroMorph.h"

std::map<std::string, std::function<void()>> CTCHeroMorph::frameUpdateCallbacks;

void CTCHeroMorph::SetTattooIndexes(const std::vector<long>& indexes)
{
    Tattoos.clear();

    for (long index : indexes)
        AddTattoo(index);
}

std::vector<long> CTCHeroMorph::GetAllTattooIndexes()
{
    std::vector<long> indexes;

    for (auto& tattoo : Tattoos)
    {
        if (tattoo.Object)
            indexes.push_back(GetTattooIndex(tattoo.Object));
    }

    return indexes;
}

long CTCHeroMorph::GetTattooIndex(CDefPointeeBase* tattoo)
{
    const int tablePos = *reinterpret_cast<const int*>(
        reinterpret_cast<uintptr_t>(tattoo) + 0x25
        );

    CCharString charName("");
    CDefStringTable::Get()->GetString(&charName, tablePos);

    return CDefinitionManager::Get()->GetDefGlobalIndexFromName(&charName);
}

void(__thiscall* CTCHeroMorph::OAddTattoo)(CTCHeroMorph*, long) = nullptr;
void __fastcall CTCHeroMorph::HAddTattoo(
    CTCHeroMorph* _this,
    void* _EDX,
    long tattoo_def_index)
{
    OAddTattoo(_this, tattoo_def_index);
}

void CTCHeroMorph::AddTattoo(long tattoo_def_index)
{
    OAddTattoo(this, tattoo_def_index);
}

void(__thiscall* CTCHeroMorph::ODoMorphUpdate)(CTCHeroMorph*) = nullptr;
void __fastcall CTCHeroMorph::HDoMorphUpdate(CTCHeroMorph* _this, void* _EDX)
{
    ODoMorphUpdate(_this);
}

void CTCHeroMorph::DoMorphUpdate()
{
    ODoMorphUpdate(this);
}

void(__thiscall* CTCHeroMorph::OFrameUpdate)(CTCHeroMorph*) = nullptr;
void __fastcall CTCHeroMorph::HFrameUpdate(CTCHeroMorph* _this, void* _EDX)
{
    OFrameUpdate(_this);

    for (const auto& pair : frameUpdateCallbacks)
    {
        if (pair.second)
            pair.second();
    }
}

void CTCHeroMorph::Hook()
{
    ADD_HOOK(0x0071DA70, HAddTattoo, OAddTattoo);
    ADD_HOOK(0x0071CD30, HFrameUpdate, OFrameUpdate);
    ADD_HOOK(0x0071E130, HDoMorphUpdate, ODoMorphUpdate);
}
