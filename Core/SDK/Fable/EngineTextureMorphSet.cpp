#include "EngineTextureMorphSet.h"

std::map<std::string, std::function<void(CEngineTextureMorph*)>> CEngineTextureMorphSet::addEngineMorphCallbacks;

CEngineTextureMorph* (__thiscall* CEngineTextureMorphSet::OAddEngineMorph)(CEngineTextureMorphSet* _this, long original_texture) = nullptr;
CEngineTextureMorph* __fastcall CEngineTextureMorphSet::HAddEngineMorph(CEngineTextureMorphSet* _this, void* _EDX, long original_texture)
{
    CEngineTextureMorph* engineTextureMorph = OAddEngineMorph(_this, original_texture);

    for (const auto& pair : addEngineMorphCallbacks)
    {
        if (pair.second)
            pair.second(engineTextureMorph);
    }

    return engineTextureMorph;
}

void(__thiscall* CEngineTextureMorphSet::OAddTextureMorph)(CEngineTextureMorphSet* _this, long original_texture, CCompositeBlendDesc const& composite_blend_desc) = nullptr;
void __fastcall CEngineTextureMorphSet::HAddTextureMorph(CEngineTextureMorphSet* _this, void* _EDX, long original_texture, CCompositeBlendDesc const& composite_blend_desc)
{
    OAddTextureMorph(_this, original_texture, composite_blend_desc);
}

void CEngineTextureMorphSet::Hook()
{
	ADD_HOOK(0x006CA8C0, HAddEngineMorph, OAddEngineMorph);
	ADD_HOOK(0x006CA950, HAddTextureMorph, OAddTextureMorph);
}
