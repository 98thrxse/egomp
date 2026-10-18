#include "NetWorld.h"

NetWorld::NetWorld(
    Network* network,
    CMainGameComponent* mainGameComponent
)
    : network(network),
    mainGameComponent(mainGameComponent)
{
    C3DVector position = {};
    float facingAngleXY = 0;
    bool teleportingAsActive = false;
}

NetWorld::~NetWorld()
{
    network = nullptr;
}
