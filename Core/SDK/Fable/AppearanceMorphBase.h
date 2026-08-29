#pragma once

#include <iostream>
#include <set>

#include "../Utils/Hook.h"

#include "IEngine.h"

class CTCAppearanceMorphBase
{
public:
    void UploadTextureMorphsToEngine(CIEngine&, std::set<long> const*, bool, float);

    static void Hook();

private:
    static void(__thiscall* OUploadTextureMorphsToEngine)(CTCAppearanceMorphBase*, CIEngine&, std::set<long> const*, bool, float);
    static void __fastcall HUploadTextureMorphsToEngine(CTCAppearanceMorphBase* _this, void* _EDX, CIEngine& engine, std::set<long> const* limit_to_texture_ids, bool use_timeout, float timeout);
};
