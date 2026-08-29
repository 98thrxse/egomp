#pragma once

#include <iostream>

#include <MinHook/include/MinHook.h>

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
#include "InventoryStats.h"
#include "HeroStats.h"
#include "HeroMorph.h"
#include "HeroExperience.h"
#include "HeroAttachableAppearanceModifiers.h"
#include "AppearanceMorphBase.h"
#include "DisplayEngine.h"
#include "IEngine.h"

#include "CreatureActions/CreatureAction_SheatheItemToInventory.h"
#include "CreatureActions/CreatureAction_UnsheatheItemFromInventory.h"
#include "CreatureActions/CreatureAction_InterruptableMidAttackAutoTurn.h"
#include "CreatureActions/CreatureAction_PlayerInteractionGreet.h"
#include "CreatureActions/CreatureAction_StartBlocking.h"

#include "CombatActions/CombatAction_KickThingOnGround.h"
#include "CombatActions/CombatAction_ControlledStrafeJump.h"

class SDK
{
public:
	SDK();
	static SDK& GetInstance();
	static void* GameMalloc(unsigned int size);
	static C3DVector* GOverridePlayerStartPos;

private:
	static void* (__cdecl* OGameMalloc)(unsigned int size);
	static void* __cdecl HGameMalloc(unsigned int size);
};
