#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupSessionCallbacks()
{
    network->AddNewIncomingConnectionCallback("NewIncomingConnection", [this](int networkId, SystemAddress systemAddress) {
		HandleNewIncomingConnection(networkId, systemAddress);
        });

    network->AddConnectionNotificationCallback("ConnectionNotification", [this](BitStream& bs) {
        HandleConnectionNotification(bs);
        });

    network->AddDisconnectionNotificationCallback("DisconnectionNotification", [this](int networkId) {
        if (networkId == 0)
            Disconnect();
        else
            netPlayerManager->DestroyNetPlayer(networkId);
        });

    network->AddConnectionLostCallback("ConnectionLost", [this](int networkId) {
        if (networkId == 0)
            Disconnect();
        else
            netPlayerManager->DestroyNetPlayer(networkId);
        });

    network->AddConnectionAttemptFailedCallback("ConnectionAttemptFailed", [this]() {
        Disconnect();
        });
}

void NetMainGameComponent::ClearSessionCallbacks()
{
    network->RemoveNewIncomingConnectionCallback("NewIncomingConnection");
    network->RemoveConnectionNotificationCallback("ConnectionNotification");

    network->RemoveDisconnectionNotificationCallback("DisconnectionNotification");
    network->RemoveConnectionLostCallback("ConnectionLost");
    network->RemoveConnectionAttemptFailedCallback("ConnectionAttemptFailed");
}

void NetMainGameComponent::HandleNewIncomingConnection(int networkId, SystemAddress systemAddress)
{
    CWorld* world = mainGameComponent->GetWorld();

    C3DVector position =
        world->GetSaveGameMarkerPos();

    float facingAngleXY =
        world->GetSaveGameMarkerAngleXY();

    bool teleporter = true;
    bool duringCutScenes = true;
    bool door = false;

    SLNet::BitStream bs;
    bs.Write((SLNet::MessageID)ID_CONNECTION_NOTIFICATION);
    bs.Write(networkId);
    bs.Write(position);
    bs.Write(facingAngleXY);
    bs.Write(teleporter);
    bs.Write(duringCutScenes);
    bs.Write(door);

    network->SendTo((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED, systemAddress);
}

void NetMainGameComponent::HandleConnectionNotification(BitStream& bs)
{
    CWorld* world = mainGameComponent->GetWorld();

    int networkId = -1;
    C3DVector position = {};
    float facingAngleXY = 0;
    bool teleporter = false;
    bool duringCutScenes = false;
    bool door = false;

    bs.Read(networkId);
    bs.Read(position);
    bs.Read(facingAngleXY);
    bs.Read(teleporter);
    bs.Read(duringCutScenes);
    bs.Read(door);

    if (networkId == 0)
    {
        netPlayerManager->CreateLocalNetPlayer(networkId, position, facingAngleXY);
        return;
	}

    world->AddUpdateRegionLoadCallback("UpdateRegionLoad", [this, world, networkId, position, facingAngleXY]() {
        if (world->GetRegionLoadStatus() != CWorld::NOT_LOADING_REGION)
            return;

        world->RemoveUpdateRegionLoadCallback("UpdateRegionLoad");
		netPlayerManager->CreateLocalNetPlayer(networkId, position, facingAngleXY);
        });

    netWorld->LoadRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
}
