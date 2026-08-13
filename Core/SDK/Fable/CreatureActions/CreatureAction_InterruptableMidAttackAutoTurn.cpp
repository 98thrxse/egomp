#include "CreatureAction_InterruptableMidAttackAutoTurn.h"

CCreatureAction_InterruptableMidAttackAutoTurn::CCreatureAction_InterruptableMidAttackAutoTurn(CThingCreatureBase& creature, CThing& target, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability)
{
    OInterruptableMidAttackAutoTurn_1(this, creature, target, pweapon, required_facing, pmelee_ability);
}

void (__thiscall* CCreatureAction_InterruptableMidAttackAutoTurn::OInterruptableMidAttackAutoTurn_1)(CCreatureAction_InterruptableMidAttackAutoTurn*, CThingCreatureBase&, CThing&, const CThing*, const C3DVector&, CDefPointer*) = nullptr;
void __fastcall CCreatureAction_InterruptableMidAttackAutoTurn::HInterruptableMidAttackAutoTurn_1(CCreatureAction_InterruptableMidAttackAutoTurn* _this, void* _EDX, CThingCreatureBase& creature, CThing& target, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability)
{
    OInterruptableMidAttackAutoTurn_1(_this, creature, target, pweapon, required_facing, pmelee_ability);
}

CCreatureAction_InterruptableMidAttackAutoTurn::CCreatureAction_InterruptableMidAttackAutoTurn(CThingCreatureBase& creature, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability)
{
    OInterruptableMidAttackAutoTurn_2(this, creature, pweapon, required_facing, pmelee_ability);
}

void (__thiscall* CCreatureAction_InterruptableMidAttackAutoTurn::OInterruptableMidAttackAutoTurn_2)(CCreatureAction_InterruptableMidAttackAutoTurn*, CThingCreatureBase&, const CThing*, const C3DVector&, CDefPointer*) = nullptr;
void __fastcall CCreatureAction_InterruptableMidAttackAutoTurn::HInterruptableMidAttackAutoTurn_2(CCreatureAction_InterruptableMidAttackAutoTurn* _this, void* _EDX, CThingCreatureBase& creature, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability)
{
    OInterruptableMidAttackAutoTurn_2(_this, creature, pweapon, required_facing, pmelee_ability);
}

CCreatureAction_InterruptableMidAttackAutoTurn::CCreatureAction_InterruptableMidAttackAutoTurn(const CCreatureAction_InterruptableMidAttackAutoTurn& __that)
{
    OInterruptableMidAttackAutoTurn_3(this, __that);
}

void (__thiscall* CCreatureAction_InterruptableMidAttackAutoTurn::OInterruptableMidAttackAutoTurn_3)(CCreatureAction_InterruptableMidAttackAutoTurn*, const CCreatureAction_InterruptableMidAttackAutoTurn&) = nullptr;
void __fastcall CCreatureAction_InterruptableMidAttackAutoTurn::HInterruptableMidAttackAutoTurn_3(CCreatureAction_InterruptableMidAttackAutoTurn* _this, void* _EDX, const CCreatureAction_InterruptableMidAttackAutoTurn& __that)
{
    OInterruptableMidAttackAutoTurn_3(_this, __that);
}

void CCreatureAction_InterruptableMidAttackAutoTurn::Hook()
{
    ADD_HOOK(0x0087CDF0, HInterruptableMidAttackAutoTurn_1, OInterruptableMidAttackAutoTurn_1);
    ADD_HOOK(0x0087CEC0, HInterruptableMidAttackAutoTurn_2, OInterruptableMidAttackAutoTurn_2);
    ADD_HOOK(0x0087E690, HInterruptableMidAttackAutoTurn_3, OInterruptableMidAttackAutoTurn_3);
}
