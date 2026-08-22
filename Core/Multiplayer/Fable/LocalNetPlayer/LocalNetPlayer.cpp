#include "LocalNetPlayer.h"

LocalNetPlayer::LocalNetPlayer() :
    networkId(-1),
    localId(-1)
{
    position = C3DVector();
    rhSet = CRightHandedSet();

	money = 0;
    morality = 0;
    age = 0.0f;
    sunTan = 0.0f;
    fatness = 0.0f;
    renownLevel = 0;
	stamina = 0.0f;

    maxHealth = 0.0f;
	health = 0.0f;

    trainableStatLevels = std::vector<long>(NumberOfTrainableHeroStats, 0);
}

void LocalNetPlayer::SetNetworkId(int id)
{
    networkId = id;
}

int LocalNetPlayer::GetNetworkId() const
{
    return networkId;
}

void LocalNetPlayer::SetLocalId(int id)
{
    localId = id;
}

int LocalNetPlayer::GetLocalId() const
{
    return localId;
}

void LocalNetPlayer::SetPosition(C3DVector position)
{
    this->position = position;
}

C3DVector LocalNetPlayer::GetPosition() const
{
    return this->position;
}

void LocalNetPlayer::SetRHSet(CRightHandedSet rhSet)
{
    this->rhSet = rhSet;
}

CRightHandedSet LocalNetPlayer::GetRHSet() const
{
    return rhSet;
}

void LocalNetPlayer::SetMoney(int money)
{
    this->money = money;
}

int LocalNetPlayer::GetMoney() const
{
    return money;
}

void LocalNetPlayer::SetMorality(int morality)
{
    this->morality = morality;
}

int LocalNetPlayer::GetMorality() const
{
    return morality;
}

void LocalNetPlayer::SetAge(float age)
{
    this->age = age;
}

float LocalNetPlayer::GetAge() const
{
    return age;
}

void LocalNetPlayer::SetSunTan(float sunTan)
{
    this->sunTan = sunTan;
}

float LocalNetPlayer::GetSunTan() const
{
    return sunTan;
}

void LocalNetPlayer::SetFatness(float fatness)
{
    this->fatness = fatness;
}

float LocalNetPlayer::GetFatness() const
{
    return fatness;
}

void LocalNetPlayer::SetRenownLevel(int renownLevel)
{
    this->renownLevel = renownLevel;
}

int LocalNetPlayer::GetRenownLevel() const
{
    return renownLevel;
}

void LocalNetPlayer::SetStamina(float stamina)
{
    this->stamina = stamina;
}

float LocalNetPlayer::GetStamina() const
{
    return stamina;
}

void LocalNetPlayer::SetMaxHealth(float maxHealth)
{
    this->maxHealth = maxHealth;
}

float LocalNetPlayer::GetMaxHealth() const
{
    return maxHealth;
}

void LocalNetPlayer::SetHealth(float health)
{
    this->health = health;
}

float LocalNetPlayer::GetHealth() const
{
    return health;
}

void LocalNetPlayer::SetTrainableStatLevels(const std::vector<long>& trainableStatLevels)
{
    this->trainableStatLevels = trainableStatLevels;
}

std::vector<long> LocalNetPlayer::GetAllTrainableStatLevels() const
{
    return trainableStatLevels;
}
