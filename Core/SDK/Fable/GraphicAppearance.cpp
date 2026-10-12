#include "GraphicAppearance.h"

namespace NGraphicAppearance
{
	void(__thiscall* CTCGraphicAppearance::OSetAlpha)(CTCGraphicAppearance*, unsigned __int8) = nullptr;
	void CTCGraphicAppearance::HSetAlpha(CTCGraphicAppearance* _this, void* _EDX, unsigned __int8 alpha)
	{
		OSetAlpha(_this, alpha);
	}

	void CTCGraphicAppearance::SetAlpha(unsigned __int8 alpha)
	{
		OSetAlpha(this, alpha);
	}

	void CTCGraphicAppearance::Hook()
	{
		ADD_HOOK(0x004BFAC0, HSetAlpha, OSetAlpha);
	}
}
