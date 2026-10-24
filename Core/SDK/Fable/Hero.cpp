#include "Hero.h"

std::map<std::string, std::function<void()>> CTCHero::frameUpdateCallbacks;

void(__thiscall* CTCHero::OSetTeleportParticle)(CTCHero*, CThing&) = nullptr;
void __fastcall CTCHero::HSetTeleportParticle(CTCHero* _this, void* _EDX, CThing& particle)
{
	OSetTeleportParticle(_this, particle);
}

void CTCHero::SetTeleportParticle(CThing& particle)
{
	OSetTeleportParticle(this, particle);
}

void(__thiscall* CTCHero::OSetWeaponsAsUsable)(CTCHero*, bool) = nullptr;
void __fastcall CTCHero::HSetWeaponsAsUsable(CTCHero* _this, void* _EDX, bool on)
{
	OSetWeaponsAsUsable(_this, on);
}

void CTCHero::SetWeaponsAsUsable(bool on)
{
	OSetWeaponsAsUsable(this, on);
}

void CTCHero::SetWillAsUsable(bool on)
{
	*reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + 0x0D) = on;
}

bool CTCHero::GetWeaponUseOverriddenByScripts() const
{
	return *reinterpret_cast<const bool*>(reinterpret_cast<const char*>(this) + 0x0E);
}

void CTCHero::SetWeaponUseOverriddenByScripts(bool value)
{
	*reinterpret_cast<bool*>(reinterpret_cast<char*>(this) + 0x0E) = value;
}

void(__thiscall* CTCHero::OFrameUpdate)(CTCHero*) = nullptr;
void __fastcall CTCHero::HFrameUpdate(CTCHero* _this, void* _EDX)
{
	OFrameUpdate(_this);

	for (const auto& pair : frameUpdateCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

void CTCHero::Hook()
{
	ADD_HOOK(0x004AB270, HSetTeleportParticle, OSetTeleportParticle);
	ADD_HOOK(0x006CA380, HSetWeaponsAsUsable, OSetWeaponsAsUsable);
	ADD_HOOK(0x006C9FD0, HFrameUpdate, OFrameUpdate);
}
