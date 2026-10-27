#include "Utils/Utils.h"
#include "Config/Config.h"
#include "Injector/Injector.h"

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	(void)hInstance; (void)hPrevInstance; (void)lpCmdLine; (void)nCmdShow;

	if (!Config())
		return 1;

	if (!Launch())
		return 1;

	return 0;
}
