#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupWorldCallbacks()
{
    network->AddSyncWorldCallback("SyncWorld", [this](BitStream& bs) {
        netWorld->SyncWorld(bs);
        });
}

void NetMainGameComponent::ClearWorldCallbacks()
{
    network->RemoveSyncWorldCallback("SyncWorld");
}
