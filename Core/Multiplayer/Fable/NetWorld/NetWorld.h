#pragma once

#include <sstream>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

class NetWorld
{
public:
    C3DVector RegionLoadStartPos;
    float RegionLoadStartAngleXY;

    NetWorld(Network* network, CMainGameComponent* mainGameComponent);
    ~NetWorld();

    void ConnectionNotification(int networkId, SystemAddress systemAddress);

private:
    Network* network;

    CMainGameComponent* mainGameComponent;
    CWorld* world = mainGameComponent->GetWorld();
};
