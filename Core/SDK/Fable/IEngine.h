#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CIEngine
{
public:
    char pad[0x08];
    bool Active;

    static void Hook();
};
