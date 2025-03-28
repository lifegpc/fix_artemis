#include "d3d11proxy.h"

void D3D11Proxy::Init(HMODULE hProxy)
{
    ProxyModuleHandle = hProxy;
    
    wchar_t realDllPath[MAX_PATH];
    GetSystemDirectoryW(realDllPath, MAX_PATH);
    wcscat_s(realDllPath, L"\\d3d11.dll");
    OriginalModuleHandle = LoadLibraryW(realDllPath);
    if (OriginalModuleHandle == nullptr)
    {
        MessageBoxW(nullptr, L"Cannot load original d3d11.dll library", L"D3D11Proxy", MB_ICONERROR);
        ExitProcess(0);
    }

#define RESOLVE(fn) Original##fn = GetProcAddress(OriginalModuleHandle, #fn)
    RESOLVE(D3D11CoreCreateDevice);
    RESOLVE(D3D11CreateDevice);
    RESOLVE(D3D11CreateDeviceAndSwapChain);
    RESOLVE(D3D11On12CreateDevice);
    RESOLVE(D3DKMTCloseAdapter);
    RESOLVE(D3DKMTCreateAllocation);
    RESOLVE(D3DKMTCreateContext);
    RESOLVE(D3DKMTCreateDevice);
    RESOLVE(D3DKMTCreateSynchronizationObject);
    RESOLVE(D3DKMTDestroyAllocation);
    RESOLVE(D3DKMTDestroyContext);
    RESOLVE(D3DKMTDestroyDevice);
    RESOLVE(D3DKMTDestroySynchronizationObject);
    RESOLVE(D3DKMTEscape);
    RESOLVE(D3DKMTGetContextSchedulingPriority);
    RESOLVE(D3DKMTGetDeviceState);
    RESOLVE(D3DKMTGetDisplayModeList);
    RESOLVE(D3DKMTGetMultisampleMethodList);
    RESOLVE(D3DKMTGetRuntimeData);
    RESOLVE(D3DKMTGetSharedPrimaryHandle);
    RESOLVE(D3DKMTLock);
    RESOLVE(D3DKMTOpenAdapterFromHdc);
    RESOLVE(D3DKMTOpenResource);
    RESOLVE(D3DKMTPresent);
    RESOLVE(D3DKMTQueryAdapterInfo);
    RESOLVE(D3DKMTQueryAllocationResidency);
    RESOLVE(D3DKMTQueryResourceInfo);
    RESOLVE(D3DKMTRender);
    RESOLVE(D3DKMTSetAllocationPriority);
    RESOLVE(D3DKMTSetContextSchedulingPriority);
    RESOLVE(D3DKMTSetDisplayMode);
    RESOLVE(D3DKMTSetDisplayPrivateDriverFormat);
    RESOLVE(D3DKMTSetGammaRamp);
    RESOLVE(D3DKMTSetVidPnSourceOwner);
    RESOLVE(D3DKMTSignalSynchronizationObject);
    RESOLVE(D3DKMTUnlock);
    RESOLVE(D3DKMTWaitForSynchronizationObject);
    RESOLVE(D3DKMTWaitForVerticalBlankEvent);
    RESOLVE(CreateDirect3D11DeviceFromDXGIDevice);
    RESOLVE(CreateDirect3D11SurfaceFromDXGISurface);
#undef RESOLVE
}

#ifdef _WIN64
// 64位平台使用函数指针调用
void FakeD3D11CoreCreateDevice()                           { ((void(*)())D3D11Proxy::OriginalD3D11CoreCreateDevice)(); }
void FakeD3D11CreateDevice()                               { ((void(*)())D3D11Proxy::OriginalD3D11CreateDevice)(); }
void FakeD3D11CreateDeviceAndSwapChain()                   { ((void(*)())D3D11Proxy::OriginalD3D11CreateDeviceAndSwapChain)(); }
void FakeD3D11On12CreateDevice()                           { ((void(*)())D3D11Proxy::OriginalD3D11On12CreateDevice)(); }
void FakeD3DKMTCloseAdapter()                              { ((void(*)())D3D11Proxy::OriginalD3DKMTCloseAdapter)(); }
void FakeD3DKMTCreateAllocation()                          { ((void(*)())D3D11Proxy::OriginalD3DKMTCreateAllocation)(); }
void FakeD3DKMTCreateContext()                             { ((void(*)())D3D11Proxy::OriginalD3DKMTCreateContext)(); }
void FakeD3DKMTCreateDevice()                              { ((void(*)())D3D11Proxy::OriginalD3DKMTCreateDevice)(); }
void FakeD3DKMTCreateSynchronizationObject()               { ((void(*)())D3D11Proxy::OriginalD3DKMTCreateSynchronizationObject)(); }
void FakeD3DKMTDestroyAllocation()                         { ((void(*)())D3D11Proxy::OriginalD3DKMTDestroyAllocation)(); }
void FakeD3DKMTDestroyContext()                            { ((void(*)())D3D11Proxy::OriginalD3DKMTDestroyContext)(); }
void FakeD3DKMTDestroyDevice()                             { ((void(*)())D3D11Proxy::OriginalD3DKMTDestroyDevice)(); }
void FakeD3DKMTDestroySynchronizationObject()              { ((void(*)())D3D11Proxy::OriginalD3DKMTDestroySynchronizationObject)(); }
void FakeD3DKMTEscape()                                    { ((void(*)())D3D11Proxy::OriginalD3DKMTEscape)(); }
void FakeD3DKMTGetContextSchedulingPriority()              { ((void(*)())D3D11Proxy::OriginalD3DKMTGetContextSchedulingPriority)(); }
void FakeD3DKMTGetDeviceState()                            { ((void(*)())D3D11Proxy::OriginalD3DKMTGetDeviceState)(); }
void FakeD3DKMTGetDisplayModeList()                        { ((void(*)())D3D11Proxy::OriginalD3DKMTGetDisplayModeList)(); }
void FakeD3DKMTGetMultisampleMethodList()                  { ((void(*)())D3D11Proxy::OriginalD3DKMTGetMultisampleMethodList)(); }
void FakeD3DKMTGetRuntimeData()                            { ((void(*)())D3D11Proxy::OriginalD3DKMTGetRuntimeData)(); }
void FakeD3DKMTGetSharedPrimaryHandle()                    { ((void(*)())D3D11Proxy::OriginalD3DKMTGetSharedPrimaryHandle)(); }
void FakeD3DKMTLock()                                      { ((void(*)())D3D11Proxy::OriginalD3DKMTLock)(); }
void FakeD3DKMTOpenAdapterFromHdc()                        { ((void(*)())D3D11Proxy::OriginalD3DKMTOpenAdapterFromHdc)(); }
void FakeD3DKMTOpenResource()                              { ((void(*)())D3D11Proxy::OriginalD3DKMTOpenResource)(); }
void FakeD3DKMTPresent()                                   { ((void(*)())D3D11Proxy::OriginalD3DKMTPresent)(); }
void FakeD3DKMTQueryAdapterInfo()                          { ((void(*)())D3D11Proxy::OriginalD3DKMTQueryAdapterInfo)(); }
void FakeD3DKMTQueryAllocationResidency()                  { ((void(*)())D3D11Proxy::OriginalD3DKMTQueryAllocationResidency)(); }
void FakeD3DKMTQueryResourceInfo()                         { ((void(*)())D3D11Proxy::OriginalD3DKMTQueryResourceInfo)(); }
void FakeD3DKMTRender()                                    { ((void(*)())D3D11Proxy::OriginalD3DKMTRender)(); }
void FakeD3DKMTSetAllocationPriority()                     { ((void(*)())D3D11Proxy::OriginalD3DKMTSetAllocationPriority)(); }
void FakeD3DKMTSetContextSchedulingPriority()              { ((void(*)())D3D11Proxy::OriginalD3DKMTSetContextSchedulingPriority)(); }
void FakeD3DKMTSetDisplayMode()                            { ((void(*)())D3D11Proxy::OriginalD3DKMTSetDisplayMode)(); }
void FakeD3DKMTSetDisplayPrivateDriverFormat()             { ((void(*)())D3D11Proxy::OriginalD3DKMTSetDisplayPrivateDriverFormat)(); }
void FakeD3DKMTSetGammaRamp()                              { ((void(*)())D3D11Proxy::OriginalD3DKMTSetGammaRamp)(); }
void FakeD3DKMTSetVidPnSourceOwner()                       { ((void(*)())D3D11Proxy::OriginalD3DKMTSetVidPnSourceOwner)(); }
void FakeD3DKMTSignalSynchronizationObject()               { ((void(*)())D3D11Proxy::OriginalD3DKMTSignalSynchronizationObject)(); }
void FakeD3DKMTUnlock()                                    { ((void(*)())D3D11Proxy::OriginalD3DKMTUnlock)(); }
void FakeD3DKMTWaitForSynchronizationObject()              { ((void(*)())D3D11Proxy::OriginalD3DKMTWaitForSynchronizationObject)(); }
void FakeD3DKMTWaitForVerticalBlankEvent()                 { ((void(*)())D3D11Proxy::OriginalD3DKMTWaitForVerticalBlankEvent)(); }
void FakeCreateDirect3D11DeviceFromDXGIDevice()            { ((void(*)())D3D11Proxy::OriginalCreateDirect3D11DeviceFromDXGIDevice)(); }
void FakeCreateDirect3D11SurfaceFromDXGISurface()          { ((void(*)())D3D11Proxy::OriginalCreateDirect3D11SurfaceFromDXGISurface)(); }
#else
// 32位平台使用原有的内联汇编
__declspec(naked) void FakeD3D11CoreCreateDevice()                           { __asm { jmp [D3D11Proxy::OriginalD3D11CoreCreateDevice] } }
__declspec(naked) void FakeD3D11CreateDevice()                               { __asm { jmp [D3D11Proxy::OriginalD3D11CreateDevice] } }
__declspec(naked) void FakeD3D11CreateDeviceAndSwapChain()                   { __asm { jmp [D3D11Proxy::OriginalD3D11CreateDeviceAndSwapChain] } }
__declspec(naked) void FakeD3D11On12CreateDevice()                           { __asm { jmp [D3D11Proxy::OriginalD3D11On12CreateDevice] } }
__declspec(naked) void FakeD3DKMTCloseAdapter()                              { __asm { jmp [D3D11Proxy::OriginalD3DKMTCloseAdapter] } }
__declspec(naked) void FakeD3DKMTCreateAllocation()                          { __asm { jmp [D3D11Proxy::OriginalD3DKMTCreateAllocation] } }
__declspec(naked) void FakeD3DKMTCreateContext()                             { __asm { jmp [D3D11Proxy::OriginalD3DKMTCreateContext] } }
__declspec(naked) void FakeD3DKMTCreateDevice()                              { __asm { jmp [D3D11Proxy::OriginalD3DKMTCreateDevice] } }
__declspec(naked) void FakeD3DKMTCreateSynchronizationObject()               { __asm { jmp [D3D11Proxy::OriginalD3DKMTCreateSynchronizationObject] } }
__declspec(naked) void FakeD3DKMTDestroyAllocation()                         { __asm { jmp [D3D11Proxy::OriginalD3DKMTDestroyAllocation] } }
__declspec(naked) void FakeD3DKMTDestroyContext()                            { __asm { jmp [D3D11Proxy::OriginalD3DKMTDestroyContext] } }
__declspec(naked) void FakeD3DKMTDestroyDevice()                             { __asm { jmp [D3D11Proxy::OriginalD3DKMTDestroyDevice] } }
__declspec(naked) void FakeD3DKMTDestroySynchronizationObject()              { __asm { jmp [D3D11Proxy::OriginalD3DKMTDestroySynchronizationObject] } }
__declspec(naked) void FakeD3DKMTEscape()                                    { __asm { jmp [D3D11Proxy::OriginalD3DKMTEscape] } }
__declspec(naked) void FakeD3DKMTGetContextSchedulingPriority()              { __asm { jmp [D3D11Proxy::OriginalD3DKMTGetContextSchedulingPriority] } }
__declspec(naked) void FakeD3DKMTGetDeviceState()                            { __asm { jmp [D3D11Proxy::OriginalD3DKMTGetDeviceState] } }
__declspec(naked) void FakeD3DKMTGetDisplayModeList()                        { __asm { jmp [D3D11Proxy::OriginalD3DKMTGetDisplayModeList] } }
__declspec(naked) void FakeD3DKMTGetMultisampleMethodList()                  { __asm { jmp [D3D11Proxy::OriginalD3DKMTGetMultisampleMethodList] } }
__declspec(naked) void FakeD3DKMTGetRuntimeData()                            { __asm { jmp [D3D11Proxy::OriginalD3DKMTGetRuntimeData] } }
__declspec(naked) void FakeD3DKMTGetSharedPrimaryHandle()                    { __asm { jmp [D3D11Proxy::OriginalD3DKMTGetSharedPrimaryHandle] } }
__declspec(naked) void FakeD3DKMTLock()                                      { __asm { jmp [D3D11Proxy::OriginalD3DKMTLock] } }
__declspec(naked) void FakeD3DKMTOpenAdapterFromHdc()                        { __asm { jmp [D3D11Proxy::OriginalD3DKMTOpenAdapterFromHdc] } }
__declspec(naked) void FakeD3DKMTOpenResource()                              { __asm { jmp [D3D11Proxy::OriginalD3DKMTOpenResource] } }
__declspec(naked) void FakeD3DKMTPresent()                                   { __asm { jmp [D3D11Proxy::OriginalD3DKMTPresent] } }
__declspec(naked) void FakeD3DKMTQueryAdapterInfo()                          { __asm { jmp [D3D11Proxy::OriginalD3DKMTQueryAdapterInfo] } }
__declspec(naked) void FakeD3DKMTQueryAllocationResidency()                  { __asm { jmp [D3D11Proxy::OriginalD3DKMTQueryAllocationResidency] } }
__declspec(naked) void FakeD3DKMTQueryResourceInfo()                         { __asm { jmp [D3D11Proxy::OriginalD3DKMTQueryResourceInfo] } }
__declspec(naked) void FakeD3DKMTRender()                                    { __asm { jmp [D3D11Proxy::OriginalD3DKMTRender] } }
__declspec(naked) void FakeD3DKMTSetAllocationPriority()                     { __asm { jmp [D3D11Proxy::OriginalD3DKMTSetAllocationPriority] } }
__declspec(naked) void FakeD3DKMTSetContextSchedulingPriority()              { __asm { jmp [D3D11Proxy::OriginalD3DKMTSetContextSchedulingPriority] } }
__declspec(naked) void FakeD3DKMTSetDisplayMode()                            { __asm { jmp [D3D11Proxy::OriginalD3DKMTSetDisplayMode] } }
__declspec(naked) void FakeD3DKMTSetDisplayPrivateDriverFormat()             { __asm { jmp [D3D11Proxy::OriginalD3DKMTSetDisplayPrivateDriverFormat] } }
__declspec(naked) void FakeD3DKMTSetGammaRamp()                              { __asm { jmp [D3D11Proxy::OriginalD3DKMTSetGammaRamp] } }
__declspec(naked) void FakeD3DKMTSetVidPnSourceOwner()                       { __asm { jmp [D3D11Proxy::OriginalD3DKMTSetVidPnSourceOwner] } }
__declspec(naked) void FakeD3DKMTSignalSynchronizationObject()               { __asm { jmp [D3D11Proxy::OriginalD3DKMTSignalSynchronizationObject] } }
__declspec(naked) void FakeD3DKMTUnlock()                                    { __asm { jmp [D3D11Proxy::OriginalD3DKMTUnlock] } }
__declspec(naked) void FakeD3DKMTWaitForSynchronizationObject()              { __asm { jmp [D3D11Proxy::OriginalD3DKMTWaitForSynchronizationObject] } }
__declspec(naked) void FakeD3DKMTWaitForVerticalBlankEvent()                 { __asm { jmp [D3D11Proxy::OriginalD3DKMTWaitForVerticalBlankEvent] } }
__declspec(naked) void FakeCreateDirect3D11DeviceFromDXGIDevice()            { __asm { jmp [D3D11Proxy::OriginalCreateDirect3D11DeviceFromDXGIDevice] } }
__declspec(naked) void FakeCreateDirect3D11SurfaceFromDXGISurface()          { __asm { jmp [D3D11Proxy::OriginalCreateDirect3D11SurfaceFromDXGISurface] } }
#endif
