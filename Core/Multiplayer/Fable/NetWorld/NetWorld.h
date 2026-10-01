#pragma once

#include <sstream>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

class NetWorld
{
public:
    NetWorld(Network* network, CMainGameComponent* mainGameComponent);
    ~NetWorld();

    void LoadRegion(C3DVector const& position,
        float facingAngleXY,
        bool teleporter,
        bool duringCutScenes,
        bool door);

private:
    Network* network;

    CMainGameComponent* mainGameComponent;
    CWorld* world = mainGameComponent->GetWorld();
};
