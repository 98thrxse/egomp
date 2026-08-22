#pragma once

#include <iostream>
#include <vector>

#include "../Utils/Hook.h"

#include "HeroTrainableStatType.h"

class CTCHeroExperience
{
public:
	void ForceTrainableStatLevelTo(EHeroTrainableStatType stat_type, long level);
	long GetTrainableStatLevel(EHeroTrainableStatType stat_type);

	std::vector<long> GetAllTrainableStatLevels();
	void SetAllTrainableStatLevels(const std::vector<long>& levels);

    static void Hook();

private:
    static void(__thiscall* OForceTrainableStatLevelTo)(CTCHeroExperience*, EHeroTrainableStatType, long);
    static void __fastcall HForceTrainableStatLevelTo(CTCHeroExperience* _this, void* _EDX, EHeroTrainableStatType stat_type, long level);

	static long(__thiscall* OGetTrainableStatLevel)(CTCHeroExperience*, EHeroTrainableStatType);
	static long __fastcall HGetTrainableStatLevel(CTCHeroExperience* _this, void* _EDX, EHeroTrainableStatType stat_type);
};
