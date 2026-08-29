#pragma once

#include <map>
#include <vector>
#include <functional>
#include <iostream>

#include <SLikeNet/RakPeerInterface.h>
#include "SLikeNet/RakNetTypes.h"
#include "SLikeNet/BitStream.h"

#include "NetworkMessages.h"

using namespace SLNet;

class Network
{
private:
	RakPeerInterface* peer;

	struct Settings
	{
		std::string ip = "127.0.0.1";
		unsigned short port = 60000;
		int slots = 4;
	};
	Settings settings;

	struct Connection
	{
		SLNet::SystemAddress address;
		int networkId = -1;
	};
	Connection self;
	std::vector<Connection> connections;

	std::map<std::string, std::function<void()>> newIncomingCallbacks;
	std::map<std::string, std::function<void()>> connectionAcceptedCallbacks;
	std::map<std::string, std::function<void(int, SystemAddress)>> connectionNotificationCallbacks;

	std::map<std::string, std::function<void(BitStream&)>> createLocalNetPlayerCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> createNetPlayerCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> createNetPlayersCallbacks;

	std::map<std::string, std::function<void(BitStream&)>> netPlayerMovementCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> netPlayerRotationCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> netPlayerActionCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> netPlayerStatsCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> netPlayerAppearanceCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> netPlayerExperienceCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> netPlayerMorphCallbacks;

	std::map<std::string, std::function<void(int)>> disconnectionNotificationCallbacks;
	std::map<std::string, std::function<void(int)>> connectionLostCallbacks;

	std::map<std::string, std::function<void()>> destroyLocalNetPlayerCallbacks;
	std::map<std::string, std::function<void(int)>> destroyNetPlayerCallbacks;
	std::map<std::string, std::function<void()>> destroyNetPlayersCallbacks;

	std::map<std::string, std::function<void()>> connectionAttemptFailedCallbacks;

	void HandleNewIncomingConnection(SLNet::Packet* packet);
	void HandleConnectionRequestAccepted(SLNet::Packet* packet);
	void HandleConnectionNotification(SLNet::Packet* packet);

	void HandleCreateLocalNetPlayer(SLNet::Packet* packet);
	void HandleCreateNetPlayer(SLNet::Packet* packet);
	void HandleCreateNetPlayers(SLNet::Packet* packet);

	void HandleNetPlayerMovement(SLNet::Packet* packet);
	void HandleNetPlayerRotation(SLNet::Packet* packet);
	void HandleNetPlayerAction(SLNet::Packet* packet);
	void HandleNetPlayerStats(SLNet::Packet* packet);
	void HandleNetPlayerAppearance(SLNet::Packet* packet);
	void HandleNetPlayerExperience(SLNet::Packet* packet);
	void HandleNetPlayerMorph(SLNet::Packet* packet);

	void HandleDisconnectionNotification(SLNet::Packet* packet);
	void HandleConnectionLost(SLNet::Packet* packet);
	void HandleDestroyNetPlayer(SLNet::Packet* packet);

	void HandleConnectionAttemptFailed(SLNet::Packet* packet);

	void RemoveSelf();
	void RemoveConnection(int networkId);
	void RemoveConnections();
	void ClearSession();

	int GetFreeNetworkId();
	int GetNetworkIdFromAddress(const SLNet::SystemAddress& address) const;
	SystemAddress GetAddressFromNetworkId(int networkId) const;

public:
	Network();
	~Network();

	bool Host(unsigned short port);
	bool Connect(const char* ip, unsigned short port);
	bool Disconnect();
	void Update();

	bool IsActive() const { return peer && peer->IsActive(); }

	void AddNewIncomingCallback(const std::string& id, std::function<void()> cb) { newIncomingCallbacks[id] = cb; }
	void RemoveNewIncomingCallback(const std::string& id) { newIncomingCallbacks.erase(id); }

	void AddConnectionAcceptedCallback(const std::string& id, std::function<void()> cb) { connectionAcceptedCallbacks[id] = cb; }
	void RemoveConnectionAcceptedCallback(const std::string& id) { connectionAcceptedCallbacks.erase(id); }

	void AddConnectionNotificationCallback(const std::string& id, std::function<void(int, SystemAddress)> cb) { connectionNotificationCallbacks[id] = cb; }
	void RemoveConnectionNotificationCallback(const std::string& id) { connectionNotificationCallbacks.erase(id); }

	void AddCreateLocalNetPlayerCallback(const std::string& id, std::function<void(BitStream&)> cb) { createLocalNetPlayerCallbacks[id] = cb; }
	void RemoveCreateLocalNetPlayerCallback(const std::string& id) { createLocalNetPlayerCallbacks.erase(id); }

	void AddCreateNetPlayerCallback(const std::string& id, std::function<void(BitStream&)> cb) { createNetPlayerCallbacks[id] = cb; }
	void RemoveCreateNetPlayerCallback(const std::string& id) { createNetPlayerCallbacks.erase(id); }

	void AddCreateNetPlayersCallback(const std::string& id, std::function<void(BitStream&)> cb) { createNetPlayersCallbacks[id] = cb; }
	void RemoveCreateNetPlayersCallback(const std::string& id) { createNetPlayersCallbacks.erase(id); }

	void AddNetPlayerMovementCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerMovementCallbacks[id] = cb; }
	void RemoveNetPlayerMovementCallback(const std::string& id) { netPlayerMovementCallbacks.erase(id); }

	void AddNetPlayerRotationCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerRotationCallbacks[id] = cb; }
	void RemoveNetPlayerRotationCallback(const std::string& id) { netPlayerRotationCallbacks.erase(id); }

	void AddNetPlayerActionCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerActionCallbacks[id] = cb; }
	void RemoveNetPlayerActionCallback(const std::string& id) { netPlayerActionCallbacks.erase(id); }

	void AddNetPlayerStatsCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerStatsCallbacks[id] = cb; }
	void RemoveNetPlayerStatsCallback(const std::string& id) { netPlayerStatsCallbacks.erase(id); }
	
	void AddNetPlayerAppearanceCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerAppearanceCallbacks[id] = cb; }
	void RemoveNetPlayerAppearanceCallback(const std::string& id) { netPlayerAppearanceCallbacks.erase(id); }

	void AddNetPlayerExperienceCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerExperienceCallbacks[id] = cb; }
	void RemoveNetPlayerExperienceCallback(const std::string& id) { netPlayerExperienceCallbacks.erase(id); }
	
	void AddNetPlayerMorphCallback(const std::string& id, std::function<void(BitStream&)> cb) { netPlayerMorphCallbacks[id] = cb; }
	void RemoveNetPlayerMorphCallback(const std::string& id) { netPlayerMorphCallbacks.erase(id); }

	void AddDisconnectionNotificationCallback(const std::string& id, std::function<void(int)> cb) { disconnectionNotificationCallbacks[id] = cb; }
	void RemoveDisconnectionNotificationCallback(const std::string& id) { disconnectionNotificationCallbacks.erase(id); }

	void AddConnectionLostCallback(const std::string& id, std::function<void(int)> cb) { connectionLostCallbacks[id] = cb; }
	void RemoveConnectionLostCallback(const std::string& id) { connectionLostCallbacks.erase(id); }

	void AddDestroyLocalNetPlayerCallback(const std::string& id, std::function<void()> cb) { destroyLocalNetPlayerCallbacks[id] = cb; }
	void RemoveDestroyLocalNetPlayerCallback(const std::string& id) { destroyLocalNetPlayerCallbacks.erase(id); }

	void AddDestroyNetPlayerCallback(const std::string& id, std::function<void(int)> cb) { destroyNetPlayerCallbacks[id] = cb; }
	void RemoveDestroyNetPlayerCallback(const std::string& id) { destroyNetPlayerCallbacks.erase(id); }

	void AddDestroyNetPlayersCallback(const std::string& id, std::function<void()> cb) { destroyNetPlayersCallbacks[id] = cb; }
	void RemoveDestroyNetPlayersCallback(const std::string& id) { destroyNetPlayersCallbacks.erase(id); }

	void AddConnectionAttemptFailedCallback(const std::string& id, std::function<void()> cb) { connectionAttemptFailedCallbacks[id] = cb; }
	void RemoveConnectionAttemptFailedCallback(const std::string& id) { connectionAttemptFailedCallbacks.erase(id); }

	void SendToClient(int networkId, const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED);
	void SendToAllClients(const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED);
	void SendToAll(const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED);
	void SendToHost(const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED);
	void SendTo(const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED,
		SystemAddress systemAddress = SLNet::UNASSIGNED_SYSTEM_ADDRESS);
	void SendToAllExcept(int networkId, const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED);
	void SendToAllClientsExcept(int networkId, const char* data, int length,
		PacketPriority priority = HIGH_PRIORITY,
		PacketReliability reliability = RELIABLE_ORDERED);
};
