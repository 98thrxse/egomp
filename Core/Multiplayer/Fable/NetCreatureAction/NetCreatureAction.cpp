#include "NetCreatureAction.h"

void* NetCreatureAction::CCreatureAction_PlayerInteractionGreet(CThingCreatureBase& creatureBase, CThing* target)
{
    void* actionBuffer = ::operator new(0xB0);
    typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CThing&);
    ((Ctor)0x0062DAD0)(actionBuffer, creatureBase, *target);
    return actionBuffer;
}

void* NetCreatureAction::CCreatureAction_StartBlocking(CThingCreatureBase& creatureBase)
{
    void* actionBuffer = ::operator new(0x114);
    typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&);
    ((Ctor)0x00855BE0)(actionBuffer, creatureBase);
    return actionBuffer;
}

void* NetCreatureAction::CCombatAction_ControlledStrafeJump(CThingCreatureBase& creatureBase, CThing* target, const C3DVector& requiredFacing, const C3DVector& originalFacing)
{
    void* actionBuffer = ::operator new(0x130);
    typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CThing&, const C3DVector&, const C3DVector&);
    ((Ctor)0x0085C190)(actionBuffer, creatureBase, *target, requiredFacing, originalFacing);
    return actionBuffer;
}

void* NetCreatureAction::CCreatureAction_KickThingOnGround(CThingCreatureBase& creatureBase, CThing* target)
{
    void* actionBuffer = ::operator new(0x130);
    typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CThing&);
    ((Ctor)0x0087FD20)(actionBuffer, creatureBase, *target);
    return actionBuffer;
}

void* NetCreatureAction::CCreatureAction_InterruptableMidAttackAutoTurn(CThingCreatureBase& creatureBase, CThing* target, CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability)
{
    void* actionBuffer = ::operator new(0x12C);

    if (target)
    {
        typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CThing&, CThing*, const C3DVector&, CDefPointer*);
        ((Ctor)0x0087CDF0)(actionBuffer, creatureBase, *target, pweapon, required_facing, pmelee_ability);
    }
    else
    {
        typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CThing*, const C3DVector&, CDefPointer*);
        ((Ctor)0x0087CEC0)(actionBuffer, creatureBase, pweapon, required_facing, pmelee_ability);
    }
    return actionBuffer;
}

void* NetCreatureAction::CCreatureAction_UnsheatheItemFromInventory(CThingCreatureBase& creatureBase, CThing& unsheathe_item, CCreatureActionBase* pfollow_up_action, long interruption_priority)
{
    void* actionBuffer = ::operator new(0xB8);
    typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CThing&, CCreatureActionBase*, long);
    ((Ctor)0x006A0150)(actionBuffer, creatureBase, unsheathe_item, pfollow_up_action, interruption_priority);
    return actionBuffer;
}

void* NetCreatureAction::CCreatureAction_SheatheItemToInventory(CThingCreatureBase& creatureBase, CCreatureActionBase* pfollow_up_action, long interruption_group_id)
{
    void* actionBuffer = ::operator new(0xB0);
    typedef void* (__thiscall* Ctor)(void*, CThingCreatureBase&, CCreatureActionBase*, long);
    ((Ctor)0x0069FFD0)(actionBuffer, creatureBase, pfollow_up_action, interruption_group_id);
    return actionBuffer;
}
