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

int NetPlayerManager::GetDefGlobalIndexFromName(CThing* thing) const
{
    CDefString def;
    CCharString defName("");

    thing->GetDefName(&def);
    defStringTable->GetString(&defName, def.TablePos);

    return definitionManager->GetDefGlobalIndexFromName(&defName);
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

void NetPlayerManager::SetNetPlayerParticle(int networkId, long particleTypeId, C3DVector position, bool force)
{
    CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::SetNetPlayerParticle]: !creature: " << networkId << std::endl;
        return;
    }

    if (position.X == 0 && position.Y == 0 && position.Z == 0)
        position = *reinterpret_cast<CThing*>(creature)->GetPos();

    CThing* particle = CTCDParticleEmitter::Create(particleTypeId, position, force);
    CTCHero* hero = reinterpret_cast<CTCHero*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO));

    if (!hero)
    {
        std::cout << "[NetPlayerManager::SetNetPlayerParticle]: !hero" << std::endl;
        return;
    }

    hero->SetTeleportParticle(*particle);
}

void NetPlayerManager::SetNetPlayersInLimbo(bool on)
{
    for (const auto& netPlayer : netPlayers)
    {
		CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(netPlayer->GetNetworkId());

        if (!creature)
        {
            std::cout << "[NetPlayerManager::SetNetPlayersInLimbo]: !creature: " << netPlayer->GetNetworkId() << std::endl;
            continue;
        }

		reinterpret_cast<CThing*>(creature)->SetInLimbo(on);
    }
}

void NetPlayerManager::SetNetPlayersPosition(C3DVector position)
{
    for (const auto& netPlayer : netPlayers)
    {
        CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(netPlayer->GetNetworkId());

        if (!creature)
        {
            std::cout << "[NetPlayerManager::SetNetPlayersPosition]: !creature: " << netPlayer->GetNetworkId() << std::endl;
            continue;
        }

        *reinterpret_cast<CThing*>(creature)->GetPos() = position;
    }
}
