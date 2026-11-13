#pragma once

#include <iostream>
#include <vector>

#include "../Utils/Hook.h"

#include "CompositeBlendDesc.h"

class CEngineTextureMorph
{
public:
    int OriginalTextureIndex;
    int MorphID;
    std::vector<CCompositeBlendDesc> Blends;

    static void Hook();
};
