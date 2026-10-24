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
        netPlayerManager->SetNetPlayerParticle(networkId, 766, position, false);
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

        netPlayerManager->SetNetPlayerParticle(networkId, 767, {}, false);
        netPlayerManager->DestroyNetPlayer(networkId);
        });

    network->AddDestroyNetPlayersCallback("DestroyNetPlayers", [this]() {
        netPlayerManager->DestroyNetPlayers();
        });

	/* Motion */
    network->AddPlayerMovementCallback("PlayerMovement", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerMovement(bs);
        });

    network->AddPlayerRotationCallback("PlayerRotation", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerRotation(bs);
        });

	/* Stats */
    network->AddPlayerStatsCallback("PlayerStats", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerStats(bs);
        });

	/* Appearance */
    network->AddPlayerAppearanceCallback("PlayerAppearance", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerAppearance(bs);
        });

	/* Experience */
    network->AddPlayerExperienceCallback("PlayerExperience", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerExperience(bs);
        });

	/* Morph */
    network->AddPlayerMorphCallback("PlayerMorph", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerMorph(bs);
        });

	/* Weapons */
    network->AddPlayerWeaponsCallback("PlayerWeapons", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerWeapons(bs);
        });

	/* Actions */
    network->AddPlayerActionCallback("PlayerActions", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerAction(bs);
        });

    /* Hero */
    network->AddPlayerHeroCallback("PlayerHero", [this](BitStream& bs) {
        netPlayerManager->ReceiveNetPlayerHero(bs);
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

    /* Hero */
    network->RemovePlayerHeroCallback("PlayerHero");
}
