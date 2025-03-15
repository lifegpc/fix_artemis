#pragma once
#include <windows.h>
#include <ctffunc.h>
#include <d2d1.h>
#include <d2d1_3.h>
#include <d3d11.h>
#include <ddraw.h>
#include <dsound.h>
#include <dwrite.h>
#include <gdiplus.h>
#include <Mmreg.h>
#include <msctf.h>
#include <MSAcm.h>

#include <codecvt>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#define VNTEXTPROXY_D2D1

class Proxy
{
public:
    static void Init(HMODULE hProxy);

    static inline HMODULE ProxyModuleHandle{};
    static inline HMODULE OriginalModuleHandle{};

    static inline void* OriginalD3DPERF_BeginEvent{};
    static inline void* OriginalD3DPERF_EndEvent{};
    static inline void* OriginalD3DPERF_GetStatus{};
    static inline void* OriginalD3DPERF_QueryRepeatFrame{};
    static inline void* OriginalD3DPERF_SetMarker{};
    static inline void* OriginalD3DPERF_SetOptions{};
    static inline void* OriginalD3DPERF_SetRegion{};
    static inline void* OriginalDebugSetLevel{};
    static inline void* OriginalDebugSetMute{};
    static inline void* OriginalDirect3D9EnableMaximizedWindowedModeShim{};
    static inline void* OriginalDirect3DCreate9{};
    static inline void* OriginalDirect3DCreate9Ex{};
    static inline void* OriginalDirect3DCreate9On12{};
    static inline void* OriginalDirect3DCreate9On12Ex{};
    static inline void* OriginalDirect3DShaderValidatorCreate9{};
    static inline void* OriginalPSGPError{};
    static inline void* OriginalPSGPSampleTexture{};
};
