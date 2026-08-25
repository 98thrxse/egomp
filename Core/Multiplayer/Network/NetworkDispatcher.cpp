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

		case ID_CREATE_LOCAL_NET_PLAYER:
			HandleCreateLocalNetPlayer(packet);
			break;

		case ID_CREATE_NET_PLAYER:
			HandleCreateNetPlayer(packet);
			break;

		case ID_CREATE_NET_PLAYERS:
			HandleCreateNetPlayers(packet);
			break;

		case ID_PLAYER_MOVEMENT:
			HandleNetPlayerMovement(packet);
			break;

		case ID_PLAYER_ROTATION:
			HandleNetPlayerRotation(packet);
			break;

		case ID_PLAYER_ACTION:
			HandleNetPlayerAction(packet);
			break;

		case ID_PLAYER_STATS:
			HandleNetPlayerStats(packet);
			break;

		case ID_PLAYER_APPEARANCE:
			HandleNetPlayerAppearance(packet);
			break;

		case ID_DISCONNECTION_NOTIFICATION:
			HandleDisconnectionNotification(packet);
			break;

		case ID_CONNECTION_LOST:
			HandleConnectionLost(packet);
			break;

		case ID_DESTROY_NET_PLAYER:
			HandleDestroyNetPlayer(packet);
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
	SLNet::BitStream bs;
	bs.Write((SLNet::MessageID)ID_CONNECTION_NOTIFICATION);
	peer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);

	std::cout << "[Network::Update] ID_CONNECTION_REQUEST_ACCEPTED: "
		<< packet->systemAddress.ToString() << std::endl;

	for (const auto& pair : connectionAcceptedCallbacks)
	{
		if (pair.second)
			pair.second();
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

void Network::HandleCreateNetPlayer(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : createNetPlayerCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleCreateNetPlayers(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : createNetPlayersCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleNetPlayerMovement(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : netPlayerMovementCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleNetPlayerRotation(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : netPlayerRotationCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleNetPlayerAction(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : netPlayerActionCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleNetPlayerStats(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : netPlayerStatsCallbacks)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}

void Network::HandleNetPlayerAppearance(SLNet::Packet* packet)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : netPlayerAppearanceCallbacks)
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

	RemoveConnection(networkId);

	for (const auto& pair : disconnectionNotificationCallbacks)
	{
		if (pair.second)
			pair.second(networkId);
	}
}

void Network::HandleConnectionLost(SLNet::Packet* packet)
{
	int networkId = GetNetworkIdFromAddress(packet->systemAddress);

	std::cout << "[Network::Update] ID_CONNECTION_LOST: "
		<< packet->systemAddress.ToString() << " - " << networkId << std::endl;

	RemoveConnection(networkId);

	for (const auto& pair : connectionLostCallbacks)
	{
		if (pair.second)
			pair.second(networkId);
	}
}

void Network::HandleDestroyNetPlayer(SLNet::Packet* packet)
{
	int networkId = -1;

	SLNet::BitStream bs(packet->data, packet->length, false);
	bs.IgnoreBytes(sizeof(SLNet::MessageID));
	bs.Read(networkId);

	for (const auto& pair : destroyNetPlayerCallbacks)
	{
		if (pair.second)
			pair.second(networkId);
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
