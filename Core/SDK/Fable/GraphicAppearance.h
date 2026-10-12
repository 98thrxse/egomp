#pragma once

#include <vector>
#include <functional>
#include <iostream>

#include "../Utils/Hook.h"

namespace NGraphicAppearance
{
    class CTCGraphicAppearance
    {
    public:
		void SetAlpha(unsigned __int8 alpha);

        static void Hook();

    private:
        static void(__thiscall* OSetAlpha)(CTCGraphicAppearance*, unsigned __int8);
		static void __fastcall HSetAlpha(CTCGraphicAppearance* _this, void* _EDX, unsigned __int8 alpha);
    };
}
