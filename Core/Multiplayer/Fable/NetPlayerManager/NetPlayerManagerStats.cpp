#include "NetPlayerManager.h"

enum Stats : int
{
    MONEY = 1 << 0,
    MORALITY = 1 << 1,
    AGE = 1 << 2,
    SUNTAN = 1 << 3,
    FATNESS = 1 << 4,
    RENOWN = 1 << 5,
    STAMINA = 1 << 6,
	HEALTH = 1 << 7,
	MAXHEALTH = 1 << 8,
    TRAINABLE_LEVELS = 1 << 9
};

void NetPlayerManager::ReceiveNetPlayerStats(int networkId, SLNet::BitStream& bsIn)
{
    int money = 0;
    int morality = 0;
    float age = 0;
    float sunTan = 0;
    float fatness = 0;
    int renownLevel = 0;
    float stamina = 0;

	float health = 0;
	float maxHealth = 0;

    std::vector<long> trainableLevels(NumberOfTrainableHeroStats, 0);

    int statsFlags = 0;
    bsIn.Read(statsFlags);

    if (statsFlags & MONEY)
        bsIn.Read(money);

    if (statsFlags & MORALITY)
        bsIn.Read(morality);

    if (statsFlags & AGE)
        bsIn.Read(age);

    if (statsFlags & SUNTAN)
        bsIn.Read(sunTan);

    if (statsFlags & FATNESS)
        bsIn.Read(fatness);

    if (statsFlags & RENOWN)
        bsIn.Read(renownLevel);

    if (statsFlags & STAMINA)
        bsIn.Read(stamina);

    if (statsFlags & HEALTH)
		bsIn.Read(health);

	if (statsFlags & MAXHEALTH)
		bsIn.Read(maxHealth);

    if (statsFlags & TRAINABLE_LEVELS)
    {
        for (int i = 0; i < NumberOfTrainableHeroStats; ++i)
        {
            long level = 0;
            bsIn.Read(level);
            trainableLevels[i] = level;
        }
    }

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_STATS);
        bsOut.Write(networkId);
        bsOut.Write(statsFlags);

        if (statsFlags & MONEY)
            bsOut.Write(money);

        if (statsFlags & MORALITY)
            bsOut.Write(morality);

        if (statsFlags & AGE)
            bsOut.Write(age);

        if (statsFlags & SUNTAN)
            bsOut.Write(sunTan);

        if (statsFlags & FATNESS)
            bsOut.Write(fatness);

        if (statsFlags & RENOWN)
            bsOut.Write(renownLevel);

        if (statsFlags & STAMINA)
            bsOut.Write(stamina);

		if (statsFlags & HEALTH)
			bsOut.Write(health);

		if (statsFlags & MAXHEALTH)
			bsOut.Write(maxHealth);

        if (statsFlags & TRAINABLE_LEVELS)
        {
            for (long level : trainableLevels)
                bsOut.Write(level);
        }

        network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed(), LOW_PRIORITY, RELIABLE_ORDERED);
    }

    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !creature" << std::endl;
        return;
    }

    CTCHeroStats* heroStats = reinterpret_cast<CTCHeroStats*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_STATS)
        );

    if (!heroStats) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !heroStats" << std::endl;
        return;
    }

    CTCHeroExperience* heroExperience = reinterpret_cast<CTCHeroExperience*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_EXPERIENCE)
        );

    if (!heroExperience) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !heroExperience" << std::endl;
        return;
    }

    if (statsFlags & AGE)
        heroStats->SetAge(age);

    if (statsFlags & MORALITY)
        heroStats->SetMorality(morality);

    if (statsFlags & SUNTAN)
        heroStats->SetSunTan(sunTan);

    if (statsFlags & FATNESS)
        heroStats->SetFatness(fatness);

    if (statsFlags & MONEY)
        heroStats->SetMoney(money, false);

    if (statsFlags & RENOWN)
        heroStats->ForceRenownLevelTo(renownLevel);

    if (statsFlags & STAMINA)
        heroStats->ForceStaminaTo(stamina);

    CThingPhysical* creaturePhysical = reinterpret_cast<CThingPhysical*>(creature);

	if (statsFlags & HEALTH)
		creaturePhysical->SetHealth(health);

	if (statsFlags & MAXHEALTH)
		creaturePhysical->SetMaxHealth(maxHealth, false);

    if (statsFlags & TRAINABLE_LEVELS)
		heroExperience->SetAllTrainableStatLevels(trainableLevels);
}

void NetPlayerManager::BroadcastLocalNetPlayerStats(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerStats]: !creature" << std::endl;
        return;
    }

    CTCHeroStats* heroStats = reinterpret_cast<CTCHeroStats*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_STATS)
        );

    if (!heroStats) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerStats]: !heroStats" << std::endl;
        return;
    }

    CTCHeroExperience* heroExperience = reinterpret_cast<CTCHeroExperience*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_EXPERIENCE)
        );

    if (!heroExperience) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerStats]: !heroExperience" << std::endl;
        return;
    }

    auto lastSendTime = std::chrono::steady_clock::now();

    heroStats->AddFrameUpdateCallback(
        "FrameUpdate" + std::to_string(networkId),
        [this, networkId, creature, heroStats, heroExperience, lastSendTime]() mutable
        {
            auto now = std::chrono::steady_clock::now();

            if (now - lastSendTime < std::chrono::milliseconds(200))
                return;

            lastSendTime = now;

            int statsFlags = 0;

            int money = heroStats->Money;
            int morality = heroStats->Morality;
            float age = heroStats->Age;
            float sunTan = heroStats->SunTan;
            float fatness = heroStats->Fatness;
            int renownLevel = heroStats->RenownLevel;
            float stamina = (heroStats->MaxStamina > 0)
                ? static_cast<float>(heroStats->Stamina) /
                static_cast<float>(heroStats->MaxStamina)
                : 0.0f;

			CThingPhysical* creaturePhysical = reinterpret_cast<CThingPhysical*>(creature);

            float health = creaturePhysical->Health;
            float maxHealth = creaturePhysical->MaxHealth;

            std::vector<long> trainableLevels = heroExperience->GetAllTrainableStatLevels();

            if (money != localNetPlayer->GetMoney())
                statsFlags |= MONEY;

            if (morality != localNetPlayer->GetMorality())
                statsFlags |= MORALITY;

            if (age != localNetPlayer->GetAge())
                statsFlags |= AGE;

            if (sunTan != localNetPlayer->GetSunTan())
                statsFlags |= SUNTAN;

            if (fatness != localNetPlayer->GetFatness())
                statsFlags |= FATNESS;

            if (renownLevel != localNetPlayer->GetRenownLevel())
                statsFlags |= RENOWN;

            if (stamina != localNetPlayer->GetStamina())
                statsFlags |= STAMINA;

			if (health != localNetPlayer->GetHealth())
				statsFlags |= HEALTH;

			if (maxHealth != localNetPlayer->GetMaxHealth())
				statsFlags |= MAXHEALTH;

            if (trainableLevels != localNetPlayer->GetAllTrainableStatLevels())
                statsFlags |= TRAINABLE_LEVELS;

            if (statsFlags == 0)
                return;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_STATS);
            bs.Write(networkId);
            bs.Write(statsFlags);

            if (statsFlags & MONEY)
            {
                bs.Write(money);
                localNetPlayer->SetMoney(money);
            }

            if (statsFlags & MORALITY)
            {
                bs.Write(morality);
                localNetPlayer->SetMorality(morality);
            }

            if (statsFlags & AGE)
            {
                bs.Write(age);
                localNetPlayer->SetAge(age);
            }

            if (statsFlags & SUNTAN)
            {
                bs.Write(sunTan);
                localNetPlayer->SetSunTan(sunTan);
            }

            if (statsFlags & FATNESS)
            {
                bs.Write(fatness);
                localNetPlayer->SetFatness(fatness);
            }

            if (statsFlags & RENOWN)
            {
                bs.Write(renownLevel);
                localNetPlayer->SetRenownLevel(renownLevel);
            }

            if (statsFlags & STAMINA)
            {
                bs.Write(stamina);
                localNetPlayer->SetStamina(stamina);
            }

            if (statsFlags & HEALTH)
            {
                bs.Write(health);
                localNetPlayer->SetHealth(health);
			}

            if (statsFlags & MAXHEALTH)
            {
                bs.Write(maxHealth);
                localNetPlayer->SetMaxHealth(maxHealth);
            }

            if (statsFlags & TRAINABLE_LEVELS)
            {
                for (long level : trainableLevels)
                    bs.Write(level);

                localNetPlayer->SetTrainableStatLevels(trainableLevels);
            }

            if (localNetPlayer->GetNetworkId() == 0)
            {
                network->SendToAllClientsExcept(
                    networkId,
                    (const char*)bs.GetData(),
                    bs.GetNumberOfBytesUsed(),
                    LOW_PRIORITY,
                    RELIABLE_ORDERED
                );
            }
            else
            {
                network->SendToHost(
                    (const char*)bs.GetData(),
                    bs.GetNumberOfBytesUsed(),
                    LOW_PRIORITY,
                    RELIABLE_ORDERED
                );
            }
        }
    );
}

void NetPlayerManager::BroadcastAllLocalNetPlayerStats(
    int networkId,
    int targetNetworkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastAllLocalNetPlayerStats]: !creature" << std::endl;
        return;
    }

    CTCHeroStats* heroStats = reinterpret_cast<CTCHeroStats*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_STATS)
        );

    if (!heroStats)
    {
        std::cout << "[NetPlayerManager::BroadcastAllLocalNetPlayerStats]: !heroStats" << std::endl;
        return;
    }

    CTCHeroExperience* heroExperience = reinterpret_cast<CTCHeroExperience*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_EXPERIENCE)
        );

    if (!heroExperience)
    {
        std::cout << "[NetPlayerManager::BroadcastAllLocalNetPlayerStats]: !heroExperience" << std::endl;
        return;
    }

    int statsFlags =
        MONEY |
        MORALITY |
        AGE |
        SUNTAN |
        FATNESS |
        RENOWN |
        STAMINA |
		HEALTH |
		MAXHEALTH |
        TRAINABLE_LEVELS;

    int money = heroStats->Money;
    int morality = heroStats->Morality;
    float age = heroStats->Age;
    float sunTan = heroStats->SunTan;
    float fatness = heroStats->Fatness;
    int renownLevel = heroStats->RenownLevel;

    float stamina = heroStats->MaxStamina > 0
        ? static_cast<float>(heroStats->Stamina) /
        static_cast<float>(heroStats->MaxStamina)
        : 0.0f;

    CThingPhysical* creaturePhysical = reinterpret_cast<CThingPhysical*>(creature);

    float health = creaturePhysical->Health;
    float maxHealth = creaturePhysical->MaxHealth;

    std::vector<long> trainableLevels = heroExperience->GetAllTrainableStatLevels();

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_PLAYER_STATS);
    bs.Write(networkId);
    bs.Write(statsFlags);

    if (statsFlags & MONEY)
        bs.Write(money);

    if (statsFlags & MORALITY)
        bs.Write(morality);

    if (statsFlags & AGE)
        bs.Write(age);

    if (statsFlags & SUNTAN)
        bs.Write(sunTan);

    if (statsFlags & FATNESS)
        bs.Write(fatness);

    if (statsFlags & RENOWN)
        bs.Write(renownLevel);

    if (statsFlags & STAMINA)
        bs.Write(stamina);

    if (statsFlags & HEALTH)
        bs.Write(health);

    if (statsFlags & MAXHEALTH)
        bs.Write(maxHealth);

    if (statsFlags & TRAINABLE_LEVELS)
    {
        for (long level : trainableLevels)
            bs.Write(level);
    }

    if (targetNetworkId != -1)
    {
        network->SendToClient(
            targetNetworkId,
            (const char*)bs.GetData(),
            bs.GetNumberOfBytesUsed(),
            LOW_PRIORITY,
            RELIABLE_ORDERED
        );
        return;
    }

    if (localNetPlayer->GetNetworkId() == 0)
    {
        network->SendToAllClientsExcept(
            networkId,
            (const char*)bs.GetData(),
            bs.GetNumberOfBytesUsed(),
            LOW_PRIORITY,
            RELIABLE_ORDERED
        );
    }
    else
    {
        network->SendToHost(
            (const char*)bs.GetData(),
            bs.GetNumberOfBytesUsed(),
            LOW_PRIORITY,
            RELIABLE_ORDERED
        );
    }
}
