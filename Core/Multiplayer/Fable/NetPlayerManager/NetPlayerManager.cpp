#include "NetPlayerManager.h"

NetPlayerManager::NetPlayerManager(
    Network* network,
    CMainGameComponent* mainGameComponent
)
    : network(network),
    mainGameComponent(mainGameComponent)
{
}

NetPlayerManager::~NetPlayerManager()
{
	network = nullptr;
}
