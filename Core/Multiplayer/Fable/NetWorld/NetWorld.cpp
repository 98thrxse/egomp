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

void NetWorld::SyncWorld(BitStream& bs)
{
    int networkId = -1;
    C3DVector position = {};
    float facingAngleXY = 0;

    bs.Read(networkId);
    bs.Read(position);
    bs.Read(facingAngleXY);

    // TODO: check if map is not the same
    world->SetAsLoadingRegion(position, facingAngleXY, false, false, false);
}
