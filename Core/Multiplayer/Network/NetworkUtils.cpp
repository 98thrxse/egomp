#include "Network.h"

int Network::GetFreeNetworkId()
{
	int networkId = 0;

	while (true)
	{
		bool used = false;
		for (auto& connection : connections)
		{
			if (connection.networkId == networkId)
			{
				used = true;
				break;
			}
		}

		if (!used)
			return networkId;

		++networkId;
	}
}

int Network::GetNetworkIdFromAddress(const SystemAddress& address) const
{
	SystemAddress hostAddress(this->settings.ip.c_str(), this->settings.port);
	if (address == hostAddress)
	{
		return 0;
	}

	for (const auto& connection : connections)
	{
		if (connection.address == address)
			return connection.networkId;
	}

	return -1;
}

SystemAddress Network::GetAddressFromNetworkId(int networkId) const
{
	for (const auto& connection : connections)
	{
		if (connection.networkId == networkId)
			return connection.address;
	}

	return SystemAddress();
}

void Network::HandlePacket(SLNet::Packet* packet, std::map<std::string, std::function<void(BitStream&)>>& callback)
{
	SLNet::BitStream bs(packet->data, packet->length, false);

	for (const auto& pair : callback)
	{
		if (pair.second)
		{
			bs.ResetReadPointer();
			bs.IgnoreBytes(sizeof(SLNet::MessageID));
			pair.second(bs);
		}
	}
}
