#include "BaseIntelligentPointer.h"

CBaseObject* (__thiscall* CBaseIntelligentPointer::OGetPItem)(CBaseIntelligentPointer*) = nullptr;
CBaseObject* __fastcall CBaseIntelligentPointer::HGetPItem(CBaseIntelligentPointer* _this, void* _EDX)
{
	return OGetPItem(_this);
}

void(__thiscall* CBaseIntelligentPointer::OSetPItem)(CBaseIntelligentPointer*, CBaseObject*) = nullptr;
void __fastcall CBaseIntelligentPointer::HSetPItem(CBaseIntelligentPointer* _this, void* _EDX, CBaseObject* pObject)
{
	OSetPItem(_this, pObject);
}

CBaseObject* CBaseIntelligentPointer::GetPItem()
{
	return OGetPItem(this);
}

void CBaseIntelligentPointer::SetPItem(CBaseObject* pObject)
{
	OSetPItem(this, pObject);
}

void CBaseIntelligentPointer::Hook()
{
	ADD_HOOK(0x00A01B50, HGetPItem, OGetPItem);
	ADD_HOOK(0x00A01B90, HSetPItem, OSetPItem);
}
