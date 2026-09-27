#include "NetPlayerManager.h"

CThingPlayerCreature* NetPlayerManager::GetPlayerCreatureFromNetworkId(int networkId) const
{
    int localId = GetLocalIdFromNetworkId(networkId);
    CPlayer* player = playerManager->GetPlayer(localId);

    if (!player)
    {
        std::cout << "[NetPlayerManager::GetPlayerCreatureFromNetworkId]: !player: " << networkId << std::endl;
        return nullptr;
    }

    return player->GetPControlledCreature();
}

CThingPlayerCreature* NetPlayerManager::GetPlayerCreatureFromLocalId(int localId) const
{
    CPlayer* player = playerManager->GetPlayer(localId);

    if (!player)
    {
        std::cout << "[NetPlayerManager::GetPlayerCreatureFromLocalId]: !player: " << localId << std::endl;
        return nullptr;
    }

    return player->GetPControlledCreature();
}

int NetPlayerManager::GetFreeLocalId()
{
    for (int localId = 0;; ++localId)
    {
        bool used = false;

        if (localNetPlayer && localNetPlayer->GetLocalId() == localId)
            used = true;

        for (const auto& p : netPlayers)
        {
            if (p && p->GetLocalId() == localId)
            {
                used = true;
                break;
            }
        }

        if (!used)
            return localId;
    }
}

int NetPlayerManager::GetLocalIdFromNetworkId(int networkId) const
{
    if (localNetPlayer && localNetPlayer->GetNetworkId() == networkId)
        return localNetPlayer->GetLocalId();

    for (const auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetNetworkId() == networkId)
            return netPlayer->GetLocalId();
    }

    return -1;
}

int NetPlayerManager::GetNetworkIdFromLocalId(int localId) const
{
    if (localNetPlayer && localNetPlayer->GetLocalId() == localId)
        return localNetPlayer->GetNetworkId();

    for (const auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetLocalId() == localId)
            return netPlayer->GetNetworkId();
    }

    return -1;
}
