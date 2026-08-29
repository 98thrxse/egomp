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
    NetPlayerManager(Network* network, CMainGameComponent* mainGameComponent);
    ~NetPlayerManager();

    void ConnectionNotification(int networkId, SystemAddress systemAddress);

    void CreateLocalNetPlayer(int networkId, C3DVector position);
    void CreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void CreateNetPlayers(BitStream& bs);

    void ReceiveNetPlayerMovement(int networkId, C3DVector remotePosition, C3DVector movementAcceleration);
    void ReceiveNetPlayerRotation(int networkId, C3DVector up, C3DVector forward);
    void ReceiveNetPlayerAction(int networkId, uintptr_t actionOffset, SLNet::BitStream& bs);
    void ReceiveNetPlayerStats(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerAppearance(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerExperience(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerMorph(int networkId, SLNet::BitStream& bs);

    void DestroyLocalNetPlayer();
    void DestroyNetPlayer(int networkId);
    void DestroyNetPlayers();

private:
    Network* network;

    CMainGameComponent* mainGameComponent;
    CPlayerManager* playerManager = mainGameComponent->GetPlayerManager();
    CWorld* world = mainGameComponent->GetWorld();
    CDisplayEngine* displayEngine = mainGameComponent->GetDisplayEngine();

    CIEngine* iengine = displayEngine->Get3DEngine();

    std::unique_ptr<LocalNetPlayer> localNetPlayer;
    std::vector<std::unique_ptr<NetPlayer>> netPlayers;

    void TeleportClientToHostOnConnect(int networkId, C3DVector position);

    void ApplyNetPlayerMovement(int networkId);
    void ApplyNetPlayerRotation(int networkId);

    void RefreshNetPlayerMorph(CTCHeroMorph* heroMorph, int networkId);

    void BroadcastCreateLocalNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void BroadcastCreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void BroadcastCreateNetPlayers(int networkId);

    void BroadcastLocalNetPlayerMovement(int networkId);
    void BroadcastLocalNetPlayerRotation(int networkId);
    void BroadcastLocalNetPlayerAction(int networkId);

    void BroadcastLocalNetPlayerStats(int networkId);
    void BroadcastNetPlayerStats(int networkId);

    void BroadcastLocalNetPlayerAppearance(int networkId);
    void BroadcastNetPlayerAppearance(int networkId);

    void BroadcastLocalNetPlayerExperience(int networkId);
    void BroadcastNetPlayerExperience(int networkId);

    void BroadcastLocalNetPlayerMorph(int networkId);
    void BroadcastNetPlayerMorph(int networkId);

    void BroadcastDestroyNetPlayer(int networkId);

    CThingPlayerCreature* GetCreatureFromNetworkId(int networkId) const;
    CThingPlayerCreature* GetCreatureFromLocalId(int localId) const;

    int GetFreeLocalId();
    int GetLocalIdFromNetworkId(int networkId) const;
    int GetNetworkIdFromLocalId(int localId) const;
};
