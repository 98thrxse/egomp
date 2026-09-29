#include "NetPlayerManager.h"

void NetPlayerManager::ConnectionNotification(int networkId, SystemAddress systemAddress)
{
    C3DVector position =
        world->GetSaveGameMarkerPos();

    float facingAngleXY =
        world->GetSaveGameMarkerAngleXY();

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_LOCAL_NET_PLAYER_CREATE);
    bs.Write(networkId);
    bs.Write(position);
    bs.Write(facingAngleXY);

    network->SendTo((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED, systemAddress);
}
