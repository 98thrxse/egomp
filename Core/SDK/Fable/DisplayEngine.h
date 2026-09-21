#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "IEngine.h"

class CDisplayEngine
{
public:
    char pad0[0x2C];

    CIEngine* Engine3D;

    char pad1[0xD0];

    CIEngine* Get3DEngine();

    static void Hook();
};
