#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

#include "Player.h"

class CPlayerManager
{
public:
	char pad[0x2C];

	void CreatePlayer(long player_number);
	CPlayer* GetPlayer(long player_number);

	static void Hook();

private:
	static void (__thiscall* OCreatePlayer)(CPlayerManager*, long player_number);
	static void __fastcall HCreatePlayer(CPlayerManager* _this, void* _EDX, long player_number);

	static CPlayer* (__thiscall* OGetPlayer)(CPlayerManager*, long player_number);
	static CPlayer* __fastcall HGetPlayer(CPlayerManager* _this, void* _EDX, long player_number);

	static bool (__thiscall* OIsMultiplayerGameActive)(CPlayerManager*);
	static bool __fastcall HIsMultiplayerGameActive(CPlayerManager*, void* _EDX);
};