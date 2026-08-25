#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "HeroTrainableStatType.h"

class CTCHeroExperience
{
public:
	void ForceTrainableStatLevelTo(EHeroTrainableStatType stat_type, long level);
	long GetTrainableStatLevel(EHeroTrainableStatType stat_type);

	std::vector<long> GetAllTrainableStatLevels();
	void SetAllTrainableStatLevels(const std::vector<long>& levels);

	void AddFrameUpdateCallback(const std::string& id, std::function<void()> callback) { frameUpdateCallbacks[id] = callback; }
	void RemoveFrameUpdateCallback(const std::string& id) { frameUpdateCallbacks.erase(id); }

    static void Hook();

private:
	static std::map<std::string, std::function<void()>> frameUpdateCallbacks;

    static void(__thiscall* OForceTrainableStatLevelTo)(CTCHeroExperience*, EHeroTrainableStatType, long);
    static void __fastcall HForceTrainableStatLevelTo(CTCHeroExperience* _this, void* _EDX, EHeroTrainableStatType stat_type, long level);

	static long(__thiscall* OGetTrainableStatLevel)(CTCHeroExperience*, EHeroTrainableStatType);
	static long __fastcall HGetTrainableStatLevel(CTCHeroExperience* _this, void* _EDX, EHeroTrainableStatType stat_type);

	static void(__thiscall* OFrameUpdate)(CTCHeroExperience*);
	static void __fastcall HFrameUpdate(CTCHeroExperience* _this, void* _EDX);
};
