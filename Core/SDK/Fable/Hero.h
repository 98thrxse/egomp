#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "Thing.h"

class CTCHero
{
public:
	void SetTeleportParticle(CThing& particle);

    static void Hook();

private:
    static void(__thiscall* OSetTeleportParticle)(CTCHero*, CThing&);
    static void __fastcall HSetTeleportParticle(CTCHero* _this, void* _EDX, CThing& particle);
};
