#define NOMINMAX

#include "windows.h"
#include <sstream>

#include "NetMainGameComponent.h"

NetMainGameComponent::NetMainGameComponent(
    Network* network
)
    : network(network),
    mainGameComponent(CMainGameComponent::Get())
    
{
    SetupCallbacks();
}

NetMainGameComponent::~NetMainGameComponent()
{
    ClearCallbacks();
    network = nullptr;
}

void NetMainGameComponent::SetupCallbacks()
{
    mainGameComponent->AddUpdateCallback("Update", [this]() { this->HandleMainGameComponentUpdate(); });
    mainGameComponent->AddShutdownCallback("Shutdown", [this]() { this->HandleMainGameComponentShutdown(); });
}

void NetMainGameComponent::ClearCallbacks()
{
    mainGameComponent->RemoveUpdateCallback("Update");
    mainGameComponent->RemoveShutdownCallback("Shutdown");
}

void NetMainGameComponent::HandleMainGameComponentUpdate()
{
    Selection();
    UpdateNetwork();

    if (!IsNetworkActive())
        Clear();
}

void NetMainGameComponent::Selection()
{
    const bool hostPressed = GetAsyncKeyState(VK_NUMPAD1) & 1;
    const bool connectPressed = GetAsyncKeyState(VK_NUMPAD2) & 1;
    const bool disconnectPressed = GetAsyncKeyState(VK_NUMPAD3) & 1;

    if (!IsNetworkActive())
    {
        if (hostPressed)
            Host();
        else if (connectPressed)
            Connect();
    }
    else if (disconnectPressed)
    {
        Disconnect();
    }
}

void NetMainGameComponent::Host()
{
    network = CreateNetwork();

    mainGameComponent = CMainGameComponent::Get();
    netPlayerManager = std::make_unique<NetPlayerManager>(
        network,
        mainGameComponent
    );
    netWorld = std::make_unique<NetWorld>(
        network,
        mainGameComponent
    );

    SetupNetworkCallbacks();
    HostNetwork();
}

void NetMainGameComponent::Connect()
{
    network = CreateNetwork();

    mainGameComponent = CMainGameComponent::Get();
    netPlayerManager = std::make_unique<NetPlayerManager>(
        network,
        mainGameComponent
    );
    netWorld = std::make_unique<NetWorld>(
        network,
        mainGameComponent
    );

    SetupNetworkCallbacks();
    ConnectNetwork();
}

void NetMainGameComponent::Disconnect()
{
    netWorld->DestroyNetWorld();
    netPlayerManager->DestroyNetPlayers();
    netPlayerManager->DestroyLocalNetPlayer();

    if (networkId != 0)
    {
        netWorld->LoadAsLoadingRegion();
        netWorld->LoadTeleportingAsActive();
    }

    DisconnectNetwork();
}

void NetMainGameComponent::HandleMainGameComponentShutdown()
{
    Disconnect();

    if (!IsNetworkActive())
        Clear();
}

void NetMainGameComponent::Clear()
{
    ClearSDKCallbacks();
    ClearNetworkCallbacks();

    netPlayerManager.reset();
    netWorld.reset();

    DestroyNetwork();
    network = nullptr;
}

void NetMainGameComponent::SetupNetworkCallbacks()
{
	SetupNetworkSessionCallbacks();
    SetupNetworkWorldCallbacks();
    SetupNetworkPlayerManagerCallbacks();
}

void NetMainGameComponent::ClearNetworkCallbacks()
{
    if (network) {
        ClearNetworkSessionCallbacks();
        ClearNetworkWorldCallbacks();
        ClearNetworkPlayerManagerCallbacks();
    }
}

void NetMainGameComponent::ClearSDKCallbacks()
{
    ClearSDKWorldCallbacks();
}

void NetMainGameComponent::ClearSDKWorldCallbacks()
{
    CWorld* world = mainGameComponent->GetWorld();
    CGameScriptInterface* gameScriptInterface = world->GetGameScriptInterface();

    world->RemoveSetAsLoadingRegionCallback("SetAsLoadingRegion");
    gameScriptInterface->RemoveSetTeleportingAsActiveCallback("SetTeleportingAsActive");
}
