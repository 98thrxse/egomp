#include "NetWorld.h"

void NetWorld::CreateNetWorld()
{
	if (networkId == 0)
		BroadcastNetWorldTime();
}

void NetWorld::SaveTeleportingAsActive(bool savedActive)
{
	teleportingAsActive = savedActive;
}

void NetWorld::LoadTeleportingAsActive()
{
	gameScriptInterface->SetTeleportingAsActive(teleportingAsActive);
}

void NetWorld::SaveAsLoadingRegion(C3DVector savedPosition, float savedFacingAngleXY)
{
	position = savedPosition;
	facingAngleXY = savedFacingAngleXY;
}

void NetWorld::LoadAsLoadingRegion()
{
	world->SetAsLoadingRegion(position, facingAngleXY, true, true, false);
}

void NetWorld::DestroyNetWorld()
{
	gameTimeManager->RemoveUpdateCallback("TimeUpdate");
}
