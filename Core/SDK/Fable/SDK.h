#pragma once

#include <iostream>

#include <MinHook/include/MinHook.h>

#include "../Utils/Hook.h"
#include "../Utils/Window.h"

#include "Base.h"
#include "BaseClass.h"
#include "ParentDefClassBase.h"
#include "CharString.h"
#include "DefString.h"
#include "DefStringTable.h"
#include "DefinitionManager.h"
#include "3DVector.h"
#include "Game.h"
#include "MainGameComponent.h"
#include "GamePlayerInterface.h"
#include "World.h"
#include "WorldMap.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Thing.h"
#include "ThingPhysical.h"
#include "ThingGameObject.h"
#include "ThingCreatureBase.h"
#include "ThingPlayerCreature.h"
#include "ThingPlayerCreatureInit.h"
#include "CoopSpirit.h"
#include "GameEvent.h"
#include "PhysicsBase.h"
#include "PhysicsControlled.h"
#include "PhysicsStandard.h"
#include "RightHandedSet.h"
#include "CreatureActionBase.h"
#include "CombatActionBase.h"
#include "DefPointer.h"
#include "DefPointeeBase.h"
#include "Stealth.h"
#include "GameScriptInterface.h"
#include "HeroStats.h"
#include "HeroMorph.h"
#include "HeroExperience.h"
#include "HeroAttachableAppearanceModifiers.h"
#include "AppearanceMorphBase.h"
#include "DisplayEngine.h"
#include "IEngine.h"
#include "InventoryBase.h"
#include "InventoryStats.h"
#include "InventoryWeapons.h"
#include "InventoryItem.h"
#include "Component.h"
#include "BaseIntelligentPointer.h"
#include "DefIndex.h"
#include "BaseObject.h"
#include "ThingObject.h"
#include "Weapon.h"
#include "ThingHolySite.h"
#include "DParticleEmitter.h"
#include "Hero.h"
#include "Combat.h"
#include "GraphicAppearance.h"
#include "GameTimeManager.h"
#include "Actions.h"
#include "SystemManager.h"
#include "InputManager.h"
#include "PlayerGui.h"

class SDK
{
public:
	SDK();
	static SDK& GetInstance();
private:
	static HWND WINAPI HGetForegroundWindow();
};
