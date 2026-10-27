#include "Multiplayer.h"

Network* (*CreateNetwork)() = &Multiplayer::CreateNetwork;
void (*DestroyNetwork)() = &Multiplayer::DestroyNetwork;
bool (*IsNetworkActive)() = &Multiplayer::IsNetworkActive;

bool (*HostNetwork)() = &Multiplayer::HostNetwork;
bool (*ConnectNetwork)() = &Multiplayer::ConnectNetwork;
bool (*DisconnectNetwork)() = &Multiplayer::DisconnectNetwork;

void (*UpdateNetwork)() = &Multiplayer::UpdateNetwork;

Multiplayer& Multiplayer::GetInstance()
{
    static Multiplayer instance;
    return instance;
}

Multiplayer::Multiplayer()
    : sdk(SDK::GetInstance())
{
    if (!LoadConfig())
        return;

    netMainGameComponent =
        std::make_unique<NetMainGameComponent>(network.get());
}

bool Multiplayer::LoadConfig()
{
    HMODULE hModule = GetModuleHandleW(L"EgoMP.dll");
    if (!hModule)
        return false;

    char dllPath[MAX_PATH];

    DWORD length = GetModuleFileNameA(hModule, dllPath, MAX_PATH);
    if (length == 0 || length >= MAX_PATH)
        return false;

    char* slash = strrchr(dllPath, '\\');
    if (!slash)
        return false;

    *slash = '\0';

    char iniPath[MAX_PATH];
    if (sprintf_s(iniPath, "%s\\EgoMP.ini", dllPath) < 0)
        return false;

    hostPort = GetPrivateProfileIntA("Host", "Port", 57150, iniPath);
    hostSlots = GetPrivateProfileIntA("Host", "Slots", 4, iniPath);

    char ip[64];

    GetPrivateProfileStringA(
        "Client", "IP", "127.0.0.1",
        ip, sizeof(ip), iniPath);

    clientIP = ip;
    clientPort = GetPrivateProfileIntA("Client", "Port", 57150, iniPath);

    return true;
}

Network* Multiplayer::CreateNetwork()
{
    Multiplayer& multiplayer = GetInstance();

    if (!multiplayer.network)
        multiplayer.network = std::make_unique<Network>();

    return multiplayer.network.get();
}

void Multiplayer::DestroyNetwork()
{
    Multiplayer& multiplayer = GetInstance();

    if (multiplayer.network)
        multiplayer.network.reset();
}

bool Multiplayer::IsNetworkActive()
{
    Multiplayer& multiplayer = GetInstance();
    return multiplayer.network && multiplayer.network->IsActive();
}

bool Multiplayer::HostNetwork()
{
    Multiplayer& multiplayer = GetInstance();
    return multiplayer.network->Host(multiplayer.hostPort, multiplayer.hostSlots);
}

bool Multiplayer::ConnectNetwork()
{
    Multiplayer& multiplayer = GetInstance();
    return multiplayer.network->Connect(multiplayer.clientIP, multiplayer.clientPort);
}

bool Multiplayer::DisconnectNetwork()
{
    Multiplayer& multiplayer = GetInstance();
    return multiplayer.network->Disconnect();
}

void Multiplayer::UpdateNetwork()
{
    Multiplayer& multiplayer = GetInstance();

    if (multiplayer.network)
        multiplayer.network->Update();
}
