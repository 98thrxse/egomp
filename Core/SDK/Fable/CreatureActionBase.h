#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CCreatureActionBase
{
public:
    char pad[0xA8];

    static void Hook();
};
