#include <Windows.h>
#include "detours.h"
#include "fileop.h"
#include "wchar_util.h"
#if D3D9_PROXY
#include "proxy.h"
#endif

std::string dir;
std::string base;

static decltype(CreateFileW) *TrueCreateFileW = CreateFileW;

HANDLE WINAPI HookedCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    if (!dir.empty() || !base.empty()) {
        std::string file;
        if (wchar_util::wstr_to_str(file, lpFileName, CP_UTF8)) {
            auto pos = file.find(".pfs");
            if (pos != std::string::npos) {
                std::string target = fileop::join(dir, base + file.substr(pos + 4));
                std::wstring wtarget;
                if (wchar_util::str_to_wstr(wtarget, target, CP_UTF8)) {
                    return TrueCreateFileW(wtarget.c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
                }
            }
        }
    }
    return TrueCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

void Init() {
    WCHAR path[MAX_PATH];
    if (!GetModuleFileNameW(NULL, path, MAX_PATH)) {
        return;
    }
    std::string exe;
    if (!wchar_util::wstr_to_str(exe, path, CP_UTF8)) {
        return;
    }
    dir = fileop::dirname(exe);
    std::list<std::string> files;
    if (!fileop::listdir(dir, files, false)) {
        return;
    }
    for (auto& f: files) {
        if (f.find(".pfs") != f.size() - 4) {
            continue;
        }
        base = f;
        return;
    }
}

void Attach() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)TrueCreateFileW, HookedCreateFileW);
    DetourTransactionCommit();
}

void Detach() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourDetach(&(PVOID&)TrueCreateFileW, HookedCreateFileW);
    DetourTransactionCommit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID rev) {
    switch (reason) {
    case DLL_PROCESS_ATTACH:
#if D3D9_PROXY
        Proxy::Init(hModule);
#endif
        Init();
        Attach();
        break;
    case DLL_PROCESS_DETACH:
        Detach();
        break;
    }
    return TRUE;
}
