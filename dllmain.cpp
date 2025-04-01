#include <Windows.h>
#include "detours.h"
#include "fileop.h"
#include "wchar_util.h"
#if D3D9_PROXY
#include "proxy.h"
#endif
#if D3D11_PROXY
#include "d3d11proxy.h"
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

void RunExe(std::string name) {
    std::wstring wpath;
    if (wchar_util::str_to_wstr(wpath, name, CP_UTF8)) {
        STARTUPINFOW si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOWNORMAL;
        wchar_t* wp = new wchar_t[wpath.size() + 1000];
        wcscpy_s(wp, wpath.size() + 1000, wpath.c_str());
        BOOL ret = CreateProcessW(wpath.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        if (ret) {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
        delete[] wp;
    } else {
        STARTUPINFOA si = { sizeof(si) };
        PROCESS_INFORMATION pi;
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_SHOWNORMAL;
        BOOL ret = CreateProcessA(name.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        if (ret) {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
    }
}

void Init() {
    char** args;
    int argc = 0;
    if (wchar_util::getArgv(args, argc)) {
        if (argc > 1) {
            std::string arg = args[1];
            if (arg.find(".exe") != std::string::npos) {
                RunExe(arg);
                wchar_util::freeArgv(args, argc);
                ExitProcess(0);
            }
        }
        wchar_util::freeArgv(args, argc);
    }
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
#if D3D11_PROXY
        D3D11Proxy::Init(hModule);
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
