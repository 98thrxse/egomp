#pragma once

#include <sstream>
#include <unordered_map>
#include <chrono>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

#include "../LocalNetPlayer/LocalNetPlayer.h"
#include "../NetPlayer/NetPlayer.h"

class NetPlayerManager
{
public:
    NetPlayerManager(Network* network, CMainGameComponent* mainGameComponent);
    ~NetPlayerManager();

    void SetNetworkId(int id);
    int GetNetworkId() const;

    void CreateLocalNetPlayer(C3DVector position, float facingAngleXY);
	void SetupLocalNetPlayer(int networkId, CThingPlayerCreature* creature, C3DVector position, float facingAngleXY);

    void CreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void CreateNetPlayers(BitStream& bs);
    void SetupNetPlayer();
    void SetupNetPlayers(int networkId);

    void ReceiveNetPlayerMovement(int networkId, C3DVector remotePosition, C3DVector movementAcceleration);
    void ReceiveNetPlayerRotation(int networkId, C3DVector up, C3DVector forward);
    void ReceiveNetPlayerAction(SLNet::BitStream& bs);
    void ReceiveNetPlayerStats(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerAppearance(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerExperience(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerMorph(int networkId, SLNet::BitStream& bs);
    void ReceiveNetPlayerWeapons(int networkId, long weapon_def_index);

    void DestroyLocalNetPlayer();
    void DestroyNetPlayer(int networkId);
    void DestroyNetPlayers();

    void SetNetPlayerInLimbo(int networkId, bool on);
    void SetNetPlayersInLimbo(bool on);

    void SetNetPlayerAlpha(int networkId, unsigned __int8 alpha);
    void SetNetPlayersAlpha(unsigned __int8 alpha);

    void SetNetPlayersPosition(C3DVector position);
	void SetNetPlayerParticle(int networkId, long particleTypeId, C3DVector position, bool force);

private:
    Network* network;

    int networkId;

    CMainGameComponent* mainGameComponent;
    CPlayerManager* playerManager = mainGameComponent->GetPlayerManager();
    CWorld* world = mainGameComponent->GetWorld();

    CDefinitionManager* definitionManager = CDefinitionManager::Get();
    CDefStringTable* defStringTable = CDefStringTable::Get();

    CDisplayEngine* displayEngine = mainGameComponent->GetDisplayEngine();
    CIEngine* iengine = displayEngine->Get3DEngine();

    std::unique_ptr<LocalNetPlayer> localNetPlayer;
    std::vector<std::unique_ptr<NetPlayer>> netPlayers;

    void ApplyNetPlayerMovement(int networkId);
    void ApplyNetPlayerRotation(int networkId);

    void RefreshNetPlayerMorph(int networkId);

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

    void BroadcastLocalNetPlayerWeapons(int networkId);
    void BroadcastNetPlayerWeapons(int networkId);

    void BroadcastDestroyNetPlayer(int networkId);

    CThingPlayerCreature* GetPlayerCreatureFromNetworkId(int networkId) const;
    CThingPlayerCreature* GetPlayerCreatureFromLocalId(int localId) const;

    int GetDefGlobalIndexFromName(CThing* thing) const;

    int GetFreeLocalId();
    int GetLocalIdFromNetworkId(int networkId) const;
    int GetNetworkIdFromLocalId(int localId) const;
    int GetNetworkIdFromThing(CThing* thing) const;
};
