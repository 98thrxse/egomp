#include "MainGameComponent.h"

CMainGameComponent* CMainGameComponent::Get()
{
	return *(CMainGameComponent**)(0x13B86A0);
}

std::map<std::string, std::function<void()>> CMainGameComponent::postInitCallbacks;
std::map<std::string, std::function<void()>> CMainGameComponent::updateCallbacks;
std::map<std::string, std::function<void()>> CMainGameComponent::shutdownCallbacks;

void(__thiscall* CMainGameComponent::OInit)(CMainGameComponent*) = nullptr;
void __fastcall CMainGameComponent::HInit(CMainGameComponent* _this, void* _EDX)
{
	OInit(_this);
}

void(__thiscall* CMainGameComponent::OPostInit)(CMainGameComponent*) = nullptr;
void __fastcall CMainGameComponent::HPostInit(CMainGameComponent* _this, void* _EDX)
{
	OPostInit(_this);

	for (const auto& pair : postInitCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

void(__thiscall* CMainGameComponent::OUpdate)(CMainGameComponent*) = nullptr;
void __fastcall CMainGameComponent::HUpdate(CMainGameComponent* _this, void* _EDX)
{
	OUpdate(_this);

	for (const auto& pair : updateCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

void(__thiscall* CMainGameComponent::OShutdown)(CMainGameComponent*) = nullptr;
void __fastcall CMainGameComponent::HShutdown(CMainGameComponent* _this, void* _EDX)
{
	for (const auto& pair : shutdownCallbacks)
	{
		if (pair.second)
			pair.second();
	}

	OShutdown(_this);
}

CPlayerManager* CMainGameComponent::GetPlayerManager()
{
	return *(CPlayerManager**)((char*)this + 0x1C);
}

CWorld* CMainGameComponent::GetWorld()
{
	return *(CWorld**)((char*)this + 0x24);
}

CDisplayEngine* CMainGameComponent::GetDisplayEngine()
{
	return *(CDisplayEngine**)((char*)this + 0x28);
}

void CMainGameComponent::Hook()
{
	ADD_HOOK(0x004184BD, HInit, OInit);
	ADD_HOOK(0x00416953, HPostInit, OPostInit);
	ADD_HOOK(0x00418289, HUpdate, OUpdate);
	ADD_HOOK(0x004175E5, HShutdown, OShutdown);
}
