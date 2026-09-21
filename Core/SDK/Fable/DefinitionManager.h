#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "CharString.h"

class CDefinitionManager
{
public:
	char pad0[0xD0];

    static CDefinitionManager* Get();
    int GetDefGlobalIndexFromName(const CCharString* instantiation_name);
    static void Hook();

private:
    static int(__thiscall* OGetDefGlobalIndexFromName)(CDefinitionManager*, const CCharString*);
    static int __fastcall HGetDefGlobalIndexFromName(CDefinitionManager* _this, void* _EDX, const CCharString* instantiation_name);
};