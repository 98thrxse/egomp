#include "ThingPlayerCreature.h"

std::map<std::string, std::function<void()>> CThingPlayerCreature::resolveMovementAccelerationCallbacks;
std::map<std::string, std::function<void()>> CThingPlayerCreature::resolveFacingDirectionCallbacks;

CThingPlayerCreature* (__fastcall* CThingPlayerCreature::OCreate)(long, C3DVector const&, long, CThingPlayerCreatureInit const &) = nullptr;
CThingPlayerCreature* __fastcall CThingPlayerCreature::HCreate(long global_def_index, C3DVector const& pos, long player, CThingPlayerCreatureInit const &init)
{
	return OCreate(global_def_index, pos, player, init);
}

CThingPlayerCreature* CThingPlayerCreature::Create(long global_def_index, C3DVector const& pos, long player, CThingPlayerCreatureInit const &init)
{
	return OCreate(global_def_index, pos, player, init);
}

void (__thiscall* CThingPlayerCreature::OResolveMovementAcceleration)(CThingPlayerCreature*) = nullptr;
void __fastcall CThingPlayerCreature::HResolveMovementAcceleration(CThingPlayerCreature* _this, void* _EDX)
{
	OResolveMovementAcceleration(_this);

	for (const auto& pair : resolveMovementAccelerationCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

void(__thiscall* CThingPlayerCreature::OResolveFacingDirection)(CThingPlayerCreature*) = nullptr;
void __fastcall CThingPlayerCreature::HResolveFacingDirection(CThingPlayerCreature* _this, void* _EDX)
{
	OResolveFacingDirection(_this);

	for (const auto& pair : resolveFacingDirectionCallbacks)
	{
		if (pair.second)
			pair.second();
	}
}

bool(__thiscall* CThingPlayerCreature::OWorldUpdate)(CThingPlayerCreature*) = nullptr;
bool __fastcall CThingPlayerCreature::HWorldUpdate(CThingPlayerCreature* _this, void* _EDX)
{
	return OWorldUpdate(_this);
}

void(__thiscall* CThingPlayerCreature::OUpdateWalkingControlForces)(CThingPlayerCreature*) = nullptr;
void __fastcall CThingPlayerCreature::HUpdateWalkingControlForces(CThingPlayerCreature* _this, void* _EDX)
{
	OUpdateWalkingControlForces(_this);
}

void(__thiscall* CThingPlayerCreature::OApplyRelativeMovementAcceleration)(CThingPlayerCreature*, C3DVector const&, EGameAction) = nullptr;
void __fastcall CThingPlayerCreature::HApplyRelativeMovementAcceleration(CThingPlayerCreature* _this, void* _EDX, C3DVector const& vect, EGameAction game_action)
{
	OApplyRelativeMovementAcceleration(_this, vect, game_action);
}

char(__thiscall* CThingPlayerCreature::OSetActionForMelee)(CThingPlayerCreature*, CCreatureAbilityDef const&) = nullptr;
char __fastcall CThingPlayerCreature::HSetActionForMelee(CThingPlayerCreature* _this, void* _EDX, CCreatureAbilityDef const& arg)
{
	return OSetActionForMelee(_this, arg);
}


char CThingPlayerCreature::SetActionForMelee(CCreatureAbilityDef const& arg)
{
	return OSetActionForMelee(this, arg);
}

char(__thiscall* CThingPlayerCreature::OSetPlayerCreatureActionForMelee)(CThingPlayerCreature*, ECombatZone, C3DVector const&, CThing*, CCreatureAbilityDef const&) = nullptr;
char __fastcall CThingPlayerCreature::HSetPlayerCreatureActionForMelee(CThingPlayerCreature* _this, void* _EDX, ECombatZone combatZone, C3DVector const& vector, CThing* thing, CCreatureAbilityDef const& abilityDef)
{
	return OSetPlayerCreatureActionForMelee(_this, combatZone, vector, thing, abilityDef);
}

char CThingPlayerCreature::SetPlayerCreatureActionForMelee(ECombatZone combatZone, C3DVector const& vector, CThing* thing, CCreatureAbilityDef const& abilityDef)
{
	return OSetPlayerCreatureActionForMelee(this, combatZone, vector, thing, abilityDef);
}

void CThingPlayerCreature::Hook()
{
	ADD_HOOK(0x006AC910, HCreate, OCreate);
	ADD_HOOK(0x006AB770, HResolveMovementAcceleration, OResolveMovementAcceleration);
	ADD_HOOK(0x006AB820, HResolveFacingDirection, OResolveFacingDirection);
	ADD_HOOK(0x006AD260, HUpdateWalkingControlForces, OUpdateWalkingControlForces);
	ADD_HOOK(0x006AD3C0, HApplyRelativeMovementAcceleration, OApplyRelativeMovementAcceleration);
	ADD_HOOK(0x006AABE0, HSetActionForMelee, OSetActionForMelee);
	ADD_HOOK(0x006AA720, HSetPlayerCreatureActionForMelee, OSetPlayerCreatureActionForMelee);
	ADD_HOOK(0x006AD9D0, HWorldUpdate, OWorldUpdate);
}
