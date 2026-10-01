#define NOMINMAX

#include "windows.h"
#include <conio.h>
#include <sstream>
#include <string>

#include "NetMainGameComponent.h"

NetMainGameComponent::NetMainGameComponent(
    std::unique_ptr<Network>& network
)
    : mainGameComponent(CMainGameComponent::Get()),
    network(network)
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
    if (!network)
        return;

    Disconnect();

    if (!network->IsActive())
        Clear();
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

    if (!network->IsActive())
    {
        Clear();
        Options();
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
    if (!network)
    {
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            Host();
        }
        else if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            Connect();
        }
    }
    else if (network && network->IsActive())
    {
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            Disconnect();
        }
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
    netWorld = std::make_unique<NetWorld>(
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
    netWorld = std::make_unique<NetWorld>(
        network.get(),
        mainGameComponent
    );

    SetupNetworkCallbacks();

    std::string ip = ReadIP();
    unsigned short port = ReadPort();
    network->Connect(ip.c_str(), port);
}

void NetMainGameComponent::Disconnect()
{
    ClearInputBuffer();
    network->Disconnect();
}

void NetMainGameComponent::Clear()
{
    ClearNetworkCallbacks();

    netPlayerManager.reset();
    netWorld.reset();
    network.reset();
}

void NetMainGameComponent::SetupNetworkCallbacks()
{
	SetupSessionCallbacks();
	SetupPlayerManagerCallbacks();
}

void NetMainGameComponent::ClearNetworkCallbacks()
{
    if (network) {
        ClearSessionCallbacks();
        ClearPlayerManagerCallbacks();
    }
}
