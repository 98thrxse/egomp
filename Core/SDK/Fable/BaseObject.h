#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CBaseObject
{
public:
    char pad[0x8];

    static void Hook();
};
