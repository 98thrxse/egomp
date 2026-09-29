#pragma once

#include <sstream>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

class NetWorld
{
public:
    NetWorld(Network* network, CMainGameComponent* mainGameComponent);
    ~NetWorld();

    void ConnectionNotification(int networkId, SystemAddress systemAddress);
    void SyncWorld(BitStream& bs);

private:
    Network* network;

    CMainGameComponent* mainGameComponent;
    CWorld* world = mainGameComponent->GetWorld();
};
