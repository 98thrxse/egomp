#include "NetPlayerManager.h"

enum Experience : int
{
    TRAINABLE_LEVELS = 1 << 0
};

void NetPlayerManager::ReceiveNetPlayerExperience(int networkId, SLNet::BitStream& bsIn)
{
    std::vector<long> trainableLevels(NUMBER_OF_TRAINABLE_HERO_STATS, 0);

    int experienceFlags = 0;
    bsIn.Read(experienceFlags);

    if (experienceFlags & TRAINABLE_LEVELS)
    {
        for (int i = 0; i < NUMBER_OF_TRAINABLE_HERO_STATS; ++i)
        {
            long level = 0;
            bsIn.Read(level);
            trainableLevels[i] = level;
        }
    }

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_EXPERIENCE);
        bsOut.Write(networkId);
        bsOut.Write(experienceFlags);

        if (experienceFlags & TRAINABLE_LEVELS)
        {
            for (long level : trainableLevels)
                bsOut.Write(level);
        }

        network->SendToAllClientsExcept(
            networkId,
            (const char*)bsOut.GetData(),
            bsOut.GetNumberOfBytesUsed(),
            LOW_PRIORITY,
            RELIABLE_ORDERED
        );
    }

    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
        return;

    CTCHeroExperience* heroExperience =
        reinterpret_cast<CTCHeroExperience*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_HERO_EXPERIENCE
            )
            );

    if (!heroExperience)
    {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerExperience]: !heroExperience" << std::endl;
        return;
    }

    for (auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetNetworkId() == networkId)
        {
            if (experienceFlags & TRAINABLE_LEVELS)
            {
                heroExperience->SetAllTrainableStatLevels(trainableLevels);
                netPlayer->SetTrainableStatLevels(trainableLevels);
            }

            return;
        }
    }
}

void NetPlayerManager::BroadcastLocalNetPlayerExperience(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerExperience]: !creature" << std::endl;
        return;
    }

    CTCHeroExperience* heroExperience =
        reinterpret_cast<CTCHeroExperience*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_HERO_EXPERIENCE
            )
            );

    if (!heroExperience)
    {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerExperience]: !heroExperience" << std::endl;
        return;
    }

    auto lastSendTime = std::chrono::steady_clock::now();

    heroExperience->AddFrameUpdateCallback(
        "ExperienceFrameUpdate" + std::to_string(networkId),
        [this, networkId, heroExperience, lastSendTime]() mutable
        {
            auto now = std::chrono::steady_clock::now();

            if (now - lastSendTime < std::chrono::milliseconds(200))
                return;

            lastSendTime = now;

            std::vector<long> trainableLevels =
                heroExperience->GetAllTrainableStatLevels();

            int experienceFlags = 0;

            if (trainableLevels != localNetPlayer->GetAllTrainableStatLevels())
                experienceFlags |= TRAINABLE_LEVELS;

            if (experienceFlags == 0)
                return;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_EXPERIENCE);
            bs.Write(networkId);
            bs.Write(experienceFlags);

            if (experienceFlags & TRAINABLE_LEVELS)
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

void NetPlayerManager::BroadcastNetPlayerExperience(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerExperience]: !creature" << std::endl;
        return;
    }

    CTCHeroExperience* heroExperience =
        reinterpret_cast<CTCHeroExperience*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_HERO_EXPERIENCE
            )
            );

    if (!heroExperience)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerExperience]: !heroExperience" << std::endl;
        return;
    }

    std::vector<long> trainableLevels =
        heroExperience->GetAllTrainableStatLevels();

    int experienceFlags = TRAINABLE_LEVELS;

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_PLAYER_EXPERIENCE);
    bs.Write(networkId);
    bs.Write(experienceFlags);

    if (experienceFlags & TRAINABLE_LEVELS)
    {
        for (long level : trainableLevels)
            bs.Write(level);
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
