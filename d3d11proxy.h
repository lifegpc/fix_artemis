#pragma once
#include <windows.h>
#include <d3d11.h>

class D3D11Proxy
{
public:
    static void Init(HMODULE hProxy);

    static inline HMODULE ProxyModuleHandle{};
    static inline HMODULE OriginalModuleHandle{};

    static inline void* OriginalD3D11CoreCreateDevice{};
    static inline void* OriginalD3D11CreateDevice{};
    static inline void* OriginalD3D11CreateDeviceAndSwapChain{};
    static inline void* OriginalD3D11On12CreateDevice{};
    static inline void* OriginalD3DKMTCloseAdapter{};
    static inline void* OriginalD3DKMTCreateAllocation{};
    static inline void* OriginalD3DKMTCreateContext{};
    static inline void* OriginalD3DKMTCreateDevice{};
    static inline void* OriginalD3DKMTCreateSynchronizationObject{};
    static inline void* OriginalD3DKMTDestroyAllocation{};
    static inline void* OriginalD3DKMTDestroyContext{};
    static inline void* OriginalD3DKMTDestroyDevice{};
    static inline void* OriginalD3DKMTDestroySynchronizationObject{};
    static inline void* OriginalD3DKMTEscape{};
    static inline void* OriginalD3DKMTGetContextSchedulingPriority{};
    static inline void* OriginalD3DKMTGetDeviceState{};
    static inline void* OriginalD3DKMTGetDisplayModeList{};
    static inline void* OriginalD3DKMTGetMultisampleMethodList{};
    static inline void* OriginalD3DKMTGetRuntimeData{};
    static inline void* OriginalD3DKMTGetSharedPrimaryHandle{};
    static inline void* OriginalD3DKMTLock{};
    static inline void* OriginalD3DKMTOpenAdapterFromHdc{};
    static inline void* OriginalD3DKMTOpenResource{};
    static inline void* OriginalD3DKMTPresent{};
    static inline void* OriginalD3DKMTQueryAdapterInfo{};
    static inline void* OriginalD3DKMTQueryAllocationResidency{};
    static inline void* OriginalD3DKMTQueryResourceInfo{};
    static inline void* OriginalD3DKMTRender{};
    static inline void* OriginalD3DKMTSetAllocationPriority{};
    static inline void* OriginalD3DKMTSetContextSchedulingPriority{};
    static inline void* OriginalD3DKMTSetDisplayMode{};
    static inline void* OriginalD3DKMTSetDisplayPrivateDriverFormat{};
    static inline void* OriginalD3DKMTSetGammaRamp{};
    static inline void* OriginalD3DKMTSetVidPnSourceOwner{};
    static inline void* OriginalD3DKMTSignalSynchronizationObject{};
    static inline void* OriginalD3DKMTUnlock{};
    static inline void* OriginalD3DKMTWaitForSynchronizationObject{};
    static inline void* OriginalD3DKMTWaitForVerticalBlankEvent{};
    static inline void* OriginalCreateDirect3D11DeviceFromDXGIDevice{};
    static inline void* OriginalCreateDirect3D11SurfaceFromDXGISurface{};
};
