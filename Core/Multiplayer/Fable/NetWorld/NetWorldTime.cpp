#include "NetWorld.h"

void NetWorld::BroadcastNetWorldTime()
{
    auto lastSendTime = std::chrono::steady_clock::now();

    gameTimeManager->AddUpdateCallback(
        "TimeUpdate",
        [this, lastSendTime]() mutable
        {
            auto now = std::chrono::steady_clock::now();

            if (now - lastSendTime < std::chrono::milliseconds(2000))
                return;

            lastSendTime = now;

            float time = gameTimeManager->Time;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_WORLD_TIME);
            bs.Write(time);

			network->SendToAllClients((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), LOW_PRIORITY, UNRELIABLE_SEQUENCED);
        });
}

void NetWorld::ReceiveNetWorldTime(float time)
{
	gameTimeManager->Time = time;
}
