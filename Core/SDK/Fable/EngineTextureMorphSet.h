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

    static void(__thiscall* OAddTextureMorph)(CEngineTextureMorphSet*, long, CCompositeBlendDesc const&);
    static void __fastcall HAddTextureMorph(CEngineTextureMorphSet* _this, void* _EDX, long original_texture, CCompositeBlendDesc const& composite_blend_desc);

    void AddEngineMorphCallback(const std::string& id, std::function<void(CEngineTextureMorph*)> callback) { addEngineMorphCallbacks[id] = callback; }
    void RemoveEngineMorphCallback(const std::string& id) { addEngineMorphCallbacks.erase(id); }

    static void Hook();

private:
    static std::map<std::string, std::function<void(CEngineTextureMorph*)>> addEngineMorphCallbacks;
};
