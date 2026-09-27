#include "Thing.h"

CTCBase* CThing::GetTC(ETCInterfaceType id)
{
	void* p_Components = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x44);

	typedef std::pair<ETCInterfaceType, CTCBase*>* (__thiscall* LowerBoundFn)(void*, const ETCInterfaceType*);
	auto* v3 = ((LowerBoundFn)0x0040F020)(p_Components, &id);

	auto* v4 = *reinterpret_cast<std::pair<ETCInterfaceType, CTCBase*>**>(reinterpret_cast<uintptr_t>(p_Components) + 4);

	if (v3 == v4 || id < v3->first)
		return v4->second;
	else
		return v3->second;
}

C3DVector* (__thiscall* CThing::OGetPos)(CThing*) = nullptr;
C3DVector* __fastcall CThing::HGetPos(CThing* _this, void* _EDX) {
	return OGetPos(_this);
}

C3DVector* CThing::GetPos() {
	return OGetPos(this);
}

int (__thiscall* CThing::OGetJoystickDeviceNumber)(CThing*) = nullptr;
int __fastcall CThing::HGetJoystickDeviceNumber(CThing* _this, void* _EDX) {
	// CRASH: if joystick is not 0 (AddRumble)
	if (IsMultiplayer()) {
		return 0;
	}

	return OGetJoystickDeviceNumber(_this);
}

CDefString* (__thiscall* CThing::OGetDefName)(CThing*, CDefString*) = nullptr;
CDefString* __fastcall CThing::HGetDefName(CThing* _this, void* _EDX, CDefString* result) {
	return OGetDefName(_this, result);
}

CDefString* CThing::GetDefName(CDefString* result) {
	return OGetDefName(this, result);
}

bool CThing::IsInLimbo()
{
    return (*reinterpret_cast<uint8_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x91
        ) & 0x20) != 0;
}

void(__thiscall* CThing::OSetInLimbo)(CThing*, bool) = nullptr;
void __fastcall CThing::HSetInLimbo(CThing* _this, void* _EDX, bool on) {
	OSetInLimbo(_this, on);
}

void CThing::SetInLimbo(bool on) {
	OSetInLimbo(this, on);
}

bool CThing::IsToKillOnLevelUnload()
{
    return (*reinterpret_cast<uint8_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x93
        ) & 0x04) != 0;
}

void(__thiscall* CThing::OSetToKillOnLevelUnload)(CThing*, bool) = nullptr;
void __fastcall CThing::HSetToKillOnLevelUnload(CThing* _this, void* _EDX, bool on) {
	OSetToKillOnLevelUnload(_this, on);
}

void CThing::SetToKillOnLevelUnload(bool on) {
	OSetToKillOnLevelUnload(this, on);
}

void CThing::Hook()
{
	ADD_HOOK(0x004C73D0, HGetPos, OGetPos);
	ADD_HOOK(0x004C7CA0, HGetJoystickDeviceNumber, OGetJoystickDeviceNumber);
	ADD_HOOK(0x004C7CC0, HGetDefName, OGetDefName);
	ADD_HOOK(0x004C9C40, HSetToKillOnLevelUnload, OSetToKillOnLevelUnload);
	ADD_HOOK(0x004C8CF0, HSetInLimbo, OSetInLimbo);
}
