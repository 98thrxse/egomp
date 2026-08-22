#include "SDK.h"

SDK& SDK::GetInstance()
{
	static SDK instance;
	return instance;
}

void* (__cdecl* SDK::OGameMalloc)(unsigned int size) = nullptr;
void* __cdecl SDK::HGameMalloc(unsigned int size)
{
	return OGameMalloc(size);
}

void* SDK::GameMalloc(unsigned int size)
{
	return OGameMalloc(size);
}

C3DVector* SDK::GOverridePlayerStartPos = (C3DVector*)(0x13B8650);

SDK::SDK()
{
	INIT_HOOKS();
	ADD_HOOK(0xBFEA1A, HGameMalloc, OGameMalloc);

	CTCBase::Hook();
	CBaseClass::Hook();
	CCharString::Hook();
	CDefString::Hook();
	CDefStringTable::Hook();
	CDefinitionManager::Hook();
	C3DVector::Hook();
	CGame::Hook();
	CMainGameComponent::Hook();
	CGamePlayerInterface::Hook();
	CPlayerManager::Hook();
	CPlayer::Hook();
	CThing::Hook();
	CThingPhysical::Hook();
	CThingGameObject::Hook();
	CThingCreatureBase::Hook();
	CThingPlayerCreature::Hook();
	CThingPlayerCreatureInit::Hook();
	CTCCoopSpirit::Hook();
	CWorld::Hook();
	CWorldMap::Hook();
	CGameEvent::Hook();
	CTCPhysicsBase::Hook();
	CTCPhysicsControlled::Hook();
	CTCPhysicsStandard::Hook();
	CRightHandedSet::Hook();
	CCreatureActionBase::Hook();
	CCombatActionBase::Hook();
	CDefPointer::Hook();
	CDefPointeeBase::Hook();
	CTCStealth::Hook();
	CGameScriptInterface::Hook();
	CTCInventoryStats::Hook();
	CTCHeroStats::Hook();
	CTCHeroMorph::Hook();
	CTCHeroExperience::Hook();

	CCreatureAction_PlayerInteractionGreet::Hook();
	CCreatureAction_StartBlocking::Hook();
	CCreatureAction_InterruptableMidAttackAutoTurn::Hook();
	CCreatureAction_UnsheatheItemFromInventory::Hook();
	CCreatureAction_SheatheItemToInventory::Hook();

	CCombatAction_KickThingOnGround::Hook();
	CCombatAction_ControlledStrafeJump::Hook();
};
