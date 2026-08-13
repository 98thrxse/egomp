#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../../Utils/Hook.h"

#include "../3DVector.h"
#include "../DefPointer.h"
#include "../Thing.h"
#include "../ThingCreatureBase.h"

class CCreatureAction_InterruptableMidAttackAutoTurn
{
public:
    char pad[0x12C];

    CCreatureAction_InterruptableMidAttackAutoTurn(CThingCreatureBase& creature, CThing& target, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability);
    CCreatureAction_InterruptableMidAttackAutoTurn(CThingCreatureBase& creature, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability);
    CCreatureAction_InterruptableMidAttackAutoTurn(const CCreatureAction_InterruptableMidAttackAutoTurn& __that);

    static void Hook();

private:
    static void (__thiscall* OInterruptableMidAttackAutoTurn_1)(CCreatureAction_InterruptableMidAttackAutoTurn*, CThingCreatureBase&, CThing&, const CThing*, const C3DVector&, CDefPointer*);
    static void __fastcall HInterruptableMidAttackAutoTurn_1(CCreatureAction_InterruptableMidAttackAutoTurn* _this, void* _EDX, CThingCreatureBase& creature, CThing& target, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability);

    static void (__thiscall* OInterruptableMidAttackAutoTurn_2)(CCreatureAction_InterruptableMidAttackAutoTurn*, CThingCreatureBase&, const CThing*, const C3DVector&, CDefPointer*);
    static void __fastcall HInterruptableMidAttackAutoTurn_2(CCreatureAction_InterruptableMidAttackAutoTurn* _this, void* _EDX, CThingCreatureBase& creature, const CThing* pweapon, const C3DVector& required_facing, CDefPointer* pmelee_ability);

    static void (__thiscall* OInterruptableMidAttackAutoTurn_3)(CCreatureAction_InterruptableMidAttackAutoTurn*, const CCreatureAction_InterruptableMidAttackAutoTurn&);
    static void __fastcall HInterruptableMidAttackAutoTurn_3(CCreatureAction_InterruptableMidAttackAutoTurn* _this, void* _EDX, const CCreatureAction_InterruptableMidAttackAutoTurn& __that);
};
