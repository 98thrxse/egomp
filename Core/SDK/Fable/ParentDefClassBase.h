#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "DefString.h"

class CParentDefClassBase
{
public:
    char pad[0x25];

    CDefString InstantiationName;

    static void Hook();
};
