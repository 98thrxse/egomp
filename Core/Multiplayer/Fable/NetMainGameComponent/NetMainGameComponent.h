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

	void SetupNetworkCallbacks();
	void ClearNetworkCallbacks();

	void SetupSessionCallbacks();
	void ClearSessionCallbacks();

	void SetupWorldCallbacks();
	void ClearWorldCallbacks();

	void SetupPlayerManagerCallbacks();
	void ClearPlayerManagerCallbacks();

	void Selection();
	void Options();
	void Clear();

	void Host();
	void Connect();
	void Disconnect();

	void HandleMainGameComponentPostInit();
	void HandleMainGameComponentUpdate();
	void HandleMainGameComponentShutdown();

	void ClearInputBuffer();
};
