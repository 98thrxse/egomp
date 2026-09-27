#pragma once

#include "../../SDK/Fable/SDK.h"

#include "./NetMainGameComponent/NetMainGameComponent.h"

class Multiplayer
{
public:
	static Multiplayer& GetInstance();
	Multiplayer();

	static bool IsActive();

private:
	SDK& sdk;
	std::unique_ptr<Network> network;
	std::unique_ptr<NetMainGameComponent> netMainGameComponent;
};
