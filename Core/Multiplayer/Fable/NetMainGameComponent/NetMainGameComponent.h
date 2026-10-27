#pragma once

#include <iostream>
#include <conio.h>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

#include "../NetPlayerManager/NetPlayerManager.h"
#include "../NetWorld/NetWorld.h"

extern Network* (*CreateNetwork)();
extern void (*DestroyNetwork)();
extern bool (*IsNetworkActive)();

extern bool (*HostNetwork)();
extern bool (*ConnectNetwork)();
extern bool (*DisconnectNetwork)();

extern void (*UpdateNetwork)();

class NetMainGameComponent
{
public:
	NetMainGameComponent(Network* network);
	~NetMainGameComponent();

	void SetNetworkId(int id);
	int GetNetworkId() const;

private:
	CMainGameComponent* mainGameComponent;

	Network* network;

	std::unique_ptr<NetPlayerManager> netPlayerManager;
	std::unique_ptr<NetWorld> netWorld;

	int networkId;

	void SetupCallbacks();
	void ClearCallbacks();

	void ClearSDKCallbacks();
	void ClearSDKWorldCallbacks();

	void SetupNetworkCallbacks();
	void ClearNetworkCallbacks();

	void SetupNetworkSessionCallbacks();
	void ClearNetworkSessionCallbacks();

	void SetupNetworkWorldCallbacks();
	void ClearNetworkWorldCallbacks();

	void SetupNetworkPlayerManagerCallbacks();
	void ClearNetworkPlayerManagerCallbacks();

	void Selection();
	void Clear();

	void Host();
	void Connect();
	void Disconnect();

	void BroadcastConnectionNotification(SystemAddress systemAddress, int networkId, C3DVector position, float facingAngleXY, bool teleporter, bool duringCutScenes, bool door);

	void HandleMainGameComponentPostInit();
	void HandleMainGameComponentUpdate();
	void HandleMainGameComponentShutdown();

	void HandleNewIncomingConnection(int networkId, SystemAddress systemAddress);
	void HandleConnectionNotification(BitStream& bs);

	void HandleDisconnectionOrLost(int networkId);
	
	void SetPlayerInLimboTillRegionLoaded(CWorld* world, C3DVector position);
};
