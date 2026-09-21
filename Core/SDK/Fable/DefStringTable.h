#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "CharString.h"

class CDefStringTable
{
public:
    char pad[0x38];

    static CDefStringTable* Get();

    CCharString* GetString(CCharString* result, int table_pos);

    static void Hook();

private:
    static CCharString* (__thiscall* OGetString)(CDefStringTable*, CCharString*, int);
    static CCharString* __fastcall HGetString(CDefStringTable* _this, void* _EDX, CCharString* result, int table_pos);
};