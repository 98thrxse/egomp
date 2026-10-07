#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupNetworkPlayerManagerCallbacks()
{
    /* Lifecycle */
    network->AddCreateNetPlayerCallback("CreateNetPlayer", [this](BitStream& bs) {
        int networkId = -1;
        int defGlobalIndex = 0;
        C3DVector position = {};
        float facingAngleXY = 0;

        bs.Read(networkId);
        bs.Read(defGlobalIndex);
        bs.Read(position);
        bs.Read(facingAngleXY);

        netPlayerManager->CreateNetPlayer(networkId, defGlobalIndex, position, facingAngleXY);
        });

    network->AddCreateNetPlayersCallback("CreateNetPlayers", [this](BitStream& bs) {
        netPlayerManager->CreateNetPlayers(bs);
        });

    network->AddDestroyLocalNetPlayerCallback("DestroyLocalNetPlayer", [this]() {
        netPlayerManager->DestroyLocalNetPlayer();
        });

    network->AddDestroyNetPlayerCallback("DestroyNetPlayer", [this](BitStream& bs) {
        int networkId = -1;
        bs.Read(networkId);

        netPlayerManager->DestroyNetPlayer(networkId);
        });

    network->AddDestroyNetPlayersCallback("DestroyNetPlayers", [this]() {
        netPlayerManager->DestroyNetPlayers();
        });

	/* Motion */
    network->AddPlayerMovementCallback("PlayerMovement", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector remotePosition = {};
        C3DVector movementAcceleration = {};

        bs.Read(networkId);
        bs.Read(remotePosition);
        bs.Read(movementAcceleration);

        netPlayerManager->ReceiveNetPlayerMovement(networkId, remotePosition, movementAcceleration);
        });

    network->AddPlayerRotationCallback("PlayerRotation", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector up = {};
        C3DVector forward = {};

        bs.Read(networkId);
        bs.Read(up);
        bs.Read(forward);

        netPlayerManager->ReceiveNetPlayerRotation(networkId, up, forward);
        });

	/* Stats */
    network->AddPlayerStatsCallback("PlayerStats", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerStats(networkId, bs);
        });

	/* Appearance */
    network->AddPlayerAppearanceCallback("PlayerAppearance", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerAppearance(networkId, bs);
        });

	/* Experience */
    network->AddPlayerExperienceCallback("PlayerExperience", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerExperience(networkId, bs);
        });

	/* Morph */
    network->AddPlayerMorphCallback("PlayerMorph", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerMorph(networkId, bs);
        });

	/* Weapons */
    network->AddPlayerWeaponsCallback("PlayerWeapons", [this](BitStream& bs) {
        int networkId = -1;
        long weapon_def_index = 0;

        bs.Read(networkId);
        bs.Read(weapon_def_index);

        netPlayerManager->ReceiveNetPlayerWeapons(networkId, weapon_def_index);
        });

	/* Actions */
    network->AddPlayerActionCallback("PlayerActions", [this](BitStream& bs) {
        int networkId = -1;
        uintptr_t actionOffset = 0;

        bs.Read(networkId);
        bs.Read(actionOffset);

        netPlayerManager->ReceiveNetPlayerAction(networkId, actionOffset, bs);
        });
}

void NetMainGameComponent::ClearNetworkPlayerManagerCallbacks()
{
	/* Lifecycle */
    network->RemoveCreateNetPlayerCallback("CreateNetPlayer");
    network->RemoveCreateNetPlayersCallback("CreateNetPlayers");

    network->RemoveDestroyLocalNetPlayerCallback("DestroyLocalNetPlayer");
    network->RemoveDestroyNetPlayerCallback("DestroyNetPlayer");
    network->RemoveDestroyNetPlayersCallback("DestroyNetPlayers");

	/* Motion */
    network->RemovePlayerMovementCallback("PlayerMovement");
    network->RemovePlayerRotationCallback("PlayerRotation");

	/* Stats */
    network->RemovePlayerStatsCallback("PlayerStats");

	/* Appearance */
    network->RemovePlayerAppearanceCallback("PlayerAppearance");

	/* Experience */
    network->RemovePlayerExperienceCallback("PlayerExperience");

	/* Morph */
    network->RemovePlayerMorphCallback("PlayerMorph");

	/* Weapons */
    network->RemovePlayerWeaponsCallback("PlayerWeapons");

	/* Actions */
    network->RemovePlayerActionCallback("PlayerActions");
}
