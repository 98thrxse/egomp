#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "CompositeBlendType.h"
#include "RGBColour.h"

class CCompositeBlendDesc
{
public:
    unsigned int TextureIndex;
    ECompositeBlendType BlendType;
    CRGBColour DiffuseColour;
    CRGBColour SpecularColour;

    static void Hook();
};