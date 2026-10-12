#pragma once

#include <sstream>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

class NetWorld
{
public:
    NetWorld(Network* network, CMainGameComponent* mainGameComponent);
    ~NetWorld();

    void SetNetworkId(int id);
    int GetNetworkId() const;

    void BroadcastLoadRegion(
        C3DVector const& position,
        float facingAngleXY,
        bool teleporter,
        bool duringCutScenes,
        bool door);

    void BroadcastLoadedRegion();
    void ReceiveLoadedRegion(int netPlayerNetworkId);

private:
    Network* network;

    CMainGameComponent* mainGameComponent;
    CWorld* world = mainGameComponent->GetWorld();

    int networkId;
};
