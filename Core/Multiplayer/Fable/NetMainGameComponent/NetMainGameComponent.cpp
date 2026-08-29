#define NOMINMAX

#include "windows.h"
#include <conio.h>
#include <sstream>
#include <string>

#include "NetMainGameComponent.h"

NetMainGameComponent& NetMainGameComponent::GetInstance()
{
    static NetMainGameComponent instance;
    return instance;
}

NetMainGameComponent::NetMainGameComponent() : mainGameComponent(CMainGameComponent::Get())
{
    SetupCallbacks();
}

NetMainGameComponent::~NetMainGameComponent()
{
    ClearCallbacks();
}

void NetMainGameComponent::SetupCallbacks()
{
    mainGameComponent->AddPostInitCallback("PostInit", [this]() { this->HandleMainGameComponentPostInit(); });
    mainGameComponent->AddUpdateCallback("Update", [this]() { this->HandleMainGameComponentUpdate(); });
    mainGameComponent->AddShutdownCallback("Shutdown", [this]() { this->HandleMainGameComponentShutdown(); });
}

void NetMainGameComponent::ClearCallbacks()
{
    mainGameComponent->RemovePostInitCallback("PostInit");
    mainGameComponent->RemoveUpdateCallback("Update");
    mainGameComponent->RemoveShutdownCallback("Shutdown");
}

void NetMainGameComponent::HandleMainGameComponentShutdown()
{
    network->Disconnect();
    if (network && !network->IsActive())
        Disconnect();
}

void NetMainGameComponent::HandleMainGameComponentPostInit() {
    Options();
}

void NetMainGameComponent::HandleMainGameComponentUpdate()
{
    Selection();

    if (!network)
        return;

    network->Update();

    if (network && !network->IsActive())
    {
        Disconnect();
        Options();
    }
}

void ClearInputBuffer() {
    std::cin.clear();

    while (_kbhit()) {
        (void)_getch();
    }
}

std::string ReadIP(std::string defaultIP = "127.0.0.1") {
    std::string input;
    std::cout << "IP (" << defaultIP << "): ";
    std::getline(std::cin, input);
    return input.empty() ? defaultIP : input;
}

unsigned short ReadPort(unsigned short defaultPort = 60000) {
    std::string input;
    std::cout << "Port (" << defaultPort << "): ";
    std::getline(std::cin, input);

    if (input.empty())
        return defaultPort;

    try {
        return (unsigned short)std::stoi(input);
    }
    catch (...) {
        return defaultPort;
    }
}

void NetMainGameComponent::Options()
{
    std::cout << "VK_NUMPAD1: Host" << std::endl;
    std::cout << "VK_NUMPAD2: Connect" << std::endl;
    std::cout << "VK_NUMPAD3: Disconnect" << std::endl;
}

void NetMainGameComponent::Selection() {
    if (network)
    {
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            ClearInputBuffer();
            network->Disconnect();
        }

        return;
    }

    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
    {
        Host();
    }
    else if (GetAsyncKeyState(VK_NUMPAD2) & 1)
    {
        Connect();
    }
}

void NetMainGameComponent::Host()
{
    ClearInputBuffer();

    mainGameComponent = CMainGameComponent::Get();
    network = std::make_unique<Network>();
    netPlayerManager = std::make_unique<NetPlayerManager>(
        network.get(),
        mainGameComponent
    );

    SetupNetworkCallbacks();

    unsigned short port = ReadPort();
    network->Host(port);
}

void NetMainGameComponent::Connect()
{
    ClearInputBuffer();

    mainGameComponent = CMainGameComponent::Get();
    network = std::make_unique<Network>();
    netPlayerManager = std::make_unique<NetPlayerManager>(
        network.get(),
        mainGameComponent
    );

    SetupNetworkCallbacks();

    std::string ip = ReadIP();
    unsigned short port = ReadPort();

    network->AddDisconnectionNotificationCallback("DisconnectionNotification", [this](int networkId) { if (networkId == 0) network->Disconnect(); });
    network->AddConnectionLostCallback("ConnectionLost", [this](int networkId) { if (networkId == 0) network->Disconnect(); });
    network->AddConnectionAttemptFailedCallback("ConnectionAttemptFailed", [this]() { network->Disconnect(); });

    network->Connect(ip.c_str(), port);
}

void NetMainGameComponent::Disconnect()
{
    ClearNetworkCallbacks();

    netPlayerManager.reset();
    network.reset();
}

void NetMainGameComponent::SetupNetworkCallbacks()
{

	SetupNetworkSessionCallbacks();
	SetupNetworkLifecycleCallbacks();
	SetupNetworkMotionCallbacks();
    SetupNetworkActionCallbacks();
    SetupNetworkStatsCallbacks();
    SetupNetworkAppearanceCallbacks();
    SetupNetworkExperienceCallbacks();
    SetupNetworkMorphCallbacks();
}

void NetMainGameComponent::ClearNetworkCallbacks()
{
    if (network) {
        ClearNetworkSessionCallbacks();
        ClearNetworkLifecycleCallbacks();
        ClearNetworkMotionCallbacks();
        ClearNetworkActionCallbacks();
        ClearNetworkStatsCallbacks();
        ClearNetworkAppearanceCallbacks();
        ClearNetworkExperienceCallbacks();
        ClearNetworkMorphCallbacks();
    }
}

void NetMainGameComponent::SetupNetworkSessionCallbacks()
{
    network->AddConnectionNotificationCallback("ConnectionNotification", [this](int networkId, SystemAddress systemAddress) {
        netPlayerManager->ConnectionNotification(networkId, systemAddress);
        });
}

void NetMainGameComponent::ClearNetworkSessionCallbacks()
{
    network->RemoveConnectionNotificationCallback("ConnectionNotification");
    network->RemoveDisconnectionNotificationCallback("DisconnectionNotification");
    network->RemoveConnectionLostCallback("ConnectionLost");
    network->RemoveConnectionAttemptFailedCallback("ConnectionAttemptFailed");
}

void NetMainGameComponent::SetupNetworkLifecycleCallbacks()
{
    network->AddCreateLocalNetPlayerCallback("CreateLocalNetPlayer", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector position = {};

        bs.Read(networkId);
        bs.Read(position);

        netPlayerManager->CreateLocalNetPlayer(networkId, position);
        });

    network->AddCreateNetPlayerCallback("CreateNetPlayer", [this](BitStream& bs) {
        int networkId = -1;
        int defGlobalIndex = 0;
        C3DVector position = {};
		float facingAngleXY = 0;

        bs.Read(networkId);
        bs.Read(defGlobalIndex);
        bs.Read(position);
        bs.Read(facingAngleXY);

        netPlayerManager->CreateNetPlayer(networkId, defGlobalIndex, position, facingAngleXY);
        });

    network->AddCreateNetPlayersCallback("CreateNetPlayers", [this](BitStream& bs) {
        netPlayerManager->CreateNetPlayers(bs);
        });

    network->AddDestroyLocalNetPlayerCallback("DestroyLocalNetPlayer", [this]() {
        netPlayerManager->DestroyLocalNetPlayer();
        });

    network->AddDestroyNetPlayerCallback("DestroyNetPlayer", [this](int networkId) {
        netPlayerManager->DestroyNetPlayer(networkId);
        });

    network->AddDestroyNetPlayersCallback("DestroyNetPlayers", [this]() {
        netPlayerManager->DestroyNetPlayers();
        });
}

void NetMainGameComponent::ClearNetworkLifecycleCallbacks()
{
    network->RemoveCreateLocalNetPlayerCallback("CreateLocalNetPlayer");
    network->RemoveCreateNetPlayerCallback("CreateNetPlayer");
    network->RemoveCreateNetPlayersCallback("CreateNetPlayers");

    network->RemoveDestroyLocalNetPlayerCallback("DestroyLocalNetPlayer");
    network->RemoveDestroyNetPlayerCallback("DestroyNetPlayer");
    network->RemoveDestroyNetPlayersCallback("DestroyNetPlayers");
}

void NetMainGameComponent::SetupNetworkMotionCallbacks()
{
    network->AddNetPlayerMovementCallback("NetPlayerMovement", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector remotePosition = {};
        C3DVector movementAcceleration = {};

        bs.Read(networkId);
        bs.Read(remotePosition);
        bs.Read(movementAcceleration);

        netPlayerManager->ReceiveNetPlayerMovement(networkId, remotePosition, movementAcceleration);
        });

    network->AddNetPlayerRotationCallback("NetPlayerRotation", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector up = {};
        C3DVector forward = {};

        bs.Read(networkId);
        bs.Read(up);
        bs.Read(forward);

        netPlayerManager->ReceiveNetPlayerRotation(networkId, up, forward);
        });
}

void NetMainGameComponent::ClearNetworkMotionCallbacks()
{
    network->RemoveNetPlayerMovementCallback("NetPlayerMovement");
    network->RemoveNetPlayerRotationCallback("NetPlayerRotation");
}

void NetMainGameComponent::SetupNetworkActionCallbacks()
{
    network->AddNetPlayerActionCallback("NetPlayerAction", [this](BitStream& bs) {
        int networkId = -1;
        uintptr_t actionOffset = 0;

        bs.Read(networkId);
        bs.Read(actionOffset);

        netPlayerManager->ReceiveNetPlayerAction(networkId, actionOffset, bs);
		});
}

void NetMainGameComponent::ClearNetworkActionCallbacks()
{
	network->RemoveNetPlayerActionCallback("NetPlayerAction");
}

void NetMainGameComponent::SetupNetworkStatsCallbacks()
{
    network->AddNetPlayerStatsCallback("NetPlayerStats", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerStats(networkId, bs);
        });
}

void NetMainGameComponent::ClearNetworkStatsCallbacks()
{
    network->RemoveNetPlayerStatsCallback("NetPlayerStats");
}

void NetMainGameComponent::SetupNetworkAppearanceCallbacks()
{
    network->AddNetPlayerAppearanceCallback("NetPlayerAppearance", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerAppearance(networkId, bs);
        });
}

void NetMainGameComponent::ClearNetworkAppearanceCallbacks()
{
    network->RemoveNetPlayerAppearanceCallback("NetPlayerAppearance");
}

void NetMainGameComponent::SetupNetworkExperienceCallbacks()
{
    network->AddNetPlayerExperienceCallback("NetPlayerExperience", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerExperience(networkId, bs);
        });
}

void NetMainGameComponent::ClearNetworkExperienceCallbacks()
{
    network->RemoveNetPlayerExperienceCallback("NetPlayerExperience");
}

void NetMainGameComponent::SetupNetworkMorphCallbacks()
{
    network->AddNetPlayerMorphCallback("NetPlayerMorph", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerMorph(networkId, bs);
        });
}

void NetMainGameComponent::ClearNetworkMorphCallbacks()
{
    network->RemoveNetPlayerMorphCallback("NetPlayerMorph");
}
