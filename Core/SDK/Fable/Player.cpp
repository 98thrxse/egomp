#include "Player.h"

void(__thiscall* CPlayer::OInitCharacterAs)(CPlayer*, CCharString const &) = nullptr;
void __fastcall CPlayer::HInitCharacterAs(CPlayer* _this, void* _EDX, CCharString const &def_name)
{
    OInitCharacterAs(_this, def_name);
}

void CPlayer::InitCharacterAs(CCharString const &def_name)
{
    OInitCharacterAs(this, def_name);
}

void(__thiscall* CPlayer::OCreateCharacter)(CPlayer*, CCharString const &) = nullptr;
void __fastcall CPlayer::HCreateCharacter(CPlayer* _this, void* _EDX, CCharString const &def_name)
{
    OCreateCharacter(_this, def_name);
}

void CPlayer::CreateCharacter(CCharString const& def_name)
{
    OCreateCharacter(this, def_name);
}

CThingPlayerCreature* (__thiscall* CPlayer::OGetPControlledCreature)(CPlayer*) = nullptr;
CThingPlayerCreature* __fastcall CPlayer::HGetPControlledCreature(CPlayer* _this, void* _EDX) {
    return OGetPControlledCreature(_this);
}

CThingPlayerCreature* CPlayer::GetPControlledCreature() {
    return OGetPControlledCreature(this);
}

void (__thiscall* CPlayer::OSetControlledCreature)(CPlayer*, CThingPlayerCreature*) = nullptr;
void __fastcall CPlayer::HSetControlledCreature(CPlayer* _this, void* _EDX, CThingPlayerCreature* creature) {
    OSetControlledCreature(_this, creature);
}

void CPlayer::SetControlledCreature(CThingPlayerCreature* creature) {
    OSetControlledCreature(this, creature);
}

void(__thiscall* CPlayer::OInitInterfaces)(CPlayer*) = nullptr;
void __fastcall CPlayer::HInitInterfaces(CPlayer* _this, void* _EDX)
{
    OInitInterfaces(_this);
}

void CPlayer::InitInterfaces()
{
    OInitInterfaces(this);
}

void(__thiscall* CPlayer::OUninitialise)(CPlayer*) = nullptr;
void __fastcall CPlayer::HUninitialise(CPlayer* _this, void* _EDX)
{
    OUninitialise(_this);
}

void CPlayer::Uninitialise()
{
    OUninitialise(this);
}

void(__thiscall* CPlayer::OUninitCharacter)(CPlayer*) = nullptr;
void __fastcall CPlayer::HUninitCharacter(CPlayer* _this, void* _EDX)
{
    OUninitCharacter(_this);
}

void CPlayer::UninitCharacter()
{
    OUninitCharacter(this);
}

bool(__thiscall* CPlayer::OLocateCharacterStartHolySite)(CPlayer*, CThingHolySite**) = nullptr;
bool __fastcall CPlayer::HLocateCharacterStartHolySite(
    CPlayer* _this,
    void* _EDX,
    CThingHolySite** site)
{
    return OLocateCharacterStartHolySite(_this, site);
}

bool CPlayer::LocateCharacterStartHolySite(CThingHolySite** site)
{
    return OLocateCharacterStartHolySite(this, site);
}

void CPlayer::Hook()
{
    ADD_HOOK(0x0048A070, HInitCharacterAs, OInitCharacterAs);
    ADD_HOOK(0x00489D40, HCreateCharacter, OCreateCharacter);
    ADD_HOOK(0x00487DC0, HGetPControlledCreature, OGetPControlledCreature);
    ADD_HOOK(0x00487CF0, HSetControlledCreature, OSetControlledCreature);
    ADD_HOOK(0x00488D10, HInitInterfaces, OInitInterfaces);
    ADD_HOOK(0x00487AF0, HUninitialise, OUninitialise);
    ADD_HOOK(0x00487BD0, HUninitCharacter, OUninitCharacter);
    ADD_HOOK(0x00488B20, HLocateCharacterStartHolySite, OLocateCharacterStartHolySite);
}
