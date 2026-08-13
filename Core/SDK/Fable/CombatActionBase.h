#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CCombatActionBase
{
public:
    char pad[0x114];

    static void Hook();
};
