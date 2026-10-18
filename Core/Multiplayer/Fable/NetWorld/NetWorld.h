#pragma once

#include <sstream>
#include <chrono>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

class NetWorld
{
public:
    NetWorld(Network* network, CMainGameComponent* mainGameComponent);
    ~NetWorld();

    void SetNetworkId(int id);
    int GetNetworkId() const;

    void CreateNetWorld();
    void DestroyNetWorld();

    void SaveTeleportingAsActive(bool);
    void LoadTeleportingAsActive();

    void SaveAsLoadingRegion(C3DVector, float);
    void LoadAsLoadingRegion();

    void BroadcastNetLoadRegion(
        C3DVector const& position,
        float facingAngleXY,
        bool teleporter,
        bool duringCutScenes,
        bool door);

    void BroadcastNetLoadedRegion();
    void ReceiveNetLoadedRegion(int netPlayerNetworkId);

	void BroadcastNetWorldTime();
	void ReceiveNetWorldTime(BitStream& bs);

private:
    Network* network;

    CMainGameComponent* mainGameComponent;

    CWorld* world = mainGameComponent->GetWorld();
    CGameScriptInterface* gameScriptInterface = world->GetGameScriptInterface();
    CGameTimeManager* gameTimeManager = world->GetGameTimeManager();

    int networkId;
    C3DVector position;
    float facingAngleXY;
    bool teleportingAsActive;
};
