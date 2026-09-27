#include "NetPlayerManager.h"

void NetPlayerManager::ConnectionNotification(int networkId, SystemAddress systemAddress)
{
    int localId = localNetPlayer->GetLocalId();
    CThingPlayerCreature* creature = GetPlayerCreatureFromLocalId(localId);

    if (!creature) {
        std::cout << "[NetPlayerManager::ConnectionNotification]: !creature" << std::endl;
        return;
    }

    C3DVector position = *(reinterpret_cast<CThing*>(creature))->GetPos();

    CTCPhysicsBase* physicsTC = reinterpret_cast<CThing*>(creature)->PhysicsTC;
    float facingAngleXY = reinterpret_cast<CTCPhysicsStandard*>(physicsTC)->GetFacingAngleXY();

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_CREATE_LOCAL_NET_PLAYER);
    bs.Write(networkId);
    bs.Write(position);
    bs.Write(facingAngleXY);

    network->SendTo((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED, systemAddress);
}
