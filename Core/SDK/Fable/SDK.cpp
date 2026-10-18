#include "SDK.h"

SDK& SDK::GetInstance()
{
	static SDK instance;
	return instance;
}

HWND WINAPI SDK::HGetForegroundWindow()
{
	if (IsMultiplayer())
	{
		HWND foreground = OGetForegroundWindow();
		CSystemManager* systemManager = CSystemManager::GFGetSystemManager();
		HWND gameWindow = *reinterpret_cast<HWND*>(systemManager + 0x94);
		return gameWindow ? gameWindow : foreground;
	}

	return OGetForegroundWindow();
}

SDK::SDK()
{
	INIT_HOOKS();

	ADD_HOOK(
		reinterpret_cast<std::uintptr_t>(&GetForegroundWindow),
		HGetForegroundWindow,
		OGetForegroundWindow
	);

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
	CTCHeroStats::Hook();
	CTCHeroMorph::Hook();
	CTCHeroExperience::Hook();
	CTCHeroAttachableAppearanceModifiers::Hook();
	CParentDefClassBase::Hook();
	CTCAppearanceMorphBase::Hook();
	CDisplayEngine::Hook();
	CIEngine::Hook();
	NInventory::CTCInventoryBase::Hook();
	CTCInventoryStats::Hook();
	CTCInventoryWeapons::Hook();
	CTCInventoryItem::Hook();
	NUISystem::CComponent::Hook();
	CBaseIntelligentPointer::Hook();
	CDefIndex::Hook();
	CBaseObject::Hook();
	CThingObject::Hook();
	CTCWeapon::Hook();
	CThingHolySite::Hook();
	CTCDParticleEmitter::Hook();
	CTCHero::Hook();
	CTCCombat::Hook();
	NGraphicAppearance::CTCGraphicAppearance::Hook();
	CGameTimeManager::Hook();
	CSystemManager::Hook();
	CInputManager::Hook();
};
