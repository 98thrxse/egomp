#include "NetWorld.h"

void NetWorld::CreateNetWorld()
{
	int networkId = GetNetworkId();

	if (networkId == 0)
	{
		BroadcastNetWorldTime();
	}
}

void NetWorld::DestroyNetWorld()
{
	gameTimeManager->RemoveUpdateCallback("TimeUpdate");
}
