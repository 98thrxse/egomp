#include "NetMainGameComponent.h"

void NetMainGameComponent::SetupPlayerManagerCallbacks()
{
    /* Lifecycle */
    network->AddCreateLocalNetPlayerCallback("CreateLocalNetPlayer", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector position = {};
        float facingAngleXY = 0;

        bs.Read(networkId);
        bs.Read(position);
        bs.Read(facingAngleXY);

        netPlayerManager->CreateLocalNetPlayer(networkId, position, facingAngleXY);
        });

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
    network->AddNetPlayerMovementCallback("NetPlayerMovement", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector remotePosition = {};
        C3DVector movementAcceleration = {};

        bs.Read(networkId);
        bs.Read(remotePosition);
        bs.Read(movementAcceleration);

        netPlayerManager->ReceiveNetPlayerMovement(networkId, remotePosition, movementAcceleration);
        });

    network->AddNetPlayerRotationCallback("NetPlayerRotation", [this](BitStream& bs) {
        int networkId = -1;
        C3DVector up = {};
        C3DVector forward = {};

        bs.Read(networkId);
        bs.Read(up);
        bs.Read(forward);

        netPlayerManager->ReceiveNetPlayerRotation(networkId, up, forward);
        });

	/* Stats */
    network->AddNetPlayerStatsCallback("NetPlayerStats", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerStats(networkId, bs);
        });

	/* Appearance */
    network->AddNetPlayerAppearanceCallback("NetPlayerAppearance", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerAppearance(networkId, bs);
        });

	/* Experience */
    network->AddNetPlayerExperienceCallback("NetPlayerExperience", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerExperience(networkId, bs);
        });

	/* Morph */
    network->AddNetPlayerMorphCallback("NetPlayerMorph", [this](BitStream& bs) {
        int networkId = -1;

        bs.Read(networkId);

        netPlayerManager->ReceiveNetPlayerMorph(networkId, bs);
        });

	/* Weapons */
    network->AddNetPlayerWeaponsCallback("NetPlayerWeapons", [this](BitStream& bs) {
        int networkId = -1;
        long weapon_def_index = 0;

        bs.Read(networkId);
        bs.Read(weapon_def_index);

        netPlayerManager->ReceiveNetPlayerWeapons(networkId, weapon_def_index);
        });

	/* Actions */
    network->AddNetPlayerActionCallback("NetPlayerAction", [this](BitStream& bs) {
        int networkId = -1;
        uintptr_t actionOffset = 0;

        bs.Read(networkId);
        bs.Read(actionOffset);

        netPlayerManager->ReceiveNetPlayerAction(networkId, actionOffset, bs);
        });
}

void NetMainGameComponent::ClearPlayerManagerCallbacks()
{
	/* Lifecycle */
    network->RemoveCreateLocalNetPlayerCallback("CreateLocalNetPlayer");
    network->RemoveCreateNetPlayerCallback("CreateNetPlayer");
    network->RemoveCreateNetPlayersCallback("CreateNetPlayers");

    network->RemoveDestroyLocalNetPlayerCallback("DestroyLocalNetPlayer");
    network->RemoveDestroyNetPlayerCallback("DestroyNetPlayer");
    network->RemoveDestroyNetPlayersCallback("DestroyNetPlayers");

	/* Motion */
    network->RemoveNetPlayerMovementCallback("NetPlayerMovement");
    network->RemoveNetPlayerRotationCallback("NetPlayerRotation");

	/* Stats */
    network->RemoveNetPlayerStatsCallback("NetPlayerStats");

	/* Appearance */
    network->RemoveNetPlayerAppearanceCallback("NetPlayerAppearance");

	/* Experience */
    network->RemoveNetPlayerExperienceCallback("NetPlayerExperience");

	/* Morph */
    network->RemoveNetPlayerMorphCallback("NetPlayerMorph");

	/* Weapons */
    network->RemoveNetPlayerWeaponsCallback("NetPlayerWeapons");

	/* Actions */
    network->RemoveNetPlayerActionCallback("NetPlayerAction");
}
