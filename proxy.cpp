#include "proxy.h"

void Proxy::Init(HMODULE hProxy)
{
    ProxyModuleHandle = hProxy;
    
    wchar_t realDllPath[MAX_PATH];
    GetSystemDirectoryW(realDllPath, MAX_PATH);
    wcscat_s(realDllPath, L"\\d3d9.dll");
    OriginalModuleHandle = LoadLibraryW(realDllPath);
    if (OriginalModuleHandle == nullptr)
    {
        MessageBoxW(nullptr, L"Cannot load original d3d9.dll library", L"Proxy", MB_ICONERROR);
        ExitProcess(0);
    }

#define RESOLVE(fn) Original##fn = GetProcAddress(OriginalModuleHandle, #fn)
    RESOLVE(D3DPERF_BeginEvent);
    RESOLVE(D3DPERF_EndEvent);
    RESOLVE(D3DPERF_GetStatus);
    RESOLVE(D3DPERF_QueryRepeatFrame);
    RESOLVE(D3DPERF_SetMarker);
    RESOLVE(D3DPERF_SetOptions);
    RESOLVE(D3DPERF_SetRegion);
    RESOLVE(DebugSetLevel);
    RESOLVE(DebugSetMute);
    RESOLVE(Direct3D9EnableMaximizedWindowedModeShim);
    RESOLVE(Direct3DCreate9);
    RESOLVE(Direct3DCreate9Ex);
    RESOLVE(Direct3DCreate9On12);
    RESOLVE(Direct3DCreate9On12Ex);
    RESOLVE(Direct3DShaderValidatorCreate9);
    RESOLVE(PSGPError);
    RESOLVE(PSGPSampleTexture);
#undef RESOLVE
}

#ifdef _WIN64
// 64位平台使用函数指针调用
void FakeD3DPERF_BeginEvent()                         { ((void(*)())Proxy::OriginalD3DPERF_BeginEvent)(); }
void FakeD3DPERF_EndEvent()                           { ((void(*)())Proxy::OriginalD3DPERF_EndEvent)(); }
void FakeD3DPERF_GetStatus()                          { ((void(*)())Proxy::OriginalD3DPERF_GetStatus)(); }
void FakeD3DPERF_QueryRepeatFrame()                   { ((void(*)())Proxy::OriginalD3DPERF_QueryRepeatFrame)(); }
void FakeD3DPERF_SetMarker()                          { ((void(*)())Proxy::OriginalD3DPERF_SetMarker)(); }
void FakeD3DPERF_SetOptions()                         { ((void(*)())Proxy::OriginalD3DPERF_SetOptions)(); }
void FakeD3DPERF_SetRegion()                          { ((void(*)())Proxy::OriginalD3DPERF_SetRegion)(); }
void FakeDebugSetLevel()                              { ((void(*)())Proxy::OriginalDebugSetLevel)(); }
void FakeDebugSetMute()                               { ((void(*)())Proxy::OriginalDebugSetMute)(); }
void FakeDirect3D9EnableMaximizedWindowedModeShim()   { ((void(*)())Proxy::OriginalDirect3D9EnableMaximizedWindowedModeShim)(); }
void FakeDirect3DCreate9()                            { ((void(*)())Proxy::OriginalDirect3DCreate9)(); }
void FakeDirect3DCreate9Ex()                          { ((void(*)())Proxy::OriginalDirect3DCreate9Ex)(); }
void FakeDirect3DCreate9On12()                        { ((void(*)())Proxy::OriginalDirect3DCreate9On12)(); }
void FakeDirect3DCreate9On12Ex()                      { ((void(*)())Proxy::OriginalDirect3DCreate9On12Ex)(); }
void FakeDirect3DShaderValidatorCreate9()             { ((void(*)())Proxy::OriginalDirect3DShaderValidatorCreate9)(); }
void FakePSGPError()                                  { ((void(*)())Proxy::OriginalPSGPError)(); }
void FakePSGPSampleTexture()                          { ((void(*)())Proxy::OriginalPSGPSampleTexture)(); }
#else
// 32位平台使用原有的内联汇编
__declspec(naked) void FakeD3DPERF_BeginEvent()                         { __asm { jmp [Proxy::OriginalD3DPERF_BeginEvent] } }
__declspec(naked) void FakeD3DPERF_EndEvent()                           { __asm { jmp [Proxy::OriginalD3DPERF_EndEvent] } }
__declspec(naked) void FakeD3DPERF_GetStatus()                          { __asm { jmp [Proxy::OriginalD3DPERF_GetStatus] } }
__declspec(naked) void FakeD3DPERF_QueryRepeatFrame()                   { __asm { jmp [Proxy::OriginalD3DPERF_QueryRepeatFrame] } }
__declspec(naked) void FakeD3DPERF_SetMarker()                          { __asm { jmp [Proxy::OriginalD3DPERF_SetMarker] } }
__declspec(naked) void FakeD3DPERF_SetOptions()                         { __asm { jmp [Proxy::OriginalD3DPERF_SetOptions] } }
__declspec(naked) void FakeD3DPERF_SetRegion()                          { __asm { jmp [Proxy::OriginalD3DPERF_SetRegion] } }
__declspec(naked) void FakeDebugSetLevel()                              { __asm { jmp [Proxy::OriginalDebugSetLevel] } }
__declspec(naked) void FakeDebugSetMute()                               { __asm { jmp [Proxy::OriginalDebugSetMute] } }
__declspec(naked) void FakeDirect3D9EnableMaximizedWindowedModeShim()   { __asm { jmp [Proxy::OriginalDirect3D9EnableMaximizedWindowedModeShim] } }
__declspec(naked) void FakeDirect3DCreate9()                            { __asm { jmp [Proxy::OriginalDirect3DCreate9] } }
__declspec(naked) void FakeDirect3DCreate9Ex()                          { __asm { jmp [Proxy::OriginalDirect3DCreate9Ex] } }
__declspec(naked) void FakeDirect3DCreate9On12()                        { __asm { jmp [Proxy::OriginalDirect3DCreate9On12] } }
__declspec(naked) void FakeDirect3DCreate9On12Ex()                      { __asm { jmp [Proxy::OriginalDirect3DCreate9On12Ex] } }
__declspec(naked) void FakeDirect3DShaderValidatorCreate9()             { __asm { jmp [Proxy::OriginalDirect3DShaderValidatorCreate9] } }
__declspec(naked) void FakePSGPError()                                  { __asm { jmp [Proxy::OriginalPSGPError] } }
__declspec(naked) void FakePSGPSampleTexture()                          { __asm { jmp [Proxy::OriginalPSGPSampleTexture] } }
#endif
