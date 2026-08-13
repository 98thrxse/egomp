#include "NetPlayerManager.h"

void NetPlayerManager::ReceiveNetPlayerAction(int networkId, uintptr_t actionOffset, SLNet::BitStream& bs)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerAction]: !creature" << std::endl;
		return;
    }

    CThingCreatureBase& creatureBase = *reinterpret_cast<CThingCreatureBase*>(creature);
    void* actionBuffer = nullptr;

    switch (actionOffset)
    {
    case 0x012592D4: // CCreatureAction_PlayerInteractionGreet
    {
        int targetNetworkId = -1;
        bs.Read(targetNetworkId);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCreatureAction_PlayerInteractionGreet(creatureBase, target);
        break;
    }
	case 0x012761CC: // CCreatureAction_StartBlocking
    {
        actionBuffer = NetCreatureAction::CCreatureAction_StartBlocking(creatureBase);
        break;
    }
	case 0x01276974: // CCombatAction_ControlledStrafeJump
    {
        int targetNetworkId = -1;
        C3DVector requiredFacing, originalFacing;

        bs.Read(targetNetworkId);
        bs.Read(requiredFacing.X); bs.Read(requiredFacing.Y); bs.Read(requiredFacing.Z);
        bs.Read(originalFacing.X); bs.Read(originalFacing.Y); bs.Read(originalFacing.Z);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCombatAction_ControlledStrafeJump(creatureBase, target, requiredFacing, originalFacing);
        break;
    }
	case 0x01277D3C: // CCreatureAction_KickThingOnGround
    {
        int targetNetworkId = -1;
        bs.Read(targetNetworkId);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCreatureAction_KickThingOnGround(creatureBase, target);
        break;
    }
	case 0x012778CC: // CCreatureAction_InterruptableMidAttackAutoTurn
    {
        int targetNetworkId = -1;
        C3DVector required_facing;
        CThing* pweapon = nullptr;

        CDefPointer melee_ability{};
        CDefPointer* pmelee_ability = &melee_ability;

        bs.Read(targetNetworkId);
        bs.Read(required_facing.X); bs.Read(required_facing.Y); bs.Read(required_facing.Z);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCreatureAction_InterruptableMidAttackAutoTurn(creatureBase, target, pweapon, required_facing, pmelee_ability);
        break;
    }
    case 0x0125CCBC: // CCreatureAction_UnsheatheItemFromInventory
    {
        CThing& unsheathe_item = *reinterpret_cast<CThing*>(creature);
        CCreatureActionBase* pfollow_up_action = nullptr;
        long interruption_priority = 0;

		bs.Read(interruption_priority);

        actionBuffer = NetCreatureAction::CCreatureAction_UnsheatheItemFromInventory(creatureBase, unsheathe_item, pfollow_up_action, interruption_priority);
        break;
    }
    case 0x0125C83C: // CCreatureAction_SheatheItemToInventory
    {
        CCreatureActionBase* pfollow_up_action = nullptr;
        long interruption_group_id = 0;

		bs.Read(interruption_group_id);

        actionBuffer = NetCreatureAction::CCreatureAction_SheatheItemToInventory(creatureBase, pfollow_up_action, interruption_group_id);
        break;
    }
    default:
        return;
    }

    if (actionBuffer)
    {
        creatureBase.SetCurrentAction(*(CCreatureActionBase*)actionBuffer);
    }
}

void NetPlayerManager::BroadcastLocalNetPlayerAction(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAction]: !creature" << std::endl;
        return;
    }

    reinterpret_cast<CThingCreatureBase*>(creature)->AddSetCurrentActionCallback("SetCurrentAction" + std::to_string(networkId), [this, networkId](CThingCreatureBase* _this, CCreatureActionBase const& action) {
        CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

        if (!creature) {
            std::cout << "[NetPlayerManager::SetCurrentAction]: !creature" << std::endl;
            return;
        }

        uint64_t thisUID = reinterpret_cast<CThing*>(_this)->UniqueID;
        uint64_t creatureUID = reinterpret_cast<CThing*>(creature)->UniqueID;

        if (thisUID == creatureUID)
        {
            uintptr_t actionOffset = *(uintptr_t*)&action;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_ACTION);
            bs.Write(networkId);
            bs.Write(actionOffset);

            // Local helper to resolve target network ID
            auto getTargetNetworkId = [this](CThing* target) {
                int targetNetworkId = -1;
                if (target)
                {
                    uint64_t targetUID = target->UniqueID;
                    for (auto& netPlayer : netPlayers)
                    {
                        CThing* targetCreature = reinterpret_cast<CThing*>(GetCreatureFromNetworkId(netPlayer->GetNetworkId()));
                        if (targetCreature && targetCreature->UniqueID == targetUID)
                        {
                            targetNetworkId = netPlayer->GetNetworkId();
                            break;
                        }
                    }
                }
                return targetNetworkId;
                };

            switch (actionOffset)
            {
            case 0x012592D4: // CCreatureAction_PlayerInteractionGreet
            {
                CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
                int targetNetworkId = getTargetNetworkId(target);
                bs.Write(targetNetworkId);
                break;
            }
            case 0x012761CC: // CCreatureAction_StartBlocking
            {
                break;
            }
            case 0x01276974: // CCombatAction_ControlledStrafeJump
            {
                CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
                int targetNetworkId = getTargetNetworkId(target);

                C3DVector requiredFacing = *reinterpret_cast<const C3DVector*>(reinterpret_cast<uintptr_t>(&action) + 0x114);
                C3DVector originalFacing = *reinterpret_cast<const C3DVector*>(reinterpret_cast<uintptr_t>(&action) + 0x120);

                bs.Write(targetNetworkId);
                bs.Write(requiredFacing.X); bs.Write(requiredFacing.Y); bs.Write(requiredFacing.Z);
                bs.Write(originalFacing.X); bs.Write(originalFacing.Y); bs.Write(originalFacing.Z);
                break;
            }
            case 0x01277D3C: // CCombatAction_KickThingOnGround
            {
                CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
                int targetNetworkId = getTargetNetworkId(target);
                bs.Write(targetNetworkId);
                break;
            }
            case 0x012778CC: // CCreatureAction_InterruptableMidAttackAutoTurn
            {
                CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
                int targetNetworkId = getTargetNetworkId(target);

                C3DVector requiredFacing = *reinterpret_cast<const C3DVector*>(reinterpret_cast<uintptr_t>(&action) + 0x114);

                bs.Write(targetNetworkId);
                bs.Write(requiredFacing.X); bs.Write(requiredFacing.Y); bs.Write(requiredFacing.Z);
                break;
            }
            case 0x0125CCBC: // CCreatureAction_UnsheatheItemFromInventory
            {
                int interuption_priority = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(&action) + 0x24);
				bs.Write(interuption_priority);

                break;
            }
            case 0x0125C83C: // CCreatureAction_SheatheItemToInventory
            {
                int interruption_group_id = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(&action) + 0x20);
				bs.Write(interruption_group_id);

                break;
            }
            default:
                return;
            }

            if (localNetPlayer->GetNetworkId() == 0) {
                network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
            }
            else {
                network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, UNRELIABLE_SEQUENCED);
            }
        }
        });
}
