#include "NetWorld.h"

NetWorld::NetWorld(
    Network* network,
    CMainGameComponent* mainGameComponent
)
    : network(network),
    mainGameComponent(mainGameComponent)
{
    RegionLoadStartPos = C3DVector();
    RegionLoadStartAngleXY = 0.0f;


}

NetWorld::~NetWorld()
{
    network = nullptr;
}
