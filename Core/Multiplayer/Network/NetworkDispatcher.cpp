#include "Network.h"

void Network::Update()
{
	if (!peer || !peer->IsActive())
		return;

	for (Packet* packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
	{
		switch (packet->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
			HandleNewIncomingConnection(packet);
			break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
			HandleConnectionRequestAccepted(packet);
			break;

		case ID_CONNECTION_NOTIFICATION:
			HandleConnectionNotification(packet);
			break;

		case ID_LOCAL_NET_PLAYER_CREATE:
			HandleCreateLocalNetPlayer(packet);
			break;

		case ID_NET_PLAYER_CREATE:
			HandlePacket(packet, createNetPlayerCallbacks);
			break;

		case ID_NET_PLAYERS_CREATE:
			HandlePacket(packet, createNetPlayersCallbacks);
			break;

		case ID_PLAYER_MOVEMENT:
			HandlePacket(packet, playerMovementCallbacks);
			break;

		case ID_PLAYER_ROTATION:
			HandlePacket(packet, playerRotationCallbacks);
			break;

		case ID_PLAYER_STATS:
			HandlePacket(packet, playerStatsCallbacks);
			break;

		case ID_PLAYER_APPEARANCE:
			HandlePacket(packet, playerAppearanceCallbacks);
			break;

		case ID_PLAYER_EXPERIENCE:
			HandlePacket(packet, playerExperienceCallbacks);
			break;

		case ID_PLAYER_MORPH:
			HandlePacket(packet, playerMorphCallbacks);
			break;

		case ID_PLAYER_WEAPONS:
			HandlePacket(packet, playerWeaponsCallbacks);
			break;

		case ID_PLAYER_ACTION:
			HandlePacket(packet, playerActionCallbacks);
			break;

		case ID_NET_PLAYER_DESTROY:
			HandlePacket(packet, destroyNetPlayerCallbacks);
			break;

		case ID_WORLD_SYNC:
			HandlePacket(packet, syncWorldCallbacks);
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			HandleDisconnectionNotification(packet);
			break;

		case ID_CONNECTION_LOST:
			HandleConnectionLost(packet);
			break;

		case ID_CONNECTION_ATTEMPT_FAILED:
			HandleConnectionAttemptFailed(packet);
			break;

		default:
			std::cout << "[Network::Update] Received message with ID: " << (int)packet->data[0] << std::endl;
			break;
		}
	}
}

void Network::HandleNewIncomingConnection(SLNet::Packet* packet)
{
	std::cout << "[Network::Update] ID_NEW_INCOMING_CONNECTION: "
		<< packet->systemAddress.ToString() << std::endl;

	for (const auto& pair : newIncomingCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

void Network::HandleConnectionRequestAccepted(SLNet::Packet* packet)
{
	std::cout << "[Network::Update] ID_CONNECTION_REQUEST_ACCEPTED: "
		<< packet->systemAddress.ToString() << std::endl;

	for (const auto& pair : connectionRequestAcceptedCallbacks)
	{
		if (pair.second)
			pair.second(packet->systemAddress);
	}
}

void Network::HandleConnectionNotification(SLNet::Packet* packet)
{
	int networkId = GetFreeNetworkId();
	connections.push_back({ packet->systemAddress, networkId });

	std::cout << "[Network::Update] ID_CONNECTION_NOTIFICATION: "
		<< packet->systemAddress.ToString() << " - " << networkId << std::endl;

	for (const auto& pair : connectionNotificationCallbacks)
	{
		if (pair.second)
			pair.second(networkId, packet->systemAddress);
	}
}

void Network::HandleCreateLocalNetPlayer(SLNet::Packet* packet)
{
	int networkId = -1;

	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(SLNet::MessageID));
	bs.Read(networkId);

	self.networkId = networkId;
	self.address = peer->GetMyBoundAddress();

	for (const auto& pair : createLocalNetPlayerCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleDisconnectionNotification(SLNet::Packet* packet)
{
	int networkId = GetNetworkIdFromAddress(packet->systemAddress);

	std::cout << "[Network::Update] ID_DISCONNECTION_NOTIFICATION: "
		<< packet->systemAddress.ToString() << " - " << networkId << std::endl;

	for (const auto& pair : disconnectionNotificationCallbacks)
	{
		if (pair.second)
			pair.second(networkId);
	}

	for (auto connection = connections.begin(); connection != connections.end(); ++connection)
	{
		if (connection->networkId == networkId)
		{
			connections.erase(connection);
			break;
		}
	}
}

void Network::HandleConnectionLost(SLNet::Packet* packet)
{
	int networkId = GetNetworkIdFromAddress(packet->systemAddress);

	std::cout << "[Network::Update] ID_CONNECTION_LOST: "
		<< packet->systemAddress.ToString() << " - " << networkId << std::endl;

	for (const auto& pair : connectionLostCallbacks)
	{
		if (pair.second)
			pair.second(networkId);
	}

	for (auto connection = connections.begin(); connection != connections.end(); ++connection)
	{
		if (connection->networkId == networkId)
		{
			connections.erase(connection);
			break;
		}
	}
}

void Network::HandleConnectionAttemptFailed(SLNet::Packet* packet)
{
	std::cout << "[Network::Update] ID_CONNECTION_ATTEMPT_FAILED: "
		<< packet->systemAddress.ToString() << std::endl;

	for (const auto& pair : connectionAttemptFailedCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}
