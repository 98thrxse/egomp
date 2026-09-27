#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CThingHolySite
{
public:
    char pad[0xD8];

    static void Hook();
};
