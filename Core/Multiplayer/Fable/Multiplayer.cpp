#include "Multiplayer.h"

bool (*IsMultiplayer)() = &Multiplayer::IsActive;

Multiplayer& Multiplayer::GetInstance()
{
    static Multiplayer instance;
    return instance;
}

Multiplayer::Multiplayer()
    : sdk(SDK::GetInstance())
{
    netMainGameComponent =
        std::make_unique<NetMainGameComponent>(network);
}

bool Multiplayer::IsActive()
{
    Multiplayer& multiplayer = GetInstance();
    return multiplayer.network && multiplayer.network->IsActive();
}
