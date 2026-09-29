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
	std::map<std::string, std::function<void(SystemAddress)>> connectionRequestAcceptedCallbacks;
	std::map<std::string, std::function<void(int, SystemAddress)>> connectionNotificationCallbacks;

	std::map<std::string, std::function<void(BitStream&)>> createLocalNetPlayerCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> createNetPlayerCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> createNetPlayersCallbacks;

	std::map<std::string, std::function<void(BitStream&)>> playerMovementCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerRotationCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerStatsCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerAppearanceCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerExperienceCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerMorphCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerWeaponsCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> playerActionCallbacks;

	std::map<std::string, std::function<void()>> destroyLocalNetPlayerCallbacks;
	std::map<std::string, std::function<void(BitStream&)>> destroyNetPlayerCallbacks;
	std::map<std::string, std::function<void()>> destroyNetPlayersCallbacks;

	std::map<std::string, std::function<void(BitStream&)>> syncWorldCallbacks;

	std::map<std::string, std::function<void(int)>> disconnectionNotificationCallbacks;
	std::map<std::string, std::function<void(int)>> connectionLostCallbacks;
	std::map<std::string, std::function<void()>> connectionAttemptFailedCallbacks;

	void HandleNewIncomingConnection(SLNet::Packet* packet);
	void HandleConnectionRequestAccepted(SLNet::Packet* packet);
	void HandleConnectionNotification(SLNet::Packet* packet);

	void HandleCreateLocalNetPlayer(SLNet::Packet* packet);

	void HandleDisconnectionNotification(SLNet::Packet* packet);
	void HandleConnectionLost(SLNet::Packet* packet);
	void HandleConnectionAttemptFailed(SLNet::Packet* packet);

	void HandlePacket(SLNet::Packet* packet, std::map<std::string, std::function<void(BitStream&)>>& callback);

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

	void AddConnectionRequestAcceptedCallback(const std::string& id, std::function<void(SystemAddress)> cb) { connectionRequestAcceptedCallbacks[id] = cb; }
	void RemoveConnectionRequestAcceptedCallback(const std::string& id) { connectionRequestAcceptedCallbacks.erase(id); }

	void AddConnectionNotificationCallback(const std::string& id, std::function<void(int, SystemAddress)> cb) { connectionNotificationCallbacks[id] = cb; }
	void RemoveConnectionNotificationCallback(const std::string& id) { connectionNotificationCallbacks.erase(id); }

	void AddCreateLocalNetPlayerCallback(const std::string& id, std::function<void(BitStream&)> cb) { createLocalNetPlayerCallbacks[id] = cb; }
	void RemoveCreateLocalNetPlayerCallback(const std::string& id) { createLocalNetPlayerCallbacks.erase(id); }

	void AddCreateNetPlayerCallback(const std::string& id, std::function<void(BitStream&)> cb) { createNetPlayerCallbacks[id] = cb; }
	void RemoveCreateNetPlayerCallback(const std::string& id) { createNetPlayerCallbacks.erase(id); }

	void AddCreateNetPlayersCallback(const std::string& id, std::function<void(BitStream&)> cb) { createNetPlayersCallbacks[id] = cb; }
	void RemoveCreateNetPlayersCallback(const std::string& id) { createNetPlayersCallbacks.erase(id); }

	void AddPlayerMovementCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerMovementCallbacks[id] = cb; }
	void RemovePlayerMovementCallback(const std::string& id) { playerMovementCallbacks.erase(id); }

	void AddPlayerRotationCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerRotationCallbacks[id] = cb; }
	void RemovePlayerRotationCallback(const std::string& id) { playerRotationCallbacks.erase(id); }

	void AddPlayerStatsCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerStatsCallbacks[id] = cb; }
	void RemovePlayerStatsCallback(const std::string& id) { playerStatsCallbacks.erase(id); }
	
	void AddPlayerAppearanceCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerAppearanceCallbacks[id] = cb; }
	void RemovePlayerAppearanceCallback(const std::string& id) { playerAppearanceCallbacks.erase(id); }

	void AddPlayerExperienceCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerExperienceCallbacks[id] = cb; }
	void RemovePlayerExperienceCallback(const std::string& id) { playerExperienceCallbacks.erase(id); }
	
	void AddPlayerMorphCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerMorphCallbacks[id] = cb; }
	void RemovePlayerMorphCallback(const std::string& id) { playerMorphCallbacks.erase(id); }

	void AddPlayerWeaponsCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerWeaponsCallbacks[id] = cb; }
	void RemovePlayerWeaponsCallback(const std::string& id) { playerWeaponsCallbacks.erase(id); }

	void AddPlayerActionCallback(const std::string& id, std::function<void(BitStream&)> cb) { playerActionCallbacks[id] = cb; }
	void RemovePlayerActionCallback(const std::string& id) { playerActionCallbacks.erase(id); }

	void AddDestroyLocalNetPlayerCallback(const std::string& id, std::function<void()> cb) { destroyLocalNetPlayerCallbacks[id] = cb; }
	void RemoveDestroyLocalNetPlayerCallback(const std::string& id) { destroyLocalNetPlayerCallbacks.erase(id); }

	void AddDestroyNetPlayerCallback(const std::string& id, std::function<void(BitStream&)> cb) { destroyNetPlayerCallbacks[id] = cb; }
	void RemoveDestroyNetPlayerCallback(const std::string& id) { destroyNetPlayerCallbacks.erase(id); }

	void AddDestroyNetPlayersCallback(const std::string& id, std::function<void()> cb) { destroyNetPlayersCallbacks[id] = cb; }
	void RemoveDestroyNetPlayersCallback(const std::string& id) { destroyNetPlayersCallbacks.erase(id); }

	void AddSyncWorldCallback(const std::string& id, std::function<void(BitStream&)> cb) { syncWorldCallbacks[id] = cb; }
	void RemoveSyncWorldCallback(const std::string& id) { syncWorldCallbacks.erase(id); }

	void AddDisconnectionNotificationCallback(const std::string& id, std::function<void(int)> cb) { disconnectionNotificationCallbacks[id] = cb; }
	void RemoveDisconnectionNotificationCallback(const std::string& id) { disconnectionNotificationCallbacks.erase(id); }

	void AddConnectionLostCallback(const std::string& id, std::function<void(int)> cb) { connectionLostCallbacks[id] = cb; }
	void RemoveConnectionLostCallback(const std::string& id) { connectionLostCallbacks.erase(id); }

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
