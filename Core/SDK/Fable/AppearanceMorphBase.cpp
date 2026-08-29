#include "AppearanceMorphBase.h"

void(__thiscall* CTCAppearanceMorphBase::OUploadTextureMorphsToEngine)(CTCAppearanceMorphBase*, CIEngine&, std::set<long> const*, bool, float) = nullptr;
void __fastcall CTCAppearanceMorphBase::HUploadTextureMorphsToEngine(CTCAppearanceMorphBase* _this, void* _EDX, CIEngine& engine, std::set<long> const* limit_to_texture_ids, bool use_timeout, float timeout)
{
	OUploadTextureMorphsToEngine(_this, engine, limit_to_texture_ids, use_timeout, timeout);
}

void CTCAppearanceMorphBase::UploadTextureMorphsToEngine(CIEngine& engine, std::set<long> const* limit_to_texture_ids, bool use_timeout, float timeout)
{
	OUploadTextureMorphsToEngine(this, engine, limit_to_texture_ids, use_timeout, timeout);
}


void CTCAppearanceMorphBase::Hook()
{
	ADD_HOOK(0x006CA7F0, HUploadTextureMorphsToEngine, OUploadTextureMorphsToEngine);
}
