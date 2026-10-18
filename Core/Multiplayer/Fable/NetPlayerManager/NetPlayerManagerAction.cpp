#include "NetPlayerManager.h"

enum class Actions : uintptr_t
{
    CreatureAction_PlayerInteractionGreet = 0x012592D4,
    CreatureAction_StartBlocking = 0x012761CC,
    CombatAction_ControlledStrafeJump = 0x01276974,
    CombatAction_KickThingOnGround = 0x01277D3C,
    CreatureAction_InterruptableMidAttackAutoTurn = 0x012778CC,
    CreatureAction_UnsheatheItemFromInventory = 0x0125CCBC,
    CreatureAction_SheatheItemToInventory = 0x0125C83C
};

void NetPlayerManager::ReceiveNetPlayerAction(SLNet::BitStream& bsIn)
{
	int networkId = -1;
    uintptr_t vtableAddress = 0;

    bsIn.Read(networkId);
    bsIn.Read(vtableAddress);

    SLNet::BitStream bsOut;
    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        bsOut.Write((SLNet::MessageID)ID_PLAYER_ACTION);
        bsOut.Write(networkId);
        bsOut.Write(vtableAddress);
    }

    CThingPlayerCreature* creature = GetPlayerCreatureFromNetworkId(networkId);

    if (!creature)
		return;

    CThingCreatureBase& creatureBase = *reinterpret_cast<CThingCreatureBase*>(creature);
    void* actionBuffer = nullptr;

    switch (static_cast<Actions>(vtableAddress))
    {
    case Actions::CreatureAction_PlayerInteractionGreet:
    {
        int targetNetworkId = -1;
        bsIn.Read(targetNetworkId);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
            bsOut.Write(targetNetworkId);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = CreatureActions::CCreatureAction_PlayerInteractionGreet(creatureBase, target);
        break;
    }
	case Actions::CreatureAction_StartBlocking:
    {
		bool block = false;
        bsIn.Read(block);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
            bsOut.Write(block);

        CTCCombat* combat = reinterpret_cast<CTCCombat*>(reinterpret_cast<CThing*>(creature)->GetTC(TCI_COMBAT));

        if (!combat) {
            std::cout << "[NetPlayerManager::ReceiveNetPlayerAction]: !combat" << std::endl;
            return;
        }

        if (block)
        {
            actionBuffer = CreatureActions::CCreatureAction_StartBlocking(creatureBase);
            combat->SetBlocking();
        }
        else
        {
			combat->UnsetBlocking();
            return;
        }

        break;
    }
	case Actions::CombatAction_ControlledStrafeJump:
    {
        int targetNetworkId = -1;
        C3DVector requiredFacing, originalFacing;

        bsIn.Read(targetNetworkId);
        bsIn.Read(requiredFacing.X); bsIn.Read(requiredFacing.Y); bsIn.Read(requiredFacing.Z);
        bsIn.Read(originalFacing.X); bsIn.Read(originalFacing.Y); bsIn.Read(originalFacing.Z);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
        {
            bsOut.Write(targetNetworkId);
            bsOut.Write(requiredFacing.X); bsOut.Write(requiredFacing.Y); bsOut.Write(requiredFacing.Z);
			bsOut.Write(originalFacing.X); bsOut.Write(originalFacing.Y); bsOut.Write(originalFacing.Z);
        }

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = CreatureActions::CCombatAction_ControlledStrafeJump(creatureBase, target, requiredFacing, originalFacing);
        break;
    }
	case Actions::CombatAction_KickThingOnGround:
    {
        int targetNetworkId = -1;
        bsIn.Read(targetNetworkId);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
			bsOut.Write(targetNetworkId);

        CThing* target = (targetNetworkId != -1) ? reinterpret_cast<CThing*>(GetPlayerCreatureFromNetworkId(targetNetworkId)) : reinterpret_cast<CThing*>(creature);
        actionBuffer = CreatureActions::CCombatAction_KickThingOnGround(creatureBase, target);
        break;
    }
	case Actions::CreatureAction_InterruptableMidAttackAutoTurn:
    {
        int targetNetworkId = -1;
        C3DVector required_facing;
        long weaponIndex = 0;

        bsIn.Read(targetNetworkId);
        bsIn.Read(required_facing.X); bsIn.Read(required_facing.Y); bsIn.Read(required_facing.Z);
        bsIn.Read(weaponIndex);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
        {
            bsOut.Write(targetNetworkId);
            bsOut.Write(required_facing.X); bsOut.Write(required_facing.Y); bsOut.Write(required_facing.Z);
            bsOut.Write(weaponIndex);
		}

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
        actionBuffer = CreatureActions::CCreatureAction_InterruptableMidAttackAutoTurn(creatureBase, target, pweapon, required_facing, pmelee_ability);
        break;
    }
    case Actions::CreatureAction_UnsheatheItemFromInventory:
    {
        int itemIndex = -1;
        long interruption_priority = 0;

        bsIn.Read(itemIndex);
        bsIn.Read(interruption_priority);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
        {
            bsOut.Write(itemIndex);
            bsOut.Write(interruption_priority);
		}

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

        actionBuffer = CreatureActions::CCreatureAction_UnsheatheItemFromInventory(creatureBase, *unsheatheItem, pfollow_up_action, interruption_priority);
        break;
    }
	case Actions::CreatureAction_SheatheItemToInventory:
    {
        CCreatureActionBase* pfollow_up_action = nullptr;
        long interruption_group_id = 0;

		bsIn.Read(interruption_group_id);

        if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
			bsOut.Write(interruption_group_id);

        actionBuffer = CreatureActions::CCreatureAction_SheatheItemToInventory(creatureBase, pfollow_up_action, interruption_group_id);
        break;
    }
    default:
        return;
    }

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
        network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);

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

        void* vptr = *reinterpret_cast<void* const*>(&action);
        uintptr_t vtableAddress = reinterpret_cast<uintptr_t>(vptr);

        const void* locator =
            reinterpret_cast<void**>(vtableAddress)[-1];

        const std::uint8_t* typeDescriptor =
            *reinterpret_cast<const std::uint8_t* const*>(
                reinterpret_cast<const std::uint8_t*>(locator) + 0x0C);

        const char* rawName =
            reinterpret_cast<const char*>(typeDescriptor + 0x08);

        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_ACTION);
        bs.Write(networkId);
        bs.Write(vtableAddress);

        switch (static_cast<Actions>(vtableAddress))
        {
        case Actions::CreatureAction_PlayerInteractionGreet:
        {
            CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
            int targetNetworkId = GetNetworkIdFromThing(target);
            bs.Write(targetNetworkId);
            
            break;
        }
        case Actions::CreatureAction_StartBlocking:
        {
            bs.Write(true);
            break;
        }
        case Actions::CombatAction_ControlledStrafeJump:
        {
            CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
            int targetNetworkId = GetNetworkIdFromThing(target);

            C3DVector requiredFacing = *reinterpret_cast<const C3DVector*>(reinterpret_cast<uintptr_t>(&action) + 0x114);
            C3DVector originalFacing = *reinterpret_cast<const C3DVector*>(reinterpret_cast<uintptr_t>(&action) + 0x120);

            bs.Write(targetNetworkId);
            bs.Write(requiredFacing.X); bs.Write(requiredFacing.Y); bs.Write(requiredFacing.Z);
            bs.Write(originalFacing.X); bs.Write(originalFacing.Y); bs.Write(originalFacing.Z);
            
            break;
        }
        case Actions::CombatAction_KickThingOnGround:
        {
            CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
            int targetNetworkId = GetNetworkIdFromThing(target);
            bs.Write(targetNetworkId);

            break;
        }
        case Actions::CreatureAction_InterruptableMidAttackAutoTurn: // UNFINISHED (pmelee_ability)
        {
            CThing* target = *reinterpret_cast<CThing**>(reinterpret_cast<uintptr_t>(&action) + 0xAC);
            int targetNetworkId = GetNetworkIdFromThing(target);

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
        case Actions::CreatureAction_UnsheatheItemFromInventory:
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
        case Actions::CreatureAction_SheatheItemToInventory: // UNFINISHED (pfollow_up_action)
        {
            int interruption_group_id = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(&action) + 0x20);
			bs.Write(interruption_group_id);

            break;
        }
        default:
        {
            std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerAction]: Unknown: " << rawName << " - " << std::hex << vtableAddress << std::dec << std::endl;
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
        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_ACTION);
        bs.Write(networkId);
        bs.Write(Actions::CreatureAction_StartBlocking);
        bs.Write(false);

        if (localNetPlayer->GetNetworkId() == 0) {
            network->SendToAllClientsExcept(networkId, (const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
        }
        else {
            network->SendToHost((const char*)bs.GetData(), bs.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
        }
        });
}
