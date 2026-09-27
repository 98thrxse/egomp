#include "PlayerManager.h"

void(__thiscall* CPlayerManager::OCreatePlayer)(CPlayerManager*, long) = nullptr;
void __fastcall CPlayerManager::HCreatePlayer(CPlayerManager* _this, void* _EDX, long player_number)
{
	OCreatePlayer(_this, player_number);
}

CPlayer* (__thiscall* CPlayerManager::OGetPlayer)(CPlayerManager*, long) = nullptr;
CPlayer* __fastcall CPlayerManager::HGetPlayer(CPlayerManager* _this, void* _EDX, long player_number)
{
	return OGetPlayer(_this, player_number);
}

bool (__thiscall* CPlayerManager::OIsMultiplayerGameActive)(CPlayerManager*) = nullptr;
bool __fastcall CPlayerManager::HIsMultiplayerGameActive(CPlayerManager* _this, void* _EDX) {
	// CRASH: disable native mp cut features
	if (IsMultiplayer()) {
		return false;
	}

	return OIsMultiplayerGameActive(_this);
}

void CPlayerManager::CreatePlayer(long player_number)
{
	OCreatePlayer(this, player_number);
}

CPlayer* CPlayerManager::GetPlayer(long player_number)
{
	return OGetPlayer(this, player_number);
}

void CPlayerManager::Hook()
{
	ADD_HOOK(0x0044A1A0, HCreatePlayer, OCreatePlayer);
	ADD_HOOK(0x004498C0, HGetPlayer, OGetPlayer);
	ADD_HOOK(0x00449D20, HIsMultiplayerGameActive, OIsMultiplayerGameActive);
}