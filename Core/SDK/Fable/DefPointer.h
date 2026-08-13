#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "DefPointeeBase.h"

class CDefPointer
{
public:
    CDefPointeeBase* Object;

    static void Hook();
};
