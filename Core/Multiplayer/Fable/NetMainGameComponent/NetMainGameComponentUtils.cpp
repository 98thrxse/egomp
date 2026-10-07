#include "NetMainGameComponent.h"

void NetMainGameComponent::SetInLimboTillRegionLoaded(CWorld* world, C3DVector position)
{
    netPlayerManager->SetNetPlayersInLimbo(true);

    world->AddUpdateRegionLoadCallback("UpdateRegionLoad", [this, world, position]() {
        if (world->GetRegionLoadStatus() == CWorld::LOADING_NEW_REGION)
            netPlayerManager->SetNetPlayersPosition(position);

        if (world->GetRegionLoadStatus() != CWorld::NOT_LOADING_REGION)
            return;

        world->RemoveUpdateRegionLoadCallback("UpdateRegionLoad");
        netPlayerManager->SetNetPlayersInLimbo(false);
        });
}

void NetMainGameComponent::ClearInputBuffer()
{
    std::cin.clear();

    while (_kbhit()) {
        (void)_getch();
    }
}
