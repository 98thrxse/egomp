#pragma once

#include <iostream>
#include <vector>

#include "../../../SDK/Fable/SDK.h"

class LocalNetPlayer
{
private:
    int networkId;
    int localId;

    C3DVector position;
    CRightHandedSet rhSet;

    int money;
    int morality;
    float age;
    float sunTan;
    float fatness;
    int renownLevel;
    float stamina;

    float maxHealth;
    float health;

    std::vector<long> trainableStatLevels;
    std::vector<std::vector<long>> appearanceModifiers;

public:
    LocalNetPlayer();
    ~LocalNetPlayer() = default;

    void SetNetworkId(int id);
    int GetNetworkId() const;

    void SetLocalId(int id);
    int GetLocalId() const;

    void SetPosition(C3DVector position);
    C3DVector GetPosition() const;

    void SetRHSet(CRightHandedSet rhSet);
    CRightHandedSet GetRHSet() const;

    void SetMoney(int money);
    int GetMoney() const;

    void SetMorality(int morality);
    int GetMorality() const;

    void SetAge(float age);
    float GetAge() const;

    void SetSunTan(float sunTan);
    float GetSunTan() const;

    void SetFatness(float fatness);
    float GetFatness() const;

    void SetRenownLevel(int renownLevel);
    int GetRenownLevel() const;

	void SetStamina(float stamina);
	float GetStamina() const;

    void SetMaxHealth(float maxHealth);
    float GetMaxHealth() const;

    void SetHealth(float health);
	float GetHealth() const;

    void SetTrainableStatLevels(const std::vector<long>& trainableStatLevels);
    std::vector<long> GetAllTrainableStatLevels() const;

    void SetAppearanceModifiers(const std::vector<std::vector<long>>& appearanceModifiers);
    std::vector<std::vector<long>> GetAppearanceModifiers() const;
};
