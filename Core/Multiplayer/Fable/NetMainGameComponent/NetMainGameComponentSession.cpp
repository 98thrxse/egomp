#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupSessionCallbacks()
{
    network->AddConnectionRequestAcceptedCallback("ConnectionRequestAccepted", [this](SystemAddress systemAddress) {
        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_CONNECTION_NOTIFICATION);
        network->SendTo((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED, systemAddress);
        });

    network->AddConnectionNotificationCallback("ConnectionNotification", [this](int networkId, SystemAddress systemAddress) {
        netWorld->ConnectionNotification(networkId, systemAddress);
        netPlayerManager->ConnectionNotification(networkId, systemAddress);
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
    network->RemoveConnectionRequestAcceptedCallback("ConnectionRequestAccepted");
    network->RemoveConnectionNotificationCallback("ConnectionNotification");

    network->RemoveDisconnectionNotificationCallback("DisconnectionNotification");
    network->RemoveConnectionLostCallback("ConnectionLost");
    network->RemoveConnectionAttemptFailedCallback("ConnectionAttemptFailed");
}
