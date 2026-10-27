#pragma once

#include "../../SDK/Fable/SDK.h"

#include "./NetMainGameComponent/NetMainGameComponent.h"

class Multiplayer
{
public:
	static Multiplayer& GetInstance();
	Multiplayer();

	static Network* CreateNetwork();
	static void DestroyNetwork();
	static bool IsNetworkActive();

	static bool HostNetwork();
	static bool ConnectNetwork();
	static bool DisconnectNetwork();

	static void UpdateNetwork();

	bool LoadConfig();

private:
	SDK& sdk;
	std::unique_ptr<Network> network;
	std::unique_ptr<NetMainGameComponent> netMainGameComponent;

	int hostPort = 57150;
	int hostSlots = 4;

	std::string clientIP = "127.0.0.1";
	int clientPort = 57150;
};
