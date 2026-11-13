#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "EngineTextureMorph.h"

class CEngineInternalPrimitiveMorphInfo
{
public:
    static void(__thiscall* OInitialiseCompositeSurfaces)(CEngineInternalPrimitiveMorphInfo*, std::vector<CEngineTextureMorph> const&);
    static void __fastcall HInitialiseCompositeSurfaces(CEngineInternalPrimitiveMorphInfo* _this, void* _EDX, std::vector<CEngineTextureMorph> const& morph_set);

    static void Hook();
};
