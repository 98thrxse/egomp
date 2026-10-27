#include "Config.h"

bool Config()
{
    wchar_t exePath[MAX_PATH];
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) == 0)
        return false;

    wchar_t* slash = wcsrchr(exePath, L'\\');
    if (!slash)
        return false;

    *slash = L'\0';

    wchar_t iniPath[MAX_PATH];
    if (swprintf_s(iniPath, L"%s\\EgoMP.ini", exePath) < 0)
        return false;

    if (GetFileAttributesW(iniPath) != INVALID_FILE_ATTRIBUTES)
        return true;

    const wchar_t* content =
        L"[Host]\n"
        L"Port=57150\n"
        L"Slots=4\n\n"

        L"[Client]\n"
        L"IP=127.0.0.1\n"
        L"Port=57150\n";

    HANDLE hFile = CreateFileW(
        iniPath,
        GENERIC_WRITE,
        0,
        nullptr,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
        return false;

    DWORD bytesWritten = 0;
    BOOL ok = WriteFile(
        hFile,
        content,
        (DWORD)(wcslen(content) * sizeof(wchar_t)),
        &bytesWritten,
        nullptr);

    CloseHandle(hFile);
    return ok != FALSE;
}
