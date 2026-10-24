#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupNetworkWorldCallbacks()
{
    network->AddLoadRegionCallback("LoadRegion", [this](BitStream& bs) {
        CWorld* world = mainGameComponent->GetWorld();

        C3DVector position = {};
        float facingAngleXY = 0;
        bool teleporter = false;
        bool duringCutScenes = false;
        bool door = false;

        bs.Read(position);
        bs.Read(facingAngleXY);
        bs.Read(teleporter);
        bs.Read(duringCutScenes);
        bs.Read(door);

        SetPlayerInLimboTillRegionLoaded(world, position);
        world->SetAsLoadingRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
        });

    network->AddLoadedRegionCallback("LoadedRegion", [this](BitStream& bsIn) {
        int netPlayerNetworkId = -1;
        bsIn.Read(netPlayerNetworkId);

		netWorld->ReceiveNetLoadedRegion(netPlayerNetworkId);
        netPlayerManager->SetNetPlayerAlpha(netPlayerNetworkId, 255);
        netPlayerManager->RefreshNetPlayerSheathedWeapons(netPlayerNetworkId);
        });
}

void NetMainGameComponent::ClearNetworkWorldCallbacks()
{
    network->RemoveLoadRegionCallback("LoadRegion");
    network->RemoveLoadedRegionCallback("LoadedRegion");
	network->RemoveWorldTimeCallback("WorldTime");
}
