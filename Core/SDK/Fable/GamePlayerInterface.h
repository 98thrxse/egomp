#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CGamePlayerInterface
{
public:
    char pad[0xBF0];

    static void Hook();
};
