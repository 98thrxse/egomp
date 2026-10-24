#include "NetPlayerManager.h"

enum HeroParams : int
{
    WEAPONS_USABLE = 1 << 0,
    WILL_USABLE = 1 << 1
};

void NetPlayerManager::ReceiveNetPlayerHero(SLNet::BitStream& bsIn)
{
    int networkId = -1;
    int heroFlags = 0;
    bool weaponsUsable = false;
    bool willUsable = false;

    bsIn.Read(networkId);
    bsIn.Read(heroFlags);

    if (heroFlags & WEAPONS_USABLE)
        bsIn.Read(weaponsUsable);

    if (heroFlags & WILL_USABLE)
        bsIn.Read(willUsable);

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_HERO);
        bsOut.Write(networkId);
        bsOut.Write(heroFlags);

        if (heroFlags & WEAPONS_USABLE)
            bsOut.Write(weaponsUsable);

        if (heroFlags & WILL_USABLE)
            bsOut.Write(willUsable);

        network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed(), LOW_PRIORITY, RELIABLE_ORDERED);
    }

    CThingPlayerCreature* netCreature = GetPlayerCreatureFromNetworkId(networkId);

    if (!netCreature)
        return;

    CTCHero* netHero = reinterpret_cast<CTCHero*>(
        reinterpret_cast<CThing*>(netCreature)->GetTC(TCI_HERO)
        );

    if (!netHero) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerHero]: !netHero" << std::endl;
        return;
    }

    if (localNetPlayer->GetNetworkId() != 0)
    {
        CThingPlayerCreature* localNetCreature = GetPlayerCreatureFromNetworkId(networkId);

        if (!localNetCreature)
            return;

        CTCHero* localNetHero = reinterpret_cast<CTCHero*>(
            reinterpret_cast<CThing*>(localNetCreature)->GetTC(TCI_HERO)
            );

        if (!localNetHero) {
            std::cout << "[NetPlayerManager::ReceiveNetPlayerHero]: !localNetHero" << std::endl;
            return;
        }

        if (heroFlags & WEAPONS_USABLE)
        {
            localNetHero->SetWeaponsAsUsable(weaponsUsable);
            localNetPlayer->SetWeaponsAsUsable(weaponsUsable);
        }

        if (heroFlags & WILL_USABLE)
        {
            localNetHero->SetWillAsUsable(willUsable);
            localNetPlayer->SetWillAsUsable(willUsable);
        }
    }

    for (auto& netPlayer : netPlayers)
    {
        if (heroFlags & WEAPONS_USABLE)
        {
            netHero->SetWeaponsAsUsable(weaponsUsable);
            netPlayer->SetWeaponsAsUsable(weaponsUsable);
        }

        if (heroFlags & WILL_USABLE)
        {
            netHero->SetWillAsUsable(willUsable);
            netPlayer->SetWillAsUsable(willUsable);
        }
    }
}

void NetPlayerManager::BroadcastLocalNetPlayerHero()
{
    CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerHero]: !creature" << std::endl;
        return;
    }

    CTCHero* hero = reinterpret_cast<CTCHero*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO)
        );

    if (!hero) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerHero]: !hero" << std::endl;
        return;
    }

    auto lastSendTime = std::chrono::steady_clock::now();

    hero->AddFrameUpdateCallback(
        "HeroFrameUpdate" + std::to_string(networkId),
        [this, lastSendTime]() mutable
        {
            CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

            if (!creature) {
                std::cout << "[NetPlayerManager::HeroFrameUpdate]: !creature" << std::endl;
                return;
            }

            CTCHero* hero = reinterpret_cast<CTCHero*>(
                reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO)
                );

            if (!hero) {
                std::cout << "[NetPlayerManager::HeroFrameUpdate]: !hero" << std::endl;
                return;
            }

            auto now = std::chrono::steady_clock::now();

            if (now - lastSendTime < std::chrono::milliseconds(200))
                return;

            lastSendTime = now;

            int heroFlags = 0;

            bool weaponsUsable = hero->WeaponsUsable;
            bool willUsable = hero->WillUsable;

            if (localNetPlayer->GetNetworkId() == 0)
            {
                if (weaponsUsable != localNetPlayer->GetWeaponsAsUsable())
                    heroFlags |= WEAPONS_USABLE;

                if (willUsable != localNetPlayer->GetWillAsUsable())
                    heroFlags |= WILL_USABLE;
            }

            if (heroFlags == 0)
                return;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_HERO);
            bs.Write(networkId);
            bs.Write(heroFlags);

            if (heroFlags & WEAPONS_USABLE)
            {
                bs.Write(weaponsUsable);
                localNetPlayer->SetWeaponsAsUsable(weaponsUsable);
                SetNetPlayersWeaponsAsUsable(weaponsUsable);
            }

            if (heroFlags & WILL_USABLE)
            {
                bs.Write(willUsable);
                localNetPlayer->SetWillAsUsable(willUsable);
                SetNetPlayersWillAsUsable(willUsable);
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

void NetPlayerManager::BroadcastNetPlayerHero(int networkId)
{
    CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerHero]: !creature" << std::endl;
        return;
    }

    CTCHero* hero = reinterpret_cast<CTCHero*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO)
        );

    if (!hero) {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerHero]: !hero" << std::endl;
        return;
    }

    int heroFlags = 0;
    bool weaponsUsable = hero->WeaponsUsable;
    bool willUsable = hero->WillUsable;

    if (localNetPlayer->GetNetworkId() == 0)
    {
        heroFlags |= WEAPONS_USABLE;
        heroFlags |= WILL_USABLE;
    }

    if (heroFlags == 0)
        return;

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_PLAYER_HERO);
    bs.Write(networkId);
    bs.Write(heroFlags);

    if (heroFlags & WEAPONS_USABLE)
    {
        bs.Write(weaponsUsable);
        SetNetPlayersWeaponsAsUsable(weaponsUsable);
    }

    if (heroFlags & WILL_USABLE)
    {
        bs.Write(willUsable);
        SetNetPlayersWillAsUsable(willUsable);
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
