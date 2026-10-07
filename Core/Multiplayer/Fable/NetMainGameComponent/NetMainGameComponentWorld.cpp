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

        SetInLimboTillRegionLoaded(world, position);
        world->SetAsLoadingRegion(position, facingAngleXY, teleporter, duringCutScenes, door);
        });
}

void NetMainGameComponent::ClearNetworkWorldCallbacks()
{
    network->RemoveLoadRegionCallback("LoadRegion");
}
