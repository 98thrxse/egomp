#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CThingGameObject
{
public:
    char pad[0xD0];

    static void Hook();
};
