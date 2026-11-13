#pragma once

#include <iostream>

#include "../Utils/Hook.h"

class CRGBColour
{
public:
    union
    {
        struct
        {
            uint8_t B;
            uint8_t G;
            uint8_t R;
            uint8_t A;
        };

        unsigned int IntValue;
    };

    static void Hook();
};
