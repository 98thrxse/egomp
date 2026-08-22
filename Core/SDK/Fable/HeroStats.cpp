#include "HeroStats.h"

std::map<std::string, std::function<void()>> CTCHeroStats::frameUpdateCallbacks;

void(__thiscall* CTCHeroStats::OSetMoney)(CTCHeroStats*, long, bool) = nullptr;
void __fastcall CTCHeroStats::HSetMoney(CTCHeroStats* _this, void* _EDX, long money, bool track_for_money_earned_and_spent)
{
	OSetMoney(_this, money, track_for_money_earned_and_spent);
}

void CTCHeroStats::SetMoney(long money, bool track_for_money_earned_and_spent)
{
	OSetMoney(this, money, track_for_money_earned_and_spent);
}

void(__thiscall* CTCHeroStats::OSetAge)(CTCHeroStats*, float) = nullptr;
void __fastcall CTCHeroStats::HSetAge(CTCHeroStats* _this, void* _EDX, float age)
{
	OSetAge(_this, age);
}

void CTCHeroStats::SetAge(float age)
{
	OSetAge(this, age);
}

void(__thiscall* CTCHeroStats::OSetMorality)(CTCHeroStats*, long) = nullptr;
void __fastcall CTCHeroStats::HSetMorality(CTCHeroStats* _this, void* _EDX, long morality)
{
	OSetMorality(_this, morality);
}

void CTCHeroStats::SetMorality(long morality)
{
	OSetMorality(this, morality);
}

void(__thiscall* CTCHeroStats::OSetFatness)(CTCHeroStats*, float) = nullptr;
void __fastcall CTCHeroStats::HSetFatness(CTCHeroStats* _this, void* _EDX, float fatness)
{
	OSetFatness(_this, fatness);
}

void CTCHeroStats::SetFatness(float fatness)
{
	OSetFatness(this, fatness);
}

void(__thiscall* CTCHeroStats::OSetSunTan)(CTCHeroStats*, float) = nullptr;
void __fastcall CTCHeroStats::HSetSunTan(CTCHeroStats* _this, void* _EDX, float sunTan)
{
	OSetSunTan(_this, sunTan);
}

void CTCHeroStats::SetSunTan(float sunTan)
{
	OSetSunTan(this, sunTan);
}

void(__thiscall* CTCHeroStats::OForceRenownLevelTo)(CTCHeroStats*, long) = nullptr;
void __fastcall CTCHeroStats::HForceRenownLevelTo(CTCHeroStats* _this, void* _EDX, long renown_level)
{
	OForceRenownLevelTo(_this, renown_level);
}

void CTCHeroStats::ForceRenownLevelTo(long renown_level)
{
	OForceRenownLevelTo(this, renown_level);
}

void(__thiscall* CTCHeroStats::OForceStaminaTo)(CTCHeroStats*, float) = nullptr;
void __fastcall CTCHeroStats::HForceStaminaTo(CTCHeroStats* _this, void* _EDX, float percentage)
{
	OForceStaminaTo(_this, percentage);
}

void CTCHeroStats::ForceStaminaTo(float percentage)
{
	OForceStaminaTo(this, percentage);
}

void(__thiscall* CTCHeroStats::OFrameUpdate)(CTCHeroStats*) = nullptr;
void __fastcall CTCHeroStats::HFrameUpdate(CTCHeroStats* _this, void* _EDX)
{
	OFrameUpdate(_this);

	for (const auto& pair : frameUpdateCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

void CTCHeroStats::Hook()
{
	ADD_HOOK(0x0057A774, HSetMoney, OSetMoney);
	ADD_HOOK(0x0057B05F, HSetAge, OSetAge);
	ADD_HOOK(0x0057C2E6, HSetMorality, OSetMorality);
	ADD_HOOK(0x0057B169, HSetFatness, OSetFatness);
	ADD_HOOK(0x0057B0F7, HSetSunTan, OSetSunTan);
	ADD_HOOK(0x0057B26F, HForceStaminaTo, OForceStaminaTo);
	ADD_HOOK(0x0057CB00, HForceRenownLevelTo, OForceRenownLevelTo);
	ADD_HOOK(0x0057D5A0, HFrameUpdate, OFrameUpdate);
}
