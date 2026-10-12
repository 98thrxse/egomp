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

    network->SendToAllClients((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_SEQUENCED);
}

void NetWorld::BroadcastLoadedRegion()
{
    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_WORLD_LOADED_REGION);
    bs.Write(networkId);

    if (networkId == 0) {
        network->SendToAllClients((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
    }
    else {
        network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
    }
}

void NetWorld::ReceiveLoadedRegion(int netPlayerNetworkId)
{
    if (networkId == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_WORLD_LOADED_REGION);
        bsOut.Write(netPlayerNetworkId);

        network->SendToAllClients((const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
    }
}
