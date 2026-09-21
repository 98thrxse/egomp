#include "NetPlayerManager.h"

void NetPlayerManager::ReceiveNetPlayerWeapons(int networkId, SLNet::BitStream& bsIn)
{
    long weapon_def_index = 0;
    bsIn.Read(weapon_def_index);

    if (localNetPlayer && localNetPlayer->GetNetworkId() == 0)
    {
        SLNet::BitStream bsOut;
        bsOut.Write((SLNet::MessageID)ID_PLAYER_WEAPONS);
        bsOut.Write(networkId);
        bsOut.Write(weapon_def_index);

        network->SendToAllClientsExcept(networkId, (const char*)bsOut.GetData(), bsOut.GetNumberOfBytesUsed(), HIGH_PRIORITY, RELIABLE_ORDERED);
    }

    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
        return;

    CTCInventoryWeapons* inventoryWeapons = reinterpret_cast<CTCInventoryWeapons*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY_WEAPONS)
        );

    if (!inventoryWeapons) {
        std::cout << "[NetPlayerManager::ReceiveNetPlayerWeapons]: !inventoryWeapons" << std::endl;
        return;
    }

    if (reinterpret_cast<NInventory::CTCInventoryBase*>(inventoryWeapons)->GetNumberOfItemsOfTypeInInventory(weapon_def_index) == 0)
    {
        CCharString scriptName("");
        creature->CreateAndAddObjectToInventory(
            weapon_def_index,
            -1,
            true,
            scriptName);
    }

    inventoryWeapons->SetThingAsActiveWeapon(weapon_def_index, 0);
}

void NetPlayerManager::BroadcastLocalNetPlayerWeapons(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerWeapons]: !creature" << std::endl;
        return;
    }

    CTCInventoryWeapons* inventoryWeapons = reinterpret_cast<CTCInventoryWeapons*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY_WEAPONS)
        );

    if (!inventoryWeapons) {
        std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerWeapons]: !inventoryWeapons" << std::endl;
        return;
    }

    inventoryWeapons->AddSetThingAsActiveWeaponCallback(
        "SetThingAsActiveWeaponCallback" + std::to_string(networkId),
        [this, networkId](CTCInventoryWeapons* _this, long weapon_def_index)
        {
            CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

            if (!creature) {
                std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerWeapons]: !creature" << std::endl;
                return;
            }

            CTCInventoryWeapons* inventoryWeapons = reinterpret_cast<CTCInventoryWeapons*>(
                reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY_WEAPONS)
                );

            if (!inventoryWeapons) {
                std::cout << "[NetPlayerManager::BroadcastLocalNetPlayerWeapons]: !inventoryWeapons" << std::endl;
                return;
            }

            if (_this != inventoryWeapons)
                return;

            SLNet::BitStream bs;
            bs.Write((SLNet::MessageID)ID_PLAYER_WEAPONS);
            bs.Write(networkId);
            bs.Write(weapon_def_index);

            if (localNetPlayer->GetNetworkId() == 0)
            {
                network->SendToAllClientsExcept(
                    networkId,
                    (const char*)bs.GetData(),
                    bs.GetNumberOfBytesUsed(),
                    HIGH_PRIORITY,
                    RELIABLE_ORDERED
                );
            }
            else
            {
                network->SendToHost(
                    (const char*)bs.GetData(),
                    bs.GetNumberOfBytesUsed(),
                    HIGH_PRIORITY,
                    RELIABLE_ORDERED
                );
            }
        }
    );
}

void NetPlayerManager::BroadcastNetPlayerWeapons(int networkId)
{
    CThingPlayerCreature* creature = GetCreatureFromNetworkId(networkId);

    if (!creature)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerWeapons]: !creature" << std::endl;
        return;
    }

    CTCInventoryWeapons* inventoryWeapons = reinterpret_cast<CTCInventoryWeapons*>(
        reinterpret_cast<CThing*>(creature)->GetTC(TCI_INVENTORY_WEAPONS)
        );

    if (!inventoryWeapons)
    {
        std::cout << "[NetPlayerManager::BroadcastNetPlayerWeapons]: !inventoryWeapons" << std::endl;
        return;
    }

    auto broadcastWeapon = [&](CThing* weapon)
    {
        if (!weapon)
        {
            std::cout << "[NetPlayerManager::BroadcastNetPlayerWeapons]: !weapon" << std::endl;
            return;
        }

		long weapon_def_index = weapon->DefGlobalIndex;

        SLNet::BitStream bs;
        bs.Write((SLNet::MessageID)ID_PLAYER_WEAPONS);
        bs.Write(networkId);
        bs.Write(weapon_def_index);

        if (localNetPlayer->GetNetworkId() == 0)
        {
            network->SendToAllClientsExcept(
                networkId,
                (const char*)bs.GetData(),
                bs.GetNumberOfBytesUsed(),
                HIGH_PRIORITY,
                RELIABLE_ORDERED
            );
        }
        else
        {
            network->SendToHost(
                (const char*)bs.GetData(),
                bs.GetNumberOfBytesUsed(),
                HIGH_PRIORITY,
                RELIABLE_ORDERED
            );
        }
    };

    broadcastWeapon(reinterpret_cast<CThing*>(inventoryWeapons->PActiveMeleeWeapon.GetPItem()));
    broadcastWeapon(reinterpret_cast<CThing*>(inventoryWeapons->PActiveRangedWeapon.GetPItem()));
}

