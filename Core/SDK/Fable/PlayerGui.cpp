#include "PlayerGui.h"

void(__thiscall* CPlayerGui::OdCPlayerGui)(CPlayerGui*) = nullptr;
void __fastcall CPlayerGui::HdCPlayerGui(CPlayerGui* _this, void* _EDX)
{
	OdCPlayerGui(_this);
}

void CPlayerGui::dCPlayerGui()
{
	OdCPlayerGui(this);
}

void CPlayerGui::Hook()
{
	ADD_HOOK(0x0043A570, HdCPlayerGui, OdCPlayerGui);
}