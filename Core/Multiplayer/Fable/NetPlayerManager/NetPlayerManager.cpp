#include "NetPlayerManager.h"

NetPlayerManager::NetPlayerManager(
    Network* network,
    CPlayerManager* playerManager,
    CWorld* world
)
    : network(network),
    playerManager(playerManager),
    world(world)
{
}

NetPlayerManager::~NetPlayerManager()
{
	network = nullptr;
}
