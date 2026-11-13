#include "EngineTextureMorphSet.h"

CEngineTextureMorph* (__thiscall* CEngineTextureMorphSet::OAddEngineMorph)(CEngineTextureMorphSet* _this, long original_texture) = nullptr;
CEngineTextureMorph* __fastcall CEngineTextureMorphSet::HAddEngineMorph(CEngineTextureMorphSet* _this, void* _EDX, long original_texture)
{
    return OAddEngineMorph(_this, original_texture);
}

void CEngineTextureMorphSet::Hook()
{
	ADD_HOOK(0x006CA8C0, HAddEngineMorph, OAddEngineMorph);
}
