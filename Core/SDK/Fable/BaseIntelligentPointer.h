#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "BaseObject.h"

class CBaseIntelligentPointer
{
public:
	char pad[0x8];

	CBaseObject* GetPItem();
	void SetPItem(CBaseObject* pObject);

	static void Hook();

private:
	static CBaseObject* (__thiscall* OGetPItem)(CBaseIntelligentPointer*);
	static CBaseObject* __fastcall HGetPItem(CBaseIntelligentPointer* _this, void* _EDX);

	static void(__thiscall* OSetPItem)(CBaseIntelligentPointer*, CBaseObject*);
	static void __fastcall HSetPItem(CBaseIntelligentPointer* _this, void* _EDX, CBaseObject* pObject);
};
