#include "NetWorld.h"

void NetWorld::LoadRegion(C3DVector const& position, float facingAngleXY, bool teleporter, bool duringCutScenes, bool door)
{
    world->SetAsLoadingRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
}
