#pragma once

#include <Windows.h>

inline HWND(WINAPI* OGetForegroundWindow)() = nullptr;
inline HWND GetOriginalForegroundWindow()
{
    return OGetForegroundWindow();
}
