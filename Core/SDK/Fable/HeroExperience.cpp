#include "HeroExperience.h"

void(__thiscall* CTCHeroExperience::OForceTrainableStatLevelTo)(CTCHeroExperience*, EHeroTrainableStatType, long) = nullptr;
void __fastcall CTCHeroExperience::HForceTrainableStatLevelTo(CTCHeroExperience* _this, void* _EDX, EHeroTrainableStatType stat_type, long level)
{
	OForceTrainableStatLevelTo(_this, stat_type, level);
}

void CTCHeroExperience::ForceTrainableStatLevelTo(EHeroTrainableStatType stat_type, long level)
{
	OForceTrainableStatLevelTo(this, stat_type, level);
}

long(__thiscall* CTCHeroExperience::OGetTrainableStatLevel)(CTCHeroExperience*, EHeroTrainableStatType) = nullptr;
long __fastcall CTCHeroExperience::HGetTrainableStatLevel(CTCHeroExperience* _this, void* _EDX, EHeroTrainableStatType stat_type)
{
	return OGetTrainableStatLevel(_this, stat_type);
}

long CTCHeroExperience::GetTrainableStatLevel(EHeroTrainableStatType stat_type)
{
	return OGetTrainableStatLevel(this, stat_type);
}

std::vector<long> CTCHeroExperience::GetAllTrainableStatLevels()
{
	std::vector<long> levels;
	for (int i = 0; i < NUMBER_OF_TRAINABLE_HERO_STATS; ++i)
		levels.push_back(GetTrainableStatLevel((EHeroTrainableStatType)i));
	return levels;
}

void CTCHeroExperience::SetAllTrainableStatLevels(const std::vector<long>& levels)
{
	for (size_t i = 0; i < levels.size() && i < NUMBER_OF_TRAINABLE_HERO_STATS; ++i)
		ForceTrainableStatLevelTo((EHeroTrainableStatType)i, levels[i]);
}

void CTCHeroExperience::Hook()
{
	ADD_HOOK(0x006D8A40, HForceTrainableStatLevelTo, OForceTrainableStatLevelTo);
	ADD_HOOK(0x006D6520, HGetTrainableStatLevel, OGetTrainableStatLevel);
}
