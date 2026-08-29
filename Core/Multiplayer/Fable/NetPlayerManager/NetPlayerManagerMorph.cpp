#include "NetPlayerManager.h"

enum Morph : int
{
    TATTOOS = 1 << 0
};

void NetPlayerManager::ReceiveNetPlayerMorph(int networkId, SLNet::BitStream& bsIn)
{
    std::vector<long> tattooIndexes;

    int morphFlags = 0;
    bsIn.Read(morphFlags);

    if (morphFlags & TATTOOS)
    {
        int tattooCount = 0;
        bsIn.Read(tattooCount);

        tattooIndexes.resize(tattooCount);

        for (int i = 0; i < tattooCount; ++i)
            bsIn.Read(tattooIndexes[i]);
    }

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_MORPH);
        bsOut.Write(networkId);
        bsOut.Write(morphFlags);

        if (morphFlags & TATTOOS)
        {
            bsOut.Write((int)tattooIndexes.size());

            for (long index : tattooIndexes)
                bsOut.Write(index);
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

    CTCHeroMorph* heroMorph =
        reinterpret_cast<CTCHeroMorph*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_APPEARANCE_MORPH
            )
            );

    if (!heroMorph)
    {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerMorph]: !heroMorph" << std::endl;
        return;
    }

    for (auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetNetworkId() == networkId)
        {
            if (morphFlags & TATTOOS)
            {
                heroMorph->SetTattooIndexes(tattooIndexes);
                netPlayer->SetTattooIndexes(tattooIndexes);
            }

            RefreshNetPlayerMorph(heroMorph, networkId);

            return;
        }
    }
}

void NetPlayerManager::BroadcastLocalNetPlayerMorph(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerMorph]: !creature" << std::endl;
        return;
    }

    CTCHeroMorph* heroMorph =
        reinterpret_cast<CTCHeroMorph*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_APPEARANCE_MORPH
            )
            );

    if (!heroMorph)
    {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerMorph]: !heroMorph" << std::endl;
        return;
    }

    auto lastSendTime = std::chrono::steady_clock::now();

    heroMorph->AddFrameUpdateCallback(
        "MorphFrameUpdate" + std::to_string(networkId),
        [this, networkId, heroMorph, lastSendTime]() mutable
        {
            auto now = std::chrono::steady_clock::now();

            if (now - lastSendTime < std::chrono::milliseconds(200))
                return;

            lastSendTime = now;

            std::vector<long> tattooIndexes =
                heroMorph->GetAllTattooIndexes();

            int morphFlags = 0;

            if (tattooIndexes != localNetPlayer->GetAllTattooIndexes())
                morphFlags |= TATTOOS;

            if (morphFlags == 0)
                return;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_MORPH);
            bs.Write(networkId);
            bs.Write(morphFlags);

            if (morphFlags & TATTOOS)
            {
                bs.Write((int)tattooIndexes.size());

                for (long index : tattooIndexes)
                    bs.Write(index);

                localNetPlayer->SetTattooIndexes(tattooIndexes);
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

void NetPlayerManager::BroadcastNetPlayerMorph(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerMorph]: !creature" << std::endl;
        return;
    }

    CTCHeroMorph* heroMorph =
        reinterpret_cast<CTCHeroMorph*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_APPEARANCE_MORPH
            )
            );

    if (!heroMorph)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerMorph]: !heroMorph" << std::endl;
        return;
    }

    std::vector<long> tattooIndexes =
        heroMorph->GetAllTattooIndexes();

    int morphFlags = TATTOOS;

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_PLAYER_MORPH);
    bs.Write(networkId);
    bs.Write(morphFlags);

    if (morphFlags & TATTOOS)
    {
        bs.Write((int)tattooIndexes.size());

        for (long index : tattooIndexes)
            bs.Write(index);
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

void NetPlayerManager::RefreshNetPlayerMorph(
    CTCHeroMorph* heroMorph,
    int networkId)
{
    heroMorph->DoMorphUpdate();

    auto meshMorphSet =
        *reinterpret_cast<uintptr_t*>(
            reinterpret_cast<uintptr_t>(heroMorph) + 0x0C);

    if (!meshMorphSet)
        return;

    auto morphs = meshMorphSet + 0x0C;

    auto first = *reinterpret_cast<uintptr_t*>(morphs + 0x00);
    auto last = *reinterpret_cast<uintptr_t*>(morphs + 0x04);

    int localId = GetLocalIdFromNetworkId(networkId);

    for (auto morph = first; morph < last; morph += 0x14)
        *reinterpret_cast<int*>(morph + 0x04) = localId + 1;

    reinterpret_cast<CTCAppearanceMorphBase*>(heroMorph)
        ->UploadTextureMorphsToEngine(
            *iengine,
            nullptr,
            false,
            0.0f
        );
}
