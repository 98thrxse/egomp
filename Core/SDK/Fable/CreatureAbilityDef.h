#pragma once

#include "CreatureAbility.h"

struct CCreatureAbilityDef
{
    char pad[0x3C];
    ECreatureAbility Type;
};
