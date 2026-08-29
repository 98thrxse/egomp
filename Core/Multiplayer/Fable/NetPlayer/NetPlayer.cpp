#include "NetPlayer.h"

NetPlayer::NetPlayer() :
    networkId(-1),
    localId(-1)
{
    movementAcceleration = C3DVector();
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

    trainableStatLevels = std::vector<long>(NUMBER_OF_TRAINABLE_HERO_STATS, 0);
    appearanceModifiers = std::vector<std::vector<long>>(NO_OF_APPEARANCE_MODIFIER_TYPES);
    tattooIndexes = std::vector<long>();
}

void NetPlayer::SetNetworkId(int id)
{
    networkId = id;
}

int NetPlayer::GetNetworkId() const
{
    return networkId;
}

void NetPlayer::SetLocalId(int id)
{
    localId = id;
}

int NetPlayer::GetLocalId() const
{
    return localId;
}

void NetPlayer::SetMovementAcceleration(C3DVector movementAcceleration)
{
    this->movementAcceleration = movementAcceleration;
}

C3DVector NetPlayer::GetMovementAcceleration() const
{
    return movementAcceleration;
}

void NetPlayer::SetPosition(C3DVector position)
{
    this->position = position;
}

C3DVector NetPlayer::GetPosition() const
{
    return this->position;
}

void NetPlayer::SetRHSet(CRightHandedSet rhSet)
{
    this->rhSet = rhSet;
}

CRightHandedSet NetPlayer::GetRHSet() const
{
    return rhSet;
}

void NetPlayer::SetMoney(int money)
{
    this->money = money;
}

int NetPlayer::GetMoney() const
{
    return money;
}

void NetPlayer::SetMorality(int morality)
{
    this->morality = morality;
}

int NetPlayer::GetMorality() const
{
    return morality;
}

void NetPlayer::SetAge(float age)
{
    this->age = age;
}

float NetPlayer::GetAge() const
{
    return age;
}

void NetPlayer::SetSunTan(float sunTan)
{
    this->sunTan = sunTan;
}

float NetPlayer::GetSunTan() const
{
    return sunTan;
}

void NetPlayer::SetFatness(float fatness)
{
    this->fatness = fatness;
}

float NetPlayer::GetFatness() const
{
    return fatness;
}

void NetPlayer::SetRenownLevel(int renownLevel)
{
    this->renownLevel = renownLevel;
}

int NetPlayer::GetRenownLevel() const
{
    return renownLevel;
}

void NetPlayer::SetStamina(float stamina)
{
    this->stamina = stamina;
}

float NetPlayer::GetStamina() const
{
    return stamina;
}

void NetPlayer::SetMaxHealth(float maxHealth)
{
    this->maxHealth = maxHealth;
}

float NetPlayer::GetMaxHealth() const
{
    return maxHealth;
}

void NetPlayer::SetHealth(float health)
{
    this->health = health;
}

float NetPlayer::GetHealth() const
{
    return health;
}

void NetPlayer::SetTrainableStatLevels(const std::vector<long>& trainableStatLevels)
{
    this->trainableStatLevels = trainableStatLevels;
}

std::vector<long> NetPlayer::GetAllTrainableStatLevels() const
{
    return trainableStatLevels;
}

void NetPlayer::SetAppearanceModifiers(const std::vector<std::vector<long>>& appearanceModifiers)
{
    this->appearanceModifiers = appearanceModifiers;
}

std::vector<std::vector<long>> NetPlayer::GetAppearanceModifiers() const
{
    return appearanceModifiers;
}

void NetPlayer::SetTattooIndexes(const std::vector<long>& tattooIndexes)
{
    this->tattooIndexes = tattooIndexes;
}

std::vector<long> NetPlayer::GetAllTattooIndexes() const
{
    return tattooIndexes;
}
