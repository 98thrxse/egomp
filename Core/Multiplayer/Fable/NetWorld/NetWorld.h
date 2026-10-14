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

    void BroadcastNetLoadRegion(
        C3DVector const& position,
        float facingAngleXY,
        bool teleporter,
        bool duringCutScenes,
        bool door);

    void BroadcastNetLoadedRegion();
    void ReceiveNetLoadedRegion(int netPlayerNetworkId);

	void BroadcastNetWorldTime();
	void ReceiveNetWorldTime(float time);

private:
    Network* network;

    CMainGameComponent* mainGameComponent;
    CWorld* world = mainGameComponent->GetWorld();
    CGameTimeManager* gameTimeManager = world->GetGameTimeManager();

    int networkId;
};
