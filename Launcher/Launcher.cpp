#include <windows.h>

bool FileExists(const wchar_t* path)
{
    DWORD attributes = GetFileAttributesW(path);
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

void ShowError(const wchar_t* message)
{
    MessageBoxW(nullptr, message, L"Error", MB_ICONERROR);
}

bool Inject(HANDLE processHandle, const wchar_t* dllPath)
{
    SIZE_T dllPathSize = (wcslen(dllPath) + 1) * sizeof(wchar_t);
    LPVOID remoteMemory = VirtualAllocEx(processHandle, nullptr, dllPathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remoteMemory) return false;

    if (!WriteProcessMemory(processHandle, remoteMemory, dllPath, dllPathSize, nullptr))
    {
        VirtualFreeEx(processHandle, remoteMemory, 0, MEM_RELEASE);
        return false;
    }

    HMODULE kernel32Module = GetModuleHandleW(L"kernel32.dll");
    FARPROC loadLibraryAddress = kernel32Module ? GetProcAddress(kernel32Module, "LoadLibraryW") : nullptr;
    if (!loadLibraryAddress) { VirtualFreeEx(processHandle, remoteMemory, 0, MEM_RELEASE); return false; }

    HANDLE remoteThread = CreateRemoteThread(processHandle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(loadLibraryAddress), remoteMemory, 0, nullptr);
    if (!remoteThread) { VirtualFreeEx(processHandle, remoteMemory, 0, MEM_RELEASE); return false; }

    WaitForSingleObject(remoteThread, INFINITE);

    DWORD exitCode = 0;
    BOOL got = GetExitCodeThread(remoteThread, &exitCode);

    CloseHandle(remoteThread);
    VirtualFreeEx(processHandle, remoteMemory, 0, MEM_RELEASE);

    return got && exitCode != 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
    (void)hInstance; (void)hPrevInstance; (void)lpCmdLine; (void)nCmdShow;

    const wchar_t* exePath = L"..\\Fable.exe";
    const wchar_t* dllRelativePath = L"EgoMP.dll";

    wchar_t fullDllPath[MAX_PATH];
    DWORD len = GetFullPathNameW(dllRelativePath, MAX_PATH, fullDllPath, nullptr);
    if (!len || len >= MAX_PATH) { ShowError(L"Could not resolve `EgoMP.dll` path."); return 1; }

    if (!FileExists(exePath)) { ShowError(L"`Fable.exe` not found."); return 1; }
    if (!FileExists(fullDllPath)) { ShowError(L"`EgoMP.dll` not found."); return 1; }

    STARTUPINFOW startupInfo = { sizeof(startupInfo) };
    PROCESS_INFORMATION processInfo = {};

    if (!CreateProcessW(exePath, nullptr, nullptr, nullptr, FALSE, CREATE_SUSPENDED, nullptr, nullptr, &startupInfo, &processInfo))
    {
        ShowError(L"Failed to launch `Fable.exe`.");
        return 1;
    }

    bool injected = false;
    if (processInfo.hProcess)
        injected = Inject(processInfo.hProcess, fullDllPath);

    if (injected)
    {
        if (processInfo.hThread)
        {
            if (ResumeThread(processInfo.hThread) == (DWORD)-1)
            {
                ShowError(L"Failed to resume thread.");
                if (processInfo.hProcess) TerminateProcess(processInfo.hProcess, 1);
                injected = false;
            }
        }
        else
        {
            ShowError(L"Missing thread handle.");
            if (processInfo.hProcess) TerminateProcess(processInfo.hProcess, 1);
            injected = false;
        }
    }
    else
    {
        if (processInfo.hProcess) TerminateProcess(processInfo.hProcess, 1);
    }

    if (processInfo.hThread) CloseHandle(processInfo.hThread);
    if (processInfo.hProcess) CloseHandle(processInfo.hProcess);

    return injected ? 0 : 1;
}
