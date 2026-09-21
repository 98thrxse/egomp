#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CThingObject
{
public:
    char pad[0xE0];

    static void Hook();
};
