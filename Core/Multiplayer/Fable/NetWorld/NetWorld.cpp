#include "NetWorld.h"

NetWorld::NetWorld(
    Network* network,
    CMainGameComponent* mainGameComponent
)
    : network(network),
    mainGameComponent(mainGameComponent)
{
}

NetWorld::~NetWorld()
{
    network = nullptr;
}
