#include "NetPlayerManager.h"

void NetPlayerManager::ReceiveNetPlayerAction(int networkId, uintptr_t actionOffset, SLNet::BitStream& bsIn)
{
    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_ACTION);
        bsOut.Write(networkId);
        bsOut.Write(actionOffset);

        network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
    }

    CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

    if (!creature)
		return;

    CThingCreatureBase& creatureBase = *reinterpret_cast<CThingCreatureBase*>(creature);
    void* actionBuffer = nullptr;

    switch (actionOffset)
    {
    case 0x012592D4: // CCreatureAction_PlayerInteractionGreet
    {
        int targetNetworkId = -1;
        bsIn.Read(targetNetworkId);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCreatureAction_PlayerInteractionGreet(creatureBase, target);
        break;
    }
	case 0x012761CC: // CCreatureAction_StartBlocking
    {
		bool block = false;
        bsIn.Read(block);

        CTCCombat* combat = reinterpret_cast<CTCCombat*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_COMBAT));

        if (!combat) {
            std::cout << "[NetPlayerManager::ReceiveNetPlayerAction]: !combat" << std::endl;
            return;
        }

        if (block)
        {
            actionBuffer = NetCreatureAction::CCreatureAction_StartBlocking(creatureBase);
            combat->SetBlocking();
        }
        else
        {
			combat->UnsetBlocking();
            return;
        }

        break;
    }
	case 0x01276974: // CCombatAction_ControlledStrafeJump
    {
        int targetNetworkId = -1;
        C3DVector requiredFacing, originalFacing;

        bsIn.Read(targetNetworkId);
        bsIn.Read(requiredFacing.X); bsIn.Read(requiredFacing.Y); bsIn.Read(requiredFacing.Z);
        bsIn.Read(originalFacing.X); bsIn.Read(originalFacing.Y); bsIn.Read(originalFacing.Z);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCombatAction_ControlledStrafeJump(creatureBase, target, requiredFacing, originalFacing);
        break;
    }
	case 0x01277D3C: // CCreatureAction_KickThingOnGround
    {
        int targetNetworkId = -1;
        bsIn.Read(targetNetworkId);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCreatureAction_KickThingOnGround(creatureBase, target);
        break;
    }
	case 0x012778CC: // CCreatureAction_InterruptableMidAttackAutoTurn
    {
        int targetNetworkId = -1;
        C3DVector required_facing;
        long weaponIndex = 0;

        bsIn.Read(targetNetworkId);
        bsIn.Read(required_facing.X); bsIn.Read(required_facing.Y); bsIn.Read(required_facing.Z);
        bsIn.Read(weaponIndex);

        CTCInventoryWeapons* inventoryWeapons =
            reinterpret_cast<CTCInventoryWeapons*>(
                reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY_WEAPONS));

        if (!inventoryWeapons)
        {
            std::cout << "[CCreatureAction_InterruptableMidAttackAutoTurn] !inventoryWeapons" << std::endl;
            return;
        }

        CThing* pweapon = nullptr;
        CThing* activeMelee = reinterpret_cast<CThing*>(inventoryWeapons->PActiveMeleeWeapon.GetPItem());
        CThing* activeRanged = reinterpret_cast<CThing*>(inventoryWeapons->PActiveRangedWeapon.GetPItem());

        if (activeMelee && activeMelee->DefGlobalIndex == weaponIndex)
        {
            pweapon = activeMelee;
        }
        else if (activeRanged && activeRanged->DefGlobalIndex == weaponIndex)
        {
            pweapon = activeRanged;
        }

        CDefPointer melee_ability{};
        CDefPointer* pmelee_ability = &melee_ability;

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = NetCreatureAction::CCreatureAction_InterruptableMidAttackAutoTurn(creatureBase, target, pweapon, required_facing, pmelee_ability);
        break;
    }
    case 0x0125CCBC: // CCreatureAction_UnsheatheItemFromInventory
    {
        CTCInventoryWeapons* inventoryWeapons =
            reinterpret_cast<CTCInventoryWeapons*>(
                reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY_WEAPONS));

        if (!inventoryWeapons)
        {
            std::cout << "[CCreatureAction_UnsheatheItemFromInventory] !inventoryWeapons" << std::endl;
            return;
        }

        NInventory::CTCInventoryBase* inventoryBase =
            reinterpret_cast<NInventory::CTCInventoryBase*>(
                reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY));

        if (!inventoryBase)
        {
            std::cout << "[CCreatureAction_UnsheatheItemFromInventory] !inventoryWeapons" << std::endl;
            return;
        }

        int itemIndex = -1;
        long interruption_priority = 0;

        bsIn.Read(itemIndex);
        bsIn.Read(interruption_priority);

        CThing* unsheatheItem = reinterpret_cast<CThing*>(creature);

        if (CTCInventoryItem::IsWeapon(itemIndex))
        {
            CThing* activeMelee = reinterpret_cast<CThing*>(inventoryWeapons->PActiveMeleeWeapon.GetPItem());
            CThing* activeRanged = reinterpret_cast<CThing*>(inventoryWeapons->PActiveRangedWeapon.GetPItem());

            if (activeMelee && activeMelee->DefGlobalIndex == itemIndex)
            {
                unsheatheItem = activeMelee;
            }
            else if (activeRanged && activeRanged->DefGlobalIndex == itemIndex)
            {
                unsheatheItem = activeRanged;
            }
		}
        else if (CTCInventoryItem::IsTrophy(itemIndex))
        {
            if (reinterpret_cast<NInventory::CTCInventoryBase*>(inventoryWeapons)->GetNumberOfItemsOfTypeInInventory(itemIndex) == 0)
            {
                CCharString scriptName("");
                creature->CreateAndAddObjectToInventory(
                    itemIndex,
                    -1,
                    true,
                    scriptName);
            }

			unsheatheItem = reinterpret_cast<CThing*>(inventoryBase->GetItemOfTypeInInventory(itemIndex));
        }

        CCreatureActionBase* pfollow_up_action = nullptr;

        actionBuffer = NetCreatureAction::CCreatureAction_UnsheatheItemFromInventory(creatureBase, *unsheatheItem, pfollow_up_action, interruption_priority);
        break;
    }
    case 0x0125C83C: // CCreatureAction_SheatheItemToInventory
    {
        CCreatureActionBase* pfollow_up_action = nullptr;
        long interruption_group_id = 0;

		bsIn.Read(interruption_group_id);

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
    CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAction]: !creature" << std::endl;
        return;
    }

    reinterpret_cast<CThingCreatureBase*>(creature)->AddSetCurrentActionCallback("SetCurrentAction" + std::to_string(networkId), [this, networkId](CThingCreatureBase* _this, CCreatureActionBase const& action) {
        CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

        if (!creature) {
            std::cout << "[NetPlayerManager::SetCurrentAction]: !creature" << std::endl;
            return;
        }

        uint64_t thisUID = reinterpret_cast<CThing*>(_this)->UniqueID;
        uint64_t creatureUID = reinterpret_cast<CThing*>(creature)->UniqueID;

        if (thisUID != creatureUID)
            return;

        uintptr_t actionOffset = *(uintptr_t*)&action;

        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_ACTION);
        bs.Write(networkId);
        bs.Write(actionOffset);

        // local helper to resolve target network ID
        auto getTargetNetworkId = [this](CThing* target) {
            int targetNetworkId = -1;
            if (target)
            {
                uint64_t targetUID = target->UniqueID;
                for (auto& netPlayer : netPlayers)
                {
                    CThing* targetCreature = reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(netPlayer->GetNetworkId()));
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
            bool block = true;
            bs.Write(block);
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

            C3DVector requiredFacing = *reinterpret_cast<const C3DVector*>(
                reinterpret_cast<uintptr_t>(&action) + 0x114);

            CBaseIntelligentPointer* pweapon =
                reinterpret_cast<CBaseIntelligentPointer*>(
                    reinterpret_cast<uintptr_t>(&action) + 0x120);

            CThing* weapon =
                reinterpret_cast<CThing*>(pweapon->GetPItem());

            int weaponIndex =
                weapon ? weapon->DefGlobalIndex : 0;

            bs.Write(targetNetworkId);
            bs.Write(requiredFacing.X); bs.Write(requiredFacing.Y); bs.Write(requiredFacing.Z);
            bs.Write(weaponIndex);
            break;
        }
        case 0x0125CCBC: // CCreatureAction_UnsheatheItemFromInventory
        {
            CBaseIntelligentPointer* pUnsheatheItem =
                reinterpret_cast<CBaseIntelligentPointer*>(
                    reinterpret_cast<uintptr_t>(&action) + 0xA8);

            CThing* unsheatheItem =
                reinterpret_cast<CThing*>(pUnsheatheItem->GetPItem());

            int itemIndex =
                unsheatheItem ? unsheatheItem->DefGlobalIndex : 0;

            int interruption_priority =
                *reinterpret_cast<int*>(
                    reinterpret_cast<uintptr_t>(&action) + 0x24);

            bs.Write(itemIndex);
            bs.Write(interruption_priority);

            break;
        }
        case 0x0125C83C: // CCreatureAction_SheatheItemToInventory
        {
            int interruption_group_id = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(&action) + 0x20);
			bs.Write(interruption_group_id);
            break;
        }
        default:
        {
            std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAction]: Unknown actionOffset: " << std::hex << actionOffset << std::dec << std::endl;
            return;
        }
        }

        if (localNetPlayer->GetNetworkId() == 0) {
            network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
        }
        else {
            network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
        }
    });

    CTCCombat* combat = reinterpret_cast<CTCCombat*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_COMBAT));

    if (!combat) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAction]: !combat" << std::endl;
        return;
    }

    combat->AddUnsetBlockingCallback("UnsetBlocking" + std::to_string(networkId), [this, networkId]() {
		uintptr_t actionOffset = 0x012761CC; // CCreatureAction_StartBlocking
		bool block = false;

        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_ACTION);
        bs.Write(networkId);
        bs.Write(actionOffset);
        bs.Write(block);

        if (localNetPlayer->GetNetworkId() == 0) {
            network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
        }
        else {
            network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
        }
        });
}
