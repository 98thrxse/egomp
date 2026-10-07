#pragma once

#include <iostream>
#include <conio.h>

#include "../../../SDK/Fable/SDK.h"
#include "../../Network/Network.h"

#include "../NetPlayerManager/NetPlayerManager.h"
#include "../NetWorld/NetWorld.h"

class NetMainGameComponent
{
public:
	NetMainGameComponent(std::unique_ptr<Network>& network);
	~NetMainGameComponent();

private:
	CMainGameComponent* mainGameComponent;

	std::unique_ptr<Network>& network;

	std::unique_ptr<NetPlayerManager> netPlayerManager;
	std::unique_ptr<NetWorld> netWorld;

	void SetupCallbacks();
	void ClearCallbacks();

	void ClearSDKCallbacks();
	void ClearSDKWorldCallbacks();
	void ClearSDKGameScriptInterfaceCallbacks();

	void SetupNetworkCallbacks();
	void ClearNetworkCallbacks();

	void SetupNetworkSessionCallbacks();
	void ClearNetworkSessionCallbacks();

	void SetupNetworkWorldCallbacks();
	void ClearNetworkWorldCallbacks();

	void SetupNetworkPlayerManagerCallbacks();
	void ClearNetworkPlayerManagerCallbacks();

	void Selection();
	void Options();
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
	
	void SetInLimboTillRegionLoaded(CWorld* world, C3DVector position);
	void ClearInputBuffer();
};
