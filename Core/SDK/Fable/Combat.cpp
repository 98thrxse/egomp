#include "Combat.h"

std::map<std::string, std::function<void()>> CTCCombat::unsetBlockingCallbacks;

void(__thiscall* CTCCombat::OSetBlocking)(CTCCombat*) = nullptr;
void __fastcall CTCCombat::HSetBlocking(CTCCombat* _this, void* _EDX)
{
	OSetBlocking(_this);
}

void CTCCombat::SetBlocking()
{
	OSetBlocking(this);
}

void(__thiscall* CTCCombat::OUnsetBlocking)(CTCCombat*) = nullptr;
void __fastcall CTCCombat::HUnsetBlocking(CTCCombat* _this, void* _EDX)
{
	for (const auto& pair : unsetBlockingCallbacks)
	{
		if (pair.second)
			pair.second();
	}

	OUnsetBlocking(_this);
}

void CTCCombat::UnsetBlocking()
{
	OUnsetBlocking(this);
}

void CTCCombat::Hook()
{
	ADD_HOOK(0x007337E0, HSetBlocking, OSetBlocking);
	ADD_HOOK(0x007338A0, HUnsetBlocking, OUnsetBlocking);
}
