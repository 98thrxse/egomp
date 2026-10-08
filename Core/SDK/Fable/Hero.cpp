#include "Hero.h"

void(__thiscall* CTCHero::OSetTeleportParticle)(CTCHero*, CThing&) = nullptr;
void __fastcall CTCHero::HSetTeleportParticle(CTCHero* _this, void* _EDX, CThing& particle)
{
	OSetTeleportParticle(_this, particle);
}

void CTCHero::SetTeleportParticle(CThing& particle)
{
	OSetTeleportParticle(this, particle);
}

void CTCHero::Hook()
{
	ADD_HOOK(0x004AB270, HSetTeleportParticle, OSetTeleportParticle);
}
