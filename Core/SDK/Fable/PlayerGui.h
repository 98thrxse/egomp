#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

class CPlayerGui
{
public:
	void dCPlayerGui();

	static void Hook();

private:
	static void(__thiscall* OdCPlayerGui)(CPlayerGui*);
	static void __fastcall HdCPlayerGui(CPlayerGui* _this, void* _EDX);
};