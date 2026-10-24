#include "NetMainGameComponent.h"

void NetMainGameComponent::SetPlayerInLimboTillRegionLoaded(CWorld* world, C3DVector position)
{
    netPlayerManager->SetNetPlayersAlpha(85);
    netPlayerManager->RefreshNetPlayersSheathedWeapons();
    netPlayerManager->SetNetPlayersInLimbo(true);

    world->AddUpdateRegionLoadCallback("UpdateRegionLoad", [this, world, position]() {
        if (world->GetRegionLoadStatus() == CWorld::LOADING_NEW_REGION)
            netPlayerManager->SetNetPlayersPosition(position);

        if (world->GetRegionLoadStatus() != CWorld::NOT_LOADING_REGION)
            return;

        world->RemoveUpdateRegionLoadCallback("UpdateRegionLoad");

        netPlayerManager->SetNetPlayersInLimbo(false);
        netWorld->BroadcastNetLoadedRegion();
        });
}

void NetMainGameComponent::ClearInputBuffer()
{
    std::cin.clear();

    while (_kbhit()) {
        (void)_getch();
    }
}

void NetMainGameComponent::SetNetworkId(int id)
{
    networkId = id;

    netWorld->SetNetworkId(id);
    netPlayerManager->SetNetworkId(id);
}

int NetMainGameComponent::GetNetworkId() const
{
    return networkId;
}
