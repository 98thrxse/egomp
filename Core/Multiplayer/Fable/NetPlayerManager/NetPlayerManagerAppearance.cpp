#include "NetPlayerManager.h"

enum Appearance : int
{
    HAIR = 1 << 0,
    HORN = 1 << 1,
    CLOTHING = 1 << 2
};

void NetPlayerManager::ReceiveNetPlayerAppearance(int networkId, SLNet::BitStream& bsIn)
{
    std::vector<std::vector<long>> appearanceModifierLists(
        NO_OF_APPEARANCE_MODIFIER_TYPES
    );

    int appearanceFlags = 0;
    bsIn.Read(appearanceFlags);

    if (appearanceFlags & HAIR)
    {
        int count = 0;
        bsIn.Read(count);

        appearanceModifierLists[APPEARANCE_HAIR].resize(count);

        for (int i = 0; i < count; ++i)
            bsIn.Read(appearanceModifierLists[APPEARANCE_HAIR][i]);
    }

    if (appearanceFlags & HORN)
    {
        int count = 0;
        bsIn.Read(count);

        appearanceModifierLists[APPEARANCE_HORN].resize(count);

        for (int i = 0; i < count; ++i)
            bsIn.Read(appearanceModifierLists[APPEARANCE_HORN][i]);
    }

    if (appearanceFlags & CLOTHING)
    {
        int count = 0;
        bsIn.Read(count);

        appearanceModifierLists[APPEARANCE_CLOTHING].resize(count);

        for (int i = 0; i < count; ++i)
            bsIn.Read(appearanceModifierLists[APPEARANCE_CLOTHING][i]);
    }

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_APPEARANCE);
        bsOut.Write(networkId);
        bsOut.Write(appearanceFlags);

        if (appearanceFlags & HAIR)
        {
            bsOut.Write((int)appearanceModifierLists[APPEARANCE_HAIR].size());

            for (long defNum : appearanceModifierLists[APPEARANCE_HAIR])
                bsOut.Write(defNum);
        }

        if (appearanceFlags & HORN)
        {
            bsOut.Write((int)appearanceModifierLists[APPEARANCE_HORN].size());

            for (long defNum : appearanceModifierLists[APPEARANCE_HORN])
                bsOut.Write(defNum);
        }

        if (appearanceFlags & CLOTHING)
        {
            bsOut.Write((int)appearanceModifierLists[APPEARANCE_CLOTHING].size());

            for (long defNum : appearanceModifierLists[APPEARANCE_CLOTHING])
                bsOut.Write(defNum);
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

    CTCHeroAttachableAppearanceModifiers* appearanceModifiers =
        reinterpret_cast<CTCHeroAttachableAppearanceModifiers*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_HERO_ATTACHABLE_APPEARANCE_MODIFIERS
            )
        );

    if (!appearanceModifiers)
    {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerAppearance]: !appearanceModifiers" << std::endl;
        return;
    }

    for (auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetNetworkId() == networkId)
        {
            std::vector<std::vector<long>> currentLists =
                appearanceModifiers->GetAllAppearanceModifierLists();

            if (appearanceFlags & HAIR)
                currentLists[APPEARANCE_HAIR] = appearanceModifierLists[APPEARANCE_HAIR];

            if (appearanceFlags & HORN)
                currentLists[APPEARANCE_HORN] = appearanceModifierLists[APPEARANCE_HORN];

            if (appearanceFlags & CLOTHING)
                currentLists[APPEARANCE_CLOTHING] = appearanceModifierLists[APPEARANCE_CLOTHING];

            appearanceModifiers->SetAllAppearanceModifierLists(currentLists);
            netPlayer->SetAppearanceModifiers(currentLists);

            return;
        }
    }
}

void NetPlayerManager::BroadcastLocalNetPlayerAppearance(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAppearance]: !creature" << std::endl;
        return;
    }

    CTCHeroAttachableAppearanceModifiers* appearanceModifiers =
        reinterpret_cast<CTCHeroAttachableAppearanceModifiers*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_HERO_ATTACHABLE_APPEARANCE_MODIFIERS
            )
            );

    if (!appearanceModifiers)
    {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAppearance]: !appearanceModifiers" << std::endl;
        return;
    }

    auto lastSendTime = std::chrono::steady_clock::now();

    appearanceModifiers->AddFrameUpdateCallback(
        "AppearanceFrameUpdate" + std::to_string(networkId),
        [this, networkId, appearanceModifiers, lastSendTime]() mutable
        {
            auto now = std::chrono::steady_clock::now();

            if (now - lastSendTime < std::chrono::milliseconds(200))
                return;

            lastSendTime = now;

            std::vector<std::vector<long>> appearanceModifierLists =
                appearanceModifiers->GetAllAppearanceModifierLists();

            std::vector<std::vector<long>> lastAppearanceModifierLists =
                localNetPlayer->GetAppearanceModifiers();

            int appearanceFlags = 0;

            if (appearanceModifierLists[APPEARANCE_HAIR] != lastAppearanceModifierLists[APPEARANCE_HAIR])
                appearanceFlags |= HAIR;

            if (appearanceModifierLists[APPEARANCE_HORN] != lastAppearanceModifierLists[APPEARANCE_HORN])
                appearanceFlags |= HORN;

            if (appearanceModifierLists[APPEARANCE_CLOTHING] != lastAppearanceModifierLists[APPEARANCE_CLOTHING])
                appearanceFlags |= CLOTHING;

            if (appearanceFlags == 0)
                return;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_APPEARANCE);
            bs.Write(networkId);
            bs.Write(appearanceFlags);

            if (appearanceFlags & HAIR)
            {
                bs.Write((int)appearanceModifierLists[APPEARANCE_HAIR].size());

                for (long defNum : appearanceModifierLists[APPEARANCE_HAIR])
                    bs.Write(defNum);
            }

            if (appearanceFlags & HORN)
            {
                bs.Write((int)appearanceModifierLists[APPEARANCE_HORN].size());

                for (long defNum : appearanceModifierLists[APPEARANCE_HORN])
                    bs.Write(defNum);
            }

            if (appearanceFlags & CLOTHING)
            {
                bs.Write((int)appearanceModifierLists[APPEARANCE_CLOTHING].size());

                for (long defNum : appearanceModifierLists[APPEARANCE_CLOTHING])
                    bs.Write(defNum);
            }

            localNetPlayer->SetAppearanceModifiers(
                appearanceModifierLists
            );

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

void NetPlayerManager::BroadcastNetPlayerAppearance(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerAppearance]: !creature" << std::endl;
        return;
    }

    CTCHeroAttachableAppearanceModifiers* appearanceModifiers =
        reinterpret_cast<CTCHeroAttachableAppearanceModifiers*>(
            reinterpret_cast<CThing*>(creature)->GetTC(
                TCI_HERO_ATTACHABLE_APPEARANCE_MODIFIERS
            )
            );

    if (!appearanceModifiers)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerAppearance]: !appearanceModifiers" << std::endl;
        return;
    }

    std::vector<std::vector<long>> appearanceModifierLists =
        appearanceModifiers->GetAllAppearanceModifierLists();

    int appearanceFlags =
        HAIR |
        HORN |
        CLOTHING;

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_PLAYER_APPEARANCE);
    bs.Write(networkId);
    bs.Write(appearanceFlags);

    if (appearanceFlags & HAIR)
    {
        bs.Write((int)appearanceModifierLists[APPEARANCE_HAIR].size());

        for (long defNum : appearanceModifierLists[APPEARANCE_HAIR])
            bs.Write(defNum);
    }

    if (appearanceFlags & HORN)
    {
        bs.Write((int)appearanceModifierLists[APPEARANCE_HORN].size());

        for (long defNum : appearanceModifierLists[APPEARANCE_HORN])
            bs.Write(defNum);
    }

    if (appearanceFlags & CLOTHING)
    {
        bs.Write((int)appearanceModifierLists[APPEARANCE_CLOTHING].size());

        for (long defNum : appearanceModifierLists[APPEARANCE_CLOTHING])
            bs.Write(defNum);
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
