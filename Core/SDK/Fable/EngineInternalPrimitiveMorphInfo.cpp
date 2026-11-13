#include "EngineInternalPrimitiveMorphInfo.h"

void(__thiscall* CEngineInternalPrimitiveMorphInfo::OInitialiseCompositeSurfaces)(CEngineInternalPrimitiveMorphInfo*, std::vector<CEngineTextureMorph> const&) = nullptr;
void __fastcall CEngineInternalPrimitiveMorphInfo::HInitialiseCompositeSurfaces(CEngineInternalPrimitiveMorphInfo* _this, void* _EDX, std::vector<CEngineTextureMorph> const& morph_set)
{
    OInitialiseCompositeSurfaces(_this, morph_set);
}

void CEngineInternalPrimitiveMorphInfo::Hook()
{
    ADD_HOOK(0x00BECBA0, HInitialiseCompositeSurfaces, OInitialiseCompositeSurfaces);
}
