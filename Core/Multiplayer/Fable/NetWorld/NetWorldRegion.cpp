#include "NetWorld.h"

void NetWorld::BroadcastLoadRegion(C3DVector const& position, float facingAngleXY, bool teleporter, bool duringCutScenes, bool door)
{
    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_WORLD_LOAD_REGION);
    bs.Write(position);
    bs.Write(facingAngleXY);
    bs.Write(teleporter);
    bs.Write(duringCutScenes);
    bs.Write(door);

    network->SendToAllClients((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
}
