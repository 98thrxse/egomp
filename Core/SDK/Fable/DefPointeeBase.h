#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CDefPointeeBase
{
public:
    char pad[0x1C];

    static void Hook();
};
