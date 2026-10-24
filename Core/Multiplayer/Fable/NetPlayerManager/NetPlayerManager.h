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
	void SetupLocalNetPlayer(CThingPlayerCreature* creature, C3DVector position, float facingAngleXY);

    void CreateNetPlayer(int networkId, int defGlobalIndex, C3DVector position, float facingAngleXY);
    void CreateNetPlayers(BitStream& bs);
    void SetupNetPlayer();
    void SetupNetPlayers(int networkId);

    void ReceiveNetPlayerMovement(SLNet::BitStream& bs);
    void ReceiveNetPlayerRotation(SLNet::BitStream& bs);
    void ReceiveNetPlayerAction(SLNet::BitStream& bs);
    void ReceiveNetPlayerStats(SLNet::BitStream& bs);
    void ReceiveNetPlayerAppearance(SLNet::BitStream& bs);
    void ReceiveNetPlayerExperience(SLNet::BitStream& bs);
    void ReceiveNetPlayerMorph(SLNet::BitStream& bs);
    void ReceiveNetPlayerWeapons(SLNet::BitStream& bs);
    void ReceiveNetPlayerHero(SLNet::BitStream& bs);

    void DestroyLocalNetPlayer();
    void DestroyNetPlayer(int networkId);
    void DestroyNetPlayers();

    void SetNetPlayerInLimbo(int networkId, bool on);
    void SetNetPlayersInLimbo(bool on);

    void SetNetPlayerAlpha(int networkId, unsigned __int8 alpha);
    void SetNetPlayersAlpha(unsigned __int8 alpha);

    void SetNetPlayerParticle(int networkId, long particleTypeId, C3DVector position, bool force);

    void SetNetPlayersPosition(C3DVector position);
    void SetNetPlayersWeaponsAsUsable(bool on);
    void SetNetPlayersWillAsUsable(bool on);

    C3DVector GetPlayerPosition();
    float GetPlayerFacingAngleXY();

    void RefreshNetPlayerSheathedWeapons(int networkId);
    void RefreshNetPlayersSheathedWeapons();

private:
    Network* network;

    int networkId;

    CMainGameComponent* mainGameComponent;
    CPlayerManager* playerManager = mainGameComponent->GetPlayerManager();

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

    void BroadcastLocalNetPlayerAction();

    void BroadcastLocalNetPlayerMovement();
    void BroadcastNetPlayerMovement(int networkId);

    void BroadcastLocalNetPlayerRotation();
    void BroadcastNetPlayerRotation(int networkId);

    void BroadcastLocalNetPlayerStats();
    void BroadcastNetPlayerStats(int networkId);

    void BroadcastLocalNetPlayerAppearance();
    void BroadcastNetPlayerAppearance(int networkId);

    void BroadcastLocalNetPlayerExperience();
    void BroadcastNetPlayerExperience(int networkId);

    void BroadcastLocalNetPlayerMorph();
    void BroadcastNetPlayerMorph(int networkId);

    void BroadcastLocalNetPlayerWeapons();
    void BroadcastNetPlayerWeapons(int networkId);

    void BroadcastLocalNetPlayerHero();
    void BroadcastNetPlayerHero(int networkId);

    void BroadcastDestroyNetPlayer(int networkId);

    CThingPlayerCreature* GetPlayerCreatureFromNetworkId(int networkId) const;
    CThingPlayerCreature* GetPlayerCreatureFromLocalId(int localId) const;

    int GetDefGlobalIndexFromThing(CThing* thing) const;

    int GetFreeLocalId();
    int GetLocalIdFromNetworkId(int networkId) const;
    int GetNetworkIdFromLocalId(int localId) const;
    int GetNetworkIdFromThing(CThing* thing) const;
};
