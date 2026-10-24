#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupNetworkSessionCallbacks()
{
    network->AddNewIncomingConnectionCallback("NewIncomingConnection", [this](int networkId, SystemAddress systemAddress) {
		HandleNewIncomingConnection(networkId, systemAddress);
        });

    network->AddConnectionNotificationCallback("ConnectionNotification", [this](BitStream& bs) {
        HandleConnectionNotification(bs);
        });

    network->AddDisconnectionNotificationCallback("DisconnectionNotification", [this](int networkId) {
        HandleDisconnectionOrLost(networkId);
        });

    network->AddConnectionLostCallback("ConnectionLost", [this](int networkId) {
        HandleDisconnectionOrLost(networkId);
        });

    network->AddConnectionAttemptFailedCallback("ConnectionAttemptFailed", [this]() {
        Disconnect();
        });
}

void NetMainGameComponent::ClearNetworkSessionCallbacks()
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

    BroadcastConnectionNotification(systemAddress, networkId, position, facingAngleXY, teleporter, duringCutScenes, door);
}

void NetMainGameComponent::BroadcastConnectionNotification(SystemAddress systemAddress, int networkId, C3DVector position, float facingAngleXY, bool teleporter, bool duringCutScenes, bool door)
{
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
    CGameScriptInterface* gameScriptInterface = world->GetGameScriptInterface();
    CGameTimeManager* gameTimeManager = world->GetGameTimeManager();

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

    SetNetworkId(networkId);

    if (networkId == 0)
    {
        world->AddSetAsLoadingRegionCallback("SetAsLoadingRegion", [this, networkId, world](C3DVector const& position, float facingAngleXY, bool teleporter, bool duringCutScenes, bool door) {
            SetPlayerInLimboTillRegionLoaded(world, position);

            world->SetAsLoadingRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
            netWorld->BroadcastNetLoadRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
            });

        gameScriptInterface->AddSetTeleportingAsActiveCallback("SetTeleportingAsActive", [this, gameScriptInterface](bool active) {
            gameScriptInterface->SetTeleportingAsActive(active);
            });

        netWorld->CreateNetWorld();
        netPlayerManager->CreateLocalNetPlayer(position, facingAngleXY);
	}
    else
    {
        world->AddUpdateRegionLoadCallback("UpdateRegionLoad", [this, networkId, world, gameScriptInterface, position, facingAngleXY]() {
            if (world->GetRegionLoadStatus() == CWorld::READY_TO_BEGIN_FADE_OUT)
            {
                world->RemoveUpdateRegionLoadCallback("UpdateRegionLoad");

                network->AddWorldTimeCallback("WorldTime", [this](BitStream& bs) {
                    netWorld->ReceiveNetWorldTime(bs);
                    });

                netPlayerManager->CreateLocalNetPlayer(position, facingAngleXY);
            }
            });

        gameScriptInterface->AddSetTeleportingAsActiveCallback("SetTeleportingAsActive", [this, gameScriptInterface](bool active) {
            gameScriptInterface->SetTeleportingAsActive(false);
            });

        netWorld->SaveTeleportingAsActive(gameScriptInterface->IsTeleportingActive());
        gameScriptInterface->SetTeleportingAsActive(false);

        netWorld->SaveAsLoadingRegion(netPlayerManager->GetPlayerPosition(), netPlayerManager->GetPlayerFacingAngleXY());
        world->SetAsLoadingRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
    }
}

void NetMainGameComponent::HandleDisconnectionOrLost(int networkId)
{
    if (networkId == 0)
    {
        Disconnect();
    }
    else
    {
        netPlayerManager->SetNetPlayerParticle(networkId, 767, {}, false);
        netPlayerManager->DestroyNetPlayer(networkId);
    }
}
