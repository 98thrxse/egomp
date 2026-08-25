#include "NetPlayerManager.h"

void NetPlayerManager::CreateLocalNetPlayer(int networkId, C3DVector position)
{
    int localId = GetFreeLocalId();
    CThingPlayerCreature* creature = GetCreatureFromLocalId(localId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::CreateLocalNetPlayer]: !creature" << std::endl;
        return;
    }

    if (!localNetPlayer)
        localNetPlayer = std::make_unique<LocalNetPlayer>();

    localNetPlayer->SetLocalId(localId);
    localNetPlayer->SetNetworkId(networkId);

    if (networkId != 0)
        TeleportClientToHostOnConnect(networkId, position);

    BroadcastLocalNetPlayerMovement(networkId);
    BroadcastLocalNetPlayerRotation(networkId);
    BroadcastLocalNetPlayerAction(networkId);
    BroadcastLocalNetPlayerStats(networkId);
    BroadcastLocalNetPlayerAppearance(networkId);
}

void NetPlayerManager::CreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY)
{
    int localId = GetFreeLocalId();
    playerManager->CreatePlayer(localId);
    CPlayer* player = playerManager->GetPlayer(localId);

    if (!player)
    {
        std::cout << "[NetPlayerManager::CreateNetPlayer]: !player: " << networkId << std::endl;
        return;
    }

    std::unique_ptr<NetPlayer> netPlayer = std::make_unique<NetPlayer>();
    netPlayer->SetNetworkId(networkId);
    netPlayer->SetLocalId(localId);
    netPlayers.push_back(std::move(netPlayer));

    CThingPlayerCreatureInit init = {};
    CThingPlayerCreature* creature = CThingPlayerCreature::Create(defGlobalIndex, position, localId, init);
    
    CTCPhysicsBase* physicsTC = reinterpret_cast<CThing*>(creature)->PhysicsTC;
    reinterpret_cast<CTCPhysicsStandard*>(physicsTC)->SetFacingAngleXY(facingAngleXY);

    player->SetControlledCreature(creature);

    ApplyNetPlayerMovement(networkId);
    ApplyNetPlayerRotation(networkId);

    if (localNetPlayer->GetNetworkId() == 0)
    {
        BroadcastCreateNetPlayer(networkId, defGlobalIndex, position, facingAngleXY);
        BroadcastCreateNetPlayers(networkId);

        BroadcastLocalNetPlayerAllStats(localNetPlayer->GetNetworkId());
        BroadcastLocalNetPlayerAllAppearance(localNetPlayer->GetNetworkId());

        for (auto& netPlayer : netPlayers)
        {
            if (netPlayer->GetNetworkId() == networkId)
                continue;

            BroadcastLocalNetPlayerAllStats(netPlayer->GetNetworkId());
            BroadcastLocalNetPlayerAllAppearance(netPlayer->GetNetworkId());
        }
    }
}

void NetPlayerManager::CreateNetPlayers(BitStream& bs)
{
    int count = 0;
    bs.Read(count);

    for (int i = 0; i < count; i++)
    {
        int networkId = -1;
        int defGlobalIndex = 0;
        C3DVector position = {};
        float facingAngleXY = 0;

        bs.Read(networkId);
        bs.Read(defGlobalIndex);
        bs.Read(position);
        bs.Read(facingAngleXY);

        if (networkId != localNetPlayer->GetNetworkId() && GetLocalIdFromNetworkId(networkId) == -1)
            CreateNetPlayer(networkId, defGlobalIndex, position, facingAngleXY);
    }

    BroadcastLocalNetPlayerAllStats(localNetPlayer->GetNetworkId());
    BroadcastLocalNetPlayerAllAppearance(localNetPlayer->GetNetworkId());
}

void NetPlayerManager::DestroyLocalNetPlayer()
{
    if (!localNetPlayer)
        return;

    int networkId = localNetPlayer->GetNetworkId();
    int localId = GetLocalIdFromNetworkId(networkId);
    CPlayer* localPlayer = playerManager->GetPlayer(localId);

    if (!localPlayer)
    {
        std::cout << "[NetPlayerManager::DestroyLocalNetPlayer]: !localPlayer" << std::endl;
        return;
    }

    CThingPlayerCreature* creature = localPlayer->GetPControlledCreature();

    if (!creature)
    {
        std::cout << "[NetPlayerManager::DestroyLocalNetPlayer]: !creature" << std::endl;
        return;
    }

    CTCHeroStats* heroStats = reinterpret_cast<CTCHeroStats*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_STATS));

    if (!heroStats) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !heroStats" << std::endl;
        return;
    }

    CTCHeroAttachableAppearanceModifiers* appearanceModifiers = reinterpret_cast<CTCHeroAttachableAppearanceModifiers*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_ATTACHABLE_APPEARANCE_MODIFIERS));

    if (!appearanceModifiers) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !appearanceModifiers" << std::endl;
        return;
    }

    creature->RemoveResolveMovementAccelerationCallback("ResolveMovementAcceleration" + std::to_string(networkId));
    creature->RemoveResolveFacingDirectionCallback("ResolveFacingDirection" + std::to_string(networkId));
    reinterpret_cast<CThingCreatureBase*>(creature)->RemoveSetCurrentActionCallback("SetCurrentAction" + std::to_string(networkId));
    heroStats->RemoveFrameUpdateCallback("StatsFrameUpdate" + std::to_string(networkId));
    appearanceModifiers->RemoveFrameUpdateCallback("AppearanceFrameUpdate" + std::to_string(networkId));

    localNetPlayer.reset();
}

void NetPlayerManager::DestroyNetPlayer(int networkId)
{
    int localId = GetLocalIdFromNetworkId(networkId);
    CPlayer* player = playerManager->GetPlayer(localId);

    if (!player)
    {
        std::cout << "[NetPlayerManager::DestroyNetPlayer]: !player: " << networkId << std::endl;
        return;
    }

    CThingPlayerCreature* creature = player->GetPControlledCreature();

    if (!creature)
    {
        std::cout << "[NetPlayerManager::DestroyNetPlayer]: !creature: " << networkId << std::endl;
        return;
    }
  
    CTCHeroStats* heroStats = reinterpret_cast<CTCHeroStats*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_STATS));

    if (!heroStats) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !heroStats" << std::endl;
        return;
    }

    CTCHeroAttachableAppearanceModifiers* appearanceModifiers = reinterpret_cast<CTCHeroAttachableAppearanceModifiers*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_HERO_ATTACHABLE_APPEARANCE_MODIFIERS));

    if (!appearanceModifiers) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerStats]: !appearanceModifiers" << std::endl;
        return;
    }

    creature->RemoveResolveMovementAccelerationCallback("ResolveMovementAcceleration" + std::to_string(networkId));
    creature->RemoveResolveFacingDirectionCallback("ResolveFacingDirection" + std::to_string(networkId));
    reinterpret_cast<CThingCreatureBase*>(creature)->RemoveSetCurrentActionCallback("SetCurrentAction" + std::to_string(networkId));
    heroStats->RemoveFrameUpdateCallback("StatsFrameUpdate" + std::to_string(networkId));
    appearanceModifiers->RemoveFrameUpdateCallback("AppearanceFrameUpdate" + std::to_string(networkId));

    player->UninitCharacter();
    player->Uninitialise();

    for (size_t i = 0; i < netPlayers.size(); ++i)
    {
        if (netPlayers[i] && netPlayers[i]->GetNetworkId() == networkId)
        {
            netPlayers.erase(netPlayers.begin() + i);
            break;
        }
    }

    if (localNetPlayer->GetNetworkId() == 0)
        BroadcastDestroyNetPlayer(networkId);
}

void NetPlayerManager::DestroyNetPlayers()
{
    while (!netPlayers.empty())
    {
        int networkId = netPlayers.front()->GetNetworkId();
        DestroyNetPlayer(networkId);
    }
}

void NetPlayerManager::TeleportClientToHostOnConnect(int networkId, C3DVector position)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::TeleportClientToHostOnConnect]: !creature" << std::endl;
        return;
    }

    CDefString def;
    CCharString defName("");

    reinterpret_cast<CThing*>(creature)->GetDefName(&def);
    CDefStringTable::Get()->GetString(&defName, def.TablePos);

    CDefinitionManager* definitionManager = CDefinitionManager::Get();
    int defGlobalIndex = definitionManager->GetDefGlobalIndexFromName(&defName);

    CTCPhysicsBase* physicsTC = reinterpret_cast<CThing*>(creature)->PhysicsTC;
    float facingAngleXY = reinterpret_cast<CTCPhysicsStandard*>(physicsTC)->GetFacingAngleXY();

    world->AddUpdateRegionLoadCallback("TeleportClientToHostOnConnect", [this, networkId, defGlobalIndex, position, facingAngleXY]() {
        if (world->RegionLoadStatus != CWorld::NOT_LOADING_REGION)
            return;

        world->RemoveUpdateRegionLoadCallback("TeleportClientToHostOnConnect");
        BroadcastCreateLocalNetPlayer(networkId, defGlobalIndex, position, facingAngleXY);
        });

    world->SetAsLoadingRegion(position, facingAngleXY, false, false, false);
}

void NetPlayerManager::BroadcastCreateLocalNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY)
{
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_CREATE_NET_PLAYER);
        bsOut.Write(networkId);
        bsOut.Write(defGlobalIndex);
        bsOut.Write(position);
        bsOut.Write(facingAngleXY);

        network->SendToHost((const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed());
}

void NetPlayerManager::BroadcastCreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY)
{
    SLNet::BitStream bsOut;
    bsOut.Write((SLNet::MessageID)ID_CREATE_NET_PLAYER);
    bsOut.Write(networkId);
    bsOut.Write(defGlobalIndex);
    bsOut.Write(position);
	bsOut.Write(facingAngleXY);

    network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed());
}

void NetPlayerManager::BroadcastCreateNetPlayers(int networkId)
{
    SLNet::BitStream bsOut;
    bsOut.Write((SLNet::MessageID)ID_CREATE_NET_PLAYERS);

    int count = (int)netPlayers.size() + (localNetPlayer ? 1 : 0);
    bsOut.Write(count);

    CDefinitionManager* definitionManager = CDefinitionManager::Get();

    if (localNetPlayer)
    {
        int localNetPlayerNetworkId = localNetPlayer->GetNetworkId();
        CThingPlayerCreature* creature = GetCreatureFromNetworkId(localNetPlayerNetworkId);

        if (!creature)
        {
            std::cout << "[NetPlayerManager::BroadcastCreateNetPlayers]: !creature" << std::endl;
            return;
        }

        CDefString def;
        CCharString defName("");

        reinterpret_cast<CThing*>(creature)->GetDefName(&def);
        CDefStringTable::Get()->GetString(&defName, def.TablePos);

        int defGlobalIndex = definitionManager->GetDefGlobalIndexFromName(&defName);

        C3DVector position = *(reinterpret_cast<CThing*>(creature))->GetPos();

        CTCPhysicsBase* physicsTC = reinterpret_cast<CThing*>(creature)->PhysicsTC;
        float facingAngleXY = reinterpret_cast<CTCPhysicsStandard*>(physicsTC)->GetFacingAngleXY();

        bsOut.Write(localNetPlayerNetworkId);
        bsOut.Write(defGlobalIndex);
        bsOut.Write(position);
		bsOut.Write(facingAngleXY);
    }

    for (const auto& netPlayer : netPlayers)
    {
        int netPlayerNetworkId = netPlayer->GetNetworkId();
        CThingPlayerCreature* creature = GetCreatureFromNetworkId(netPlayerNetworkId);

        if (!creature)
        {
            std::cout << "[NetPlayerManager::BroadcastCreateNetPlayers]: !creature" << std::endl;
            continue;
        }

        CDefString def;
        CCharString defName("");

        reinterpret_cast<CThing*>(creature)->GetDefName(&def);
        CDefStringTable::Get()->GetString(&defName, def.TablePos);

        int defGlobalIndex = definitionManager->GetDefGlobalIndexFromName(&defName);

        C3DVector position = *(reinterpret_cast<CThing*>(creature))->GetPos();

        CTCPhysicsBase* physicsTC = reinterpret_cast<CThing*>(creature)->PhysicsTC;
        float facingAngleXY = reinterpret_cast<CTCPhysicsStandard*>(physicsTC)->GetFacingAngleXY();

        bsOut.Write(netPlayerNetworkId);
        bsOut.Write(defGlobalIndex);
        bsOut.Write(position);
		bsOut.Write(facingAngleXY);
    }

    network->SendToClient(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed());
}

void NetPlayerManager::BroadcastDestroyNetPlayer(int networkId)
{
    SLNet::BitStream bsOut;
    bsOut.Write((SLNet::MessageID)ID_DESTROY_NET_PLAYER);
    bsOut.Write(networkId);

    network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed());
}
