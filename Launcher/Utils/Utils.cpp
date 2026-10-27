#include "Utils.h"

bool FileExists(const wchar_t* path)
{
    DWORD attributes = GetFileAttributesW(path);
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

void ShowError(const wchar_t* message)
{
    MessageBoxW(nullptr, message, L"Error", MB_ICONERROR);
}
