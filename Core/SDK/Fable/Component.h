#pragma once

#include <iostream>

#include "../Utils/Hook.h"

namespace NUISystem
{
	class CComponent
	{
	public:
		char pad[0xDC];

		static void Hook();
	};
}
