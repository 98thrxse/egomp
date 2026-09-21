#include "Weapon.h"

bool(__thiscall* CTCWeapon::OIsMeleeWeapon)(CTCWeapon*) = nullptr;
bool __fastcall CTCWeapon::HIsMeleeWeapon(CTCWeapon* _this, void* _EDX) {
	return OIsMeleeWeapon(_this);
}

bool CTCWeapon::IsMeleeWeapon() {
	return OIsMeleeWeapon(this);
}

bool(__thiscall* CTCWeapon::OIsProjectileWeapon)(CTCWeapon*) = nullptr;
bool __fastcall CTCWeapon::HIsProjectileWeapon(CTCWeapon* _this, void* _EDX) {
	return OIsProjectileWeapon(_this);
}

bool CTCWeapon::IsProjectileWeapon() {
	return OIsProjectileWeapon(this);
}

void CTCWeapon::Hook()
{
	ADD_HOOK(0x005DAA00, HIsMeleeWeapon, OIsMeleeWeapon);
	ADD_HOOK(0x005DAA40, HIsProjectileWeapon, OIsProjectileWeapon);
}

