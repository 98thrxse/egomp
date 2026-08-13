#include "NetPlayerManager.h"

void NetPlayerManager::ApplyNetPlayerMovement(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::ApplyNetPlayerMovement]: !creature" << std::endl;
        return;
    }

    creature->AddResolveMovementAccelerationCallback("ResolveMovementAcceleration" + std::to_string(networkId), [this, networkId]() {
        CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);
        
        if (!creature) {
            std::cout << "[NetPlayerManager::AddResolveMovementAccelerationCallback]: !creature" << std::endl;
            return;
        }
        
        for (auto& netPlayer : netPlayers)
        {
            if (netPlayer && netPlayer->GetNetworkId() == networkId)
            {
                creature->MovementAcceleration = netPlayer->GetMovementAcceleration();

                CThing* thing = reinterpret_cast<CThing*>(creature);

                C3DVector remotePosition = netPlayer->GetPosition();
                C3DVector position = *thing->GetPos();

                float dx = remotePosition.X - position.X;
                float dy = remotePosition.Y - position.Y;
                float dz = remotePosition.Z - position.Z;

                float driftSq = (dx * dx) + (dy * dy) + (dz * dz);

                if (driftSq > 1)
                {
                    CTCPhysicsBase* physicsTC = thing->PhysicsTC;
                    physicsTC->SetPosition(remotePosition);
                }
            }
        }
        });
}

void NetPlayerManager::ApplyNetPlayerRotation(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::ApplyNetPlayerRotation]: !creature" << std::endl;
        return;
    }

    creature->AddResolveFacingDirectionCallback("ResolveFacingDirection" + std::to_string(networkId), [this, networkId]() {
        CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

        if (!creature) {
            std::cout << "[NetPlayerManager::AddResolveMovementAccelerationCallback]: !creature" << std::endl;
            return;
        }
        
        for (auto& netPlayer : netPlayers)
        {
            if (netPlayer && netPlayer->GetNetworkId() == networkId)
            {
                CRightHandedSet rhSet = netPlayer->GetRHSet();

                CThing* thing = reinterpret_cast<CThing*>(creature);
                CTCPhysicsBase* physicsTC = thing->PhysicsTC;
                CTCPhysicsStandard* physicsStandard = reinterpret_cast<CTCPhysicsStandard*>(physicsTC);
                physicsStandard->SetRHSet(rhSet);
                return;
            }
        }
        });
}

void NetPlayerManager::BroadcastLocalNetPlayerMovement(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerMovement]: !creature" << std::endl;
        return;
    }

    creature->AddResolveMovementAccelerationCallback("ResolveMovementAcceleration" + std::to_string(networkId), [this, networkId, creature]() {      
        C3DVector position = *(reinterpret_cast<CThing*>(creature))->GetPos();
        C3DVector movementAcceleration = creature->MovementAcceleration;

        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_MOVEMENT);
        bs.Write(networkId);
        bs.Write(position);
        bs.Write(movementAcceleration);

        if (localNetPlayer->GetNetworkId() == 0) {
            network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
        }
        else {
            network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
        }
        });
}
void NetPlayerManager::BroadcastLocalNetPlayerRotation(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerRotation]: !creature" << std::endl;
        return;
    }

    creature->AddResolveFacingDirectionCallback("ResolveFacingDirection" + std::to_string(networkId), [this, networkId, creature]() {
        CTCPhysicsBase* physicsTC = reinterpret_cast<CThing*>(creature)->PhysicsTC;
        CRightHandedSet* rhSet = reinterpret_cast<CTCPhysicsStandard*>(physicsTC)->GetRHSet();

        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_ROTATION);
        bs.Write(networkId);
        bs.Write(rhSet->Up);
        bs.Write(rhSet->Forward);

        if (localNetPlayer->GetNetworkId() == 0) {
            network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
        }
        else
        {
            network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
        }
        });
}


void NetPlayerManager::ReceiveNetPlayerMovement(int networkId, C3DVector remotePosition, C3DVector movementAcceleration)
{
    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_MOVEMENT);
        bs.Write(networkId);
        bs.Write(remotePosition);
        bs.Write(movementAcceleration);

        network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
    }

    for (auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetNetworkId() == networkId)
        {
            netPlayer->SetMovementAcceleration(movementAcceleration);
            netPlayer->SetPosition(remotePosition);

            return;
        }
    }
}

void NetPlayerManager::ReceiveNetPlayerRotation(int networkId, C3DVector up, C3DVector forward)
{
    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_ROTATION);
        bs.Write(networkId);
        bs.Write(up);
        bs.Write(forward);

        network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
    }

    for (auto& netPlayer : netPlayers)
    {
        if (netPlayer && netPlayer->GetNetworkId() == networkId)
        {
            CRightHandedSet rhSet;
            rhSet.Up = up;
            rhSet.Forward = forward;

            netPlayer->SetRHSet(rhSet);

            return;
        }
    }
}
