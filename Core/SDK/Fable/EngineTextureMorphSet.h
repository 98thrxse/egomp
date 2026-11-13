#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "EngineTextureMorph.h"

class CEngineTextureMorphSet
{
public:
    static CEngineTextureMorph* (__thiscall* OAddEngineMorph)(CEngineTextureMorphSet*, long);
    static CEngineTextureMorph* __fastcall HAddEngineMorph(CEngineTextureMorphSet* _this, void* _EDX, long original_texture);
    
    static void Hook();
};
