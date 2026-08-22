#pragma once

#include <sstream>
#include <unordered_map>
#include <chrono>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

#include "../LocalNetPlayer/LocalNetPlayer.h"
#include "../NetPlayer/NetPlayer.h"
#include "../NetCreatureAction/NetCreatureAction.h"

class NetPlayerManager
{
public:
    NetPlayerManager(Network* network, CPlayerManager* playerManager, CWorld* world);
    ~NetPlayerManager();

    void ConnectionNotification(int networkId, SystemAddress systemAddress);

    void CreateLocalNetPlayer(int networkId, C3DVector position);
    void CreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void CreateNetPlayers(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);

    void ReceiveNetPlayerMovement(int networkId, C3DVector remotePosition, C3DVector movementAcceleration);
    void ReceiveNetPlayerRotation(int networkId, C3DVector up, C3DVector forward);
    void ReceiveNetPlayerAction(int networkId, uintptr_t actionOffset, SLNet::BitStream& bs);
    void ReceiveNetPlayerStats(int networkId, SLNet::BitStream& bs);

    void DestroyLocalNetPlayer();
    void DestroyNetPlayer(int networkId);
    void DestroyNetPlayers();

private:
    Network* network;

    CPlayerManager* playerManager;
    CWorld* world;

    std::unique_ptr<LocalNetPlayer> localNetPlayer;
    std::vector<std::unique_ptr<NetPlayer>> netPlayers;

    void TeleportClientToHostOnConnect(int networkId, C3DVector position);

    void ApplyNetPlayerMovement(int networkId);
    void ApplyNetPlayerRotation(int networkId);

    void BroadcastCreateLocalNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void BroadcastCreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void BroadcastCreateNetPlayers(int networkId);

    void BroadcastLocalNetPlayerMovement(int networkId);
    void BroadcastLocalNetPlayerRotation(int networkId);
    void BroadcastLocalNetPlayerAction(int networkId);
    void BroadcastLocalNetPlayerStats(int networkId);
    void BroadcastAllLocalNetPlayerStats(int networkId, int targetNetworkId = -1);

    void BroadcastDestroyNetPlayer(int networkId);

    CThingPlayerCreature* GetCreatureFromNetworkId(int networkId) const;
    CThingPlayerCreature* GetCreatureFromLocalId(int localId) const;

    int GetFreeLocalId();
    int GetLocalIdFromNetworkId(int networkId) const;
    int GetNetworkIdFromLocalId(int localId) const;
};
