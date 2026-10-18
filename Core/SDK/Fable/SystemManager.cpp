#include "SystemManager.h"

CSystemManager* (__fastcall* CSystemManager::OGFGetSystemManager)() = nullptr;
CSystemManager* __fastcall CSystemManager::HGFGetSystemManager()
{
	return OGFGetSystemManager();
}

CSystemManager* CSystemManager::GFGetSystemManager()
{
	return OGFGetSystemManager();
}

bool(__thiscall* CSystemManager::OIsApplicationActive)(CSystemManager*) = nullptr;
bool __fastcall CSystemManager::HIsApplicationActive(CSystemManager* _this, void* _EDX)
{

    return OIsApplicationActive(_this);
}

void(__thiscall* CSystemManager::OUpdateActive)(CSystemManager*) = nullptr;
void __fastcall CSystemManager::HUpdateActive(CSystemManager* _this, void* _EDX)
{
    OUpdateActive(_this);
}

void CSystemManager::Hook()
{
	ADD_HOOK(0x009A4EC0, HGFGetSystemManager, OGFGetSystemManager);
	ADD_HOOK(0x009A57B0, HIsApplicationActive, OIsApplicationActive);
    ADD_HOOK(0x009A6370, HUpdateActive, OUpdateActive);
}
