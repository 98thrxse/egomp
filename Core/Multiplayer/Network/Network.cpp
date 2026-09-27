#include "Network.h"

using namespace SLNet;

Network::Network()
{
	peer = RakPeerInterface::GetInstance();
}

Network::~Network()
{
	if (peer)
	{
		for (Packet* packet = peer->Receive(); packet; packet = peer->Receive())
			peer->DeallocatePacket(packet);

		RakPeerInterface::DestroyInstance(peer);
		peer = nullptr;

		std::cout << "[Network::~Network] Disconnected" << std::endl;
	}
}

bool Network::Host(unsigned short port)
{
	this->settings.port = port;

	if (!peer)
	{
		MessageBoxW(NULL, L"[Network::Host] Failed to get RakPeerInterface instance!", L"Error", MB_OK);
		return false;
	}

	if (peer->IsActive())
	{
		MessageBoxW(NULL, L"[Network::Host] Peer already active!", L"Error", MB_OK);
		return false;
	}

	SocketDescriptor sd(this->settings.port, 0);

	if (peer->Startup(settings.slots, &sd, 1) != RAKNET_STARTED)
	{
		MessageBoxW(NULL, L"[Network::Host] Failed to start hosting!", L"Error", MB_OK);
		return false;
	}

	peer->SetMaximumIncomingConnections(this->settings.slots - 1);

	self.networkId = GetFreeNetworkId();
	self.address = peer->GetMyBoundAddress();
	connections.push_back(self);

	SLNet::BitStream bs;
	bs.Write(self.networkId);

	for (const auto& pair : createLocalNetPlayerCallbacks)
	{
		if (pair.second)
			pair.second(bs);
	}

	std::cout << "[Network::Host]: " << self.address.ToString(true) << " - " << self.networkId << std::endl;

	return true;
}

bool Network::Connect(const char* ip, unsigned short port)
{
	this->settings.ip = ip;
	this->settings.port = port;

	if (!peer)
	{
		MessageBoxW(NULL, L"[Network::Connect] Failed to get RakPeerInterface instance!", L"Error", MB_OK);
		return false;
	}

	if (peer->IsActive())
	{
		MessageBoxW(NULL, L"[Network::Connect] Peer already active!", L"Error", MB_OK);
		return false;
	}

	SocketDescriptor sd;

	if (peer->Startup(1, &sd, 1) != RAKNET_STARTED)
	{
		MessageBoxW(NULL, L"[Network::Connect] Failed to start client peer!", L"Error", MB_OK);
		return false;
	}

	if (peer->Connect(this->settings.ip.c_str(), this->settings.port, nullptr, 0) != CONNECTION_ATTEMPT_STARTED)
	{
		MessageBoxW(NULL, L"[Network::Connect] Failed to connect!", L"Error", MB_OK);
		return false;
	}

	return true;
}

bool Network::Disconnect()
{
	if (!peer)
	{
		MessageBoxW(NULL, L"[Network::Disconnect] Failed to get RakPeerInterface instance!", L"Error", MB_OK);
		return false;
	}

	if (!peer->IsActive())
	{
		MessageBoxW(NULL, L"[Network::Disconnect] Peer is not active!", L"Error", MB_OK);
		return false;
	}

	std::cout << "[Network::Disconnect] Disconnecting..." << std::endl;

	peer->Shutdown(1000);

	for (const auto& pair : destroyNetPlayersCallbacks)
	{
		if (pair.second)
			pair.second();
	}

	for (const auto& pair : destroyLocalNetPlayerCallbacks)
	{
		if (pair.second)
			pair.second();
	}

	self = Connection{};
	connections.clear();
	settings.ip.clear();
	settings.port = 0;

	return true;
}
