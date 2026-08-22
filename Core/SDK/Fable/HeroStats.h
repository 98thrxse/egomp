#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "CharString.h"
#include "HeroTrainingStatus.h"

class CTCHeroStats
{
public:
    char pad0[0x0C];

    char pad1[0x0C];  // std::map<CCharString, CTCHeroStats::MirroredCriminalStatus> OutstandingCrimes;

    std::vector<long> ExperienceSpentOn;
    int NumberOfDecapitations;
    int Morality;
    bool MoralityChangingEnabled;

    char pad2[0x03];

    float Age;
    float SunTan;
    float Fatness;
    int Money;
    int MaxMoney;
    int ConfiscatedMoney;
    int TotalMoneyEarned;
    int TotalMoneySpent;
    int RewardMoney;
    int RentMoney;
    int Stamina;
    int MaxStamina;
    int FramesUntilStaminaRefills;
    int FramesUntilHealthRefills;
    bool ScriptOverridePreventStaminaRefill;

    char pad3[0x03];

    int FramesUntilFatnessReduces;
    int RenownLevel;
    int RenownMaxLevel;
    int RenownPointsInLevel;
    int RenownTotal;
    float Agreeableness;
    float InherentAttractiveness;
    float InherentScariness;
    float ExtraMaxHealth;
    int ExtraMaxStamina;
    int FramesLeftForSpeedMultiplier;
    int MaximumMultiplier;
    float Attractiveness;
    float Scariness;
    float AppearanceGoodstrength;
    float SoundRadiusMultiplier;
    float VisibilityMultiplier;
    int FrameUpdatedClothingStats;
    int FrameUpdatedTattooStats;
    int NumFailedAQuest;
    int NumCompletedAQuest;
    int NumCompletedACoreQuest;
    int NumCompletedAFeatQuest;
    int NumCompletedAnOptionalQuest;
    int NumBoastsTaken;
    int NumBoastsCompleted;
    int NumberOfTrophies;
    int NumTrophyGamePlayed;
    int BestTrophyWitnesses;
    int NumberOfShopsOwned;
    int NumberOfHousesOwned;
    int NumberOfBuildingsRented;
    int NumberOfVomits;
    int NumberOfDrinks;
    int NumberOfCrimes;
    int TotalFine;
    int FinePaid;
    int TimesThrownOut;
    int TotalBribeAmount;
    int NumTeleports;
    float MaxChickenThrow;
    EHeroTrainingStatus TrainingStatus;
    std::vector<long> HeroStatsExperience;
    std::vector<long> RegionTime;
    std::vector<long> NumberOfTimesUsedAbility;
    int TotalSpentExperience;
    int NumLoversAcquired;
    int NumWeddings;
    int NumSpousesMurdered;
    int NumDivorces;
    int NumSex;

    char pad4[0x0C]; // std::vector<std::pair<CRegion const*, C3DVector>> HousePositions;

    bool InfiniteStamina;

    char pad5[0x03];

    CCharString DeathRecoveryMarkerName;
    bool FailQuestOnDeath;

    char pad6[0x03];

    float BestTimePairs;
    float BestTimeSorting;
    float BestScoreBlackjack;
    float BestScoreCoinGolf;
    float BestScoreShoveHaPenny;
    float BestTimeGuessTheAddition;
    bool PrizeGivenPairs;
    bool PrizeGivenSorting;
    bool PrizeGivenBlackjack;
    bool PrizeGivenCoinGolf;
    bool PrizeGivenShoveHaPenny;
    bool PrizeGivenGuessTheAddition;

    char pad7[0x02];

    float Drunkenness;
    float BeerReservoir;
    float DrinkAffectMultiplier;
    float DrinkAffectMultiplierMultiplier;
    int FrameToVomit;
    int DeedHandle;
    int FrameEndVomit;
    bool UpdateDrunkenness;

    char pad8[8];

    char pad9[0x04]; // CDefPointer<CSpecialAbilitiesDrunkennessDef const> PDef;
    char pad10[0x08]; // CEnginePrimitiveHandle PrimitiveHandle;

    float UCounter;
    float VCounter;
    float RotCounter;
    bool IsInCutSceneFirstTime;

    char pad11[0x03];

    char pad12[0x04]; // std::list<CHeroMarriageInfo> Marriages;

    void SetMoney(long, bool);
    void SetAge(float);
    void SetMorality(long);
    void SetFatness(float);
    void SetSunTan(float);
    void ForceRenownLevelTo(long);
    void ForceStaminaTo(float);

    void AddFrameUpdateCallback(const std::string& id, std::function<void()> callback) { frameUpdateCallbacks[id] = callback; }
    void RemoveFrameUpdateCallback(const std::string& id) { frameUpdateCallbacks.erase(id); }

    static void Hook();

private:
	static std::map<std::string, std::function<void()>> frameUpdateCallbacks;

    static void(__thiscall* OSetMoney)(CTCHeroStats*, long, bool);
    static void __fastcall HSetMoney(CTCHeroStats* _this, void* _EDX, long money, bool track_for_money_earned_and_spent);

    static void(__thiscall* OSetAge)(CTCHeroStats*, float);
    static void __fastcall HSetAge(CTCHeroStats* _this, void* _EDX, float age);

    static void(__thiscall* OSetMorality)(CTCHeroStats*, long);
    static void __fastcall HSetMorality(CTCHeroStats* _this, void* _EDX, long morality);

    static void(__thiscall* OSetFatness)(CTCHeroStats*, float);
    static void __fastcall HSetFatness(CTCHeroStats* _this, void* _EDX, float fatness);

    static void(__thiscall* OSetSunTan)(CTCHeroStats*, float);
    static void __fastcall HSetSunTan(CTCHeroStats* _this, void* _EDX, float sunTan);

    static void(__thiscall* OFrameUpdate)(CTCHeroStats*);
    static void __fastcall HFrameUpdate(CTCHeroStats* _this, void* _EDX);

    static void(__thiscall* OForceRenownLevelTo)(CTCHeroStats*, long);
    static void __fastcall HForceRenownLevelTo(CTCHeroStats* _this, void* _EDX, long renown_level);

    static void(__thiscall* OForceStaminaTo)(CTCHeroStats*, float);
    static void __fastcall HForceStaminaTo(CTCHeroStats* _this, void* _EDX, float percentage);
};
