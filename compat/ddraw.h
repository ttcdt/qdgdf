#ifndef __DDRAW_INCLUDED__
#define __DDRAW_INCLUDED__
#ifndef DIRECTDRAW_VERSION
#define DIRECTDRAW_VERSION 1792
#endif 
#if defined(_WIN32) && !defined(_NO_COM)
#define COM_NO_WINDOWS_H
#include <objbase.h>
#else
#define IUnknown void
#if !defined(NT_BUILD_ENVIRONMENT) && !defined(WINNT)
#define CO_E_NOTINITIALIZED 0x800401f0
#endif
#endif
#define _FACDD 2166
#define MAKE_DDHRESULT(code) MAKE_HRESULT(1, _FACDD, code)
#ifndef DUMMYUNIONNAMEN
#if defined(__cplusplus) || !defined(NONAMELESSUNION)
#define DUMMYUNIONNAMEN(n)
#else
#define DUMMYUNIONNAMEN(n) u##n
#endif
#endif
#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) | ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24))
#endif 
#define FOURCC_DXT1 (MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT2 (MAKEFOURCC('D','X','T','2'))
#define FOURCC_DXT3 (MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT4 (MAKEFOURCC('D','X','T','4'))
#define FOURCC_DXT5 (MAKEFOURCC('D','X','T','5'))
#if defined(_WIN32) && !defined(_NO_COM)
DEFINE_GUID(CLSID_DirectDraw, 0xd7b70ee0,0x4340,4559,176,99,0,32,175,194,205,53);
DEFINE_GUID(CLSID_DirectDraw7, 0x3c305196,0x50db,4563,156,254,0,192,79,217,48,197);
DEFINE_GUID(CLSID_DirectDrawClipper, 0x593817a0,0x7db3,4559,162,222,0,170,0,185,51,86);
DEFINE_GUID(IID_IDirectDraw, 0x6c14db80,0xa733,4558,165,33,0,32,175,11,229,96);
DEFINE_GUID(IID_IDirectDraw2, 0xb3a6f3e0,0x2b43,4559,162,222,0,170,0,185,51,86);
DEFINE_GUID(IID_IDirectDraw4, 0x9c59509a,0x39bd,4561,140,74,0,192,79,217,48,197);
DEFINE_GUID(IID_IDirectDraw7, 0x15e65ec0,0x3b9c,4562,185,47,0,96,151,151,234,91);
DEFINE_GUID(IID_IDirectDrawSurface, 0x6c14db81,0xa733,4558,165,33,0,32,175,11,229,96);
DEFINE_GUID(IID_IDirectDrawSurface2, 0x57805885,0x6eec,4559,148,65,168,35,3,193,14,39);
DEFINE_GUID(IID_IDirectDrawSurface3, 0xda044e00,0x69b2,4560,161,213,0,170,0,184,223,187);
DEFINE_GUID(IID_IDirectDrawSurface4, 0xb2b8630,0xad35,4560,142,166,0,96,151,151,234,91);
DEFINE_GUID(IID_IDirectDrawSurface7, 0x6675a80,0x3b9b,4562,185,47,0,96,151,151,234,91);
DEFINE_GUID(IID_IDirectDrawPalette, 0x6c14db84,0xa733,4558,165,33,0,32,175,11,229,96);
DEFINE_GUID(IID_IDirectDrawClipper, 0x6c14db85,0xa733,4558,165,33,0,32,175,11,229,96);
DEFINE_GUID(IID_IDirectDrawColorControl, 0x4b9f0ee0,3454,4560,155,6,0,160,201,3,163,184);
DEFINE_GUID(IID_IDirectDrawGammaControl, 0x69c11c3e,0xb46b,4561,173,122,0,192,79,194,155,78);
#endif
struct IDirectDraw;
struct IDirectDrawSurface;
struct IDirectDrawPalette;
struct IDirectDrawClipper;
typedef struct IDirectDraw *LPDIRECTDRAW;
typedef struct IDirectDraw2 *LPDIRECTDRAW2;
typedef struct IDirectDraw4 *LPDIRECTDRAW4;
typedef struct IDirectDraw7 *LPDIRECTDRAW7;
typedef struct IDirectDrawSurface *LPDIRECTDRAWSURFACE;
typedef struct IDirectDrawSurface2 *LPDIRECTDRAWSURFACE2;
typedef struct IDirectDrawSurface3 *LPDIRECTDRAWSURFACE3;
typedef struct IDirectDrawSurface4 *LPDIRECTDRAWSURFACE4;
typedef struct IDirectDrawSurface7 *LPDIRECTDRAWSURFACE7;
typedef struct IDirectDrawPalette *LPDIRECTDRAWPALETTE;
typedef struct IDirectDrawClipper *LPDIRECTDRAWCLIPPER;
typedef struct IDirectDrawColorControl *LPDIRECTDRAWCOLORCONTROL;
typedef struct IDirectDrawGammaControl *LPDIRECTDRAWGAMMACONTROL;
typedef struct _DDFXROP *LPDDFXROP;
typedef struct _DDSURFACEDESC *LPDDSURFACEDESC;
typedef struct _DDSURFACEDESC2 *LPDDSURFACEDESC2;
typedef struct _DDCOLORCONTROL *LPDDCOLORCONTROL;
#if (defined (WIN32) || defined(_WIN32)) && !defined(_NO_COM)
typedef BOOL (FAR PASCAL * LPDDENUMCALLBACKA)(GUID *, LPSTR, LPSTR, LPVOID);
typedef BOOL (FAR PASCAL * LPDDENUMCALLBACKW)(GUID *, LPWSTR, LPWSTR, LPVOID);
extern HRESULT WINAPI DirectDrawEnumerateW(LPDDENUMCALLBACKW lpCallback, LPVOID lpContext);
extern HRESULT WINAPI DirectDrawEnumerateA(LPDDENUMCALLBACKA lpCallback, LPVOID lpContext);
#ifndef HMONITOR_DECLARED
#define HMONITOR_DECLARED
DECLARE_HANDLE(HMONITOR);
#endif
typedef BOOL (FAR PASCAL * LPDDENUMCALLBACKEXA)(GUID *, LPSTR, LPSTR, LPVOID, HMONITOR);
typedef BOOL (FAR PASCAL * LPDDENUMCALLBACKEXW)(GUID *, LPWSTR, LPWSTR, LPVOID, HMONITOR);
extern HRESULT WINAPI DirectDrawEnumerateExW(LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags);
extern HRESULT WINAPI DirectDrawEnumerateExA(LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags);
typedef HRESULT (WINAPI * LPDIRECTDRAWENUMERATEEXA)(LPDDENUMCALLBACKEXA lpCallback, LPVOID lpContext, DWORD dwFlags);
typedef HRESULT (WINAPI * LPDIRECTDRAWENUMERATEEXW)(LPDDENUMCALLBACKEXW lpCallback, LPVOID lpContext, DWORD dwFlags);
#ifdef UNICODE
typedef LPDDENUMCALLBACKW LPDDENUMCALLBACK;
#define DirectDrawEnumerate DirectDrawEnumerateW
typedef LPDDENUMCALLBACKEXW LPDDENUMCALLBACKEX;
typedef LPDIRECTDRAWENUMERATEEXW LPDIRECTDRAWENUMERATEEX;
#define DirectDrawEnumerateEx DirectDrawEnumerateExW
#else
typedef LPDDENUMCALLBACKA LPDDENUMCALLBACK;
#define DirectDrawEnumerate DirectDrawEnumerateA
typedef LPDDENUMCALLBACKEXA LPDDENUMCALLBACKEX;
typedef LPDIRECTDRAWENUMERATEEXA LPDIRECTDRAWENUMERATEEX;
#define DirectDrawEnumerateEx DirectDrawEnumerateExA
#endif
extern HRESULT WINAPI DirectDrawCreate(GUID *lpGUID, LPDIRECTDRAW *lplpDD, IUnknown *pUnkOuter);
extern HRESULT WINAPI DirectDrawCreateEx(GUID * lpGuid, LPVOID *lplpDD, REFIID iid,IUnknown *pUnkOuter);
extern HRESULT WINAPI DirectDrawCreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER *lplpDDClipper, IUnknown *pUnkOuter);
#endif
#define DDENUM_ATTACHEDSECONDARYDEVICES 1
#define DDENUM_DETACHEDSECONDARYDEVICES 2
#define DDENUM_NONDISPLAYDEVICES 4
#define REGSTR_KEY_DDHW_DESCRIPTION "Description"
#define REGSTR_KEY_DDHW_DRIVERNAME "DriverName"
#define REGSTR_PATH_DDHW "Hardware\\DirectDrawDrivers"
#define DDCREATE_HARDWAREONLY 1
#define DDCREATE_EMULATIONONLY 2
#if defined(WINNT) || !defined(WIN32)
typedef long HRESULT;
#endif
typedef HRESULT (FAR PASCAL * LPDDENUMMODESCALLBACK)(LPDDSURFACEDESC, LPVOID);
typedef HRESULT (FAR PASCAL * LPDDENUMMODESCALLBACK2)(LPDDSURFACEDESC2, LPVOID);
typedef HRESULT (FAR PASCAL * LPDDENUMSURFACESCALLBACK)(LPDIRECTDRAWSURFACE, LPDDSURFACEDESC, LPVOID);
typedef HRESULT (FAR PASCAL * LPDDENUMSURFACESCALLBACK2)(LPDIRECTDRAWSURFACE4, LPDDSURFACEDESC2, LPVOID);
typedef HRESULT (FAR PASCAL * LPDDENUMSURFACESCALLBACK7)(LPDIRECTDRAWSURFACE7, LPDDSURFACEDESC2, LPVOID);
typedef struct _DDARGB
{
BYTE blue;
BYTE green;
BYTE red;
BYTE alpha;
} DDARGB;
typedef DDARGB *LPDDARGB;
typedef struct _DDRGBA
{
BYTE red;
BYTE green;
BYTE blue;
BYTE alpha;
} DDRGBA;
typedef DDRGBA *LPDDRGBA;
typedef struct _DDCOLORKEY
{
DWORD dwColorSpaceLowValue; 
DWORD dwColorSpaceHighValue; 
} DDCOLORKEY;
typedef DDCOLORKEY FAR* LPDDCOLORKEY;
typedef struct _DDBLTFX
{
DWORD dwSize; 
DWORD dwDDFX; 
DWORD dwROP; 
DWORD dwDDROP; 
DWORD dwRotationAngle; 
DWORD dwZBufferOpCode; 
DWORD dwZBufferLow; 
DWORD dwZBufferHigh; 
DWORD dwZBufferBaseDest; 
DWORD dwZDestConstBitDepth; 
union
{
DWORD dwZDestConst; 
LPDIRECTDRAWSURFACE lpDDSZBufferDest; 
} DUMMYUNIONNAMEN(1);
DWORD dwZSrcConstBitDepth; 
union
{
DWORD dwZSrcConst; 
LPDIRECTDRAWSURFACE lpDDSZBufferSrc; 
} DUMMYUNIONNAMEN(2);
DWORD dwAlphaEdgeBlendBitDepth; 
DWORD dwAlphaEdgeBlend; 
DWORD dwReserved;
DWORD dwAlphaDestConstBitDepth; 
union
{
DWORD dwAlphaDestConst; 
LPDIRECTDRAWSURFACE lpDDSAlphaDest; 
} DUMMYUNIONNAMEN(3);
DWORD dwAlphaSrcConstBitDepth; 
union
{
DWORD dwAlphaSrcConst; 
LPDIRECTDRAWSURFACE lpDDSAlphaSrc; 
} DUMMYUNIONNAMEN(4);
union
{
DWORD dwFillColor; 
DWORD dwFillDepth; 
DWORD dwFillPixel; 
LPDIRECTDRAWSURFACE lpDDSPattern; 
} DUMMYUNIONNAMEN(5);
DDCOLORKEY ddckDestColorkey; 
DDCOLORKEY ddckSrcColorkey; 
} DDBLTFX;
typedef DDBLTFX FAR* LPDDBLTFX;
typedef struct _DDSCAPS
{
DWORD dwCaps; 
} DDSCAPS;
typedef DDSCAPS FAR* LPDDSCAPS;
typedef struct _DDOSCAPS
{
DWORD dwCaps; 
} DDOSCAPS;
typedef DDOSCAPS FAR* LPDDOSCAPS;
typedef struct _DDSCAPSEX
{
DWORD dwCaps2;
DWORD dwCaps3;
DWORD dwCaps4;
} DDSCAPSEX, * LPDDSCAPSEX;
typedef struct _DDSCAPS2
{
DWORD dwCaps; 
DWORD dwCaps2;
DWORD dwCaps3;
DWORD dwCaps4;
} DDSCAPS2;
typedef DDSCAPS2 FAR* LPDDSCAPS2;
#define DD_ROP_SPACE (256/32) 
typedef struct _DDCAPS_DX1
{
DWORD dwSize; 
DWORD dwCaps; 
DWORD dwCaps2; 
DWORD dwCKeyCaps; 
DWORD dwFXCaps; 
DWORD dwFXAlphaCaps; 
DWORD dwPalCaps; 
DWORD dwSVCaps; 
DWORD dwAlphaBltConstBitDepths; 
DWORD dwAlphaBltPixelBitDepths; 
DWORD dwAlphaBltSurfaceBitDepths; 
DWORD dwAlphaOverlayConstBitDepths; 
DWORD dwAlphaOverlayPixelBitDepths; 
DWORD dwAlphaOverlaySurfaceBitDepths; 
DWORD dwZBufferBitDepths; 
DWORD dwVidMemTotal; 
DWORD dwVidMemFree; 
DWORD dwMaxVisibleOverlays; 
DWORD dwCurrVisibleOverlays; 
DWORD dwNumFourCCCodes; 
DWORD dwAlignBoundarySrc; 
DWORD dwAlignSizeSrc; 
DWORD dwAlignBoundaryDest; 
DWORD dwAlignSizeDest; 
DWORD dwAlignStrideAlign; 
DWORD dwRops[DD_ROP_SPACE]; 
DDSCAPS ddsCaps; 
DWORD dwMinOverlayStretch; 
DWORD dwMaxOverlayStretch; 
DWORD dwMinLiveVideoStretch; 
DWORD dwMaxLiveVideoStretch; 
DWORD dwMinHwCodecStretch; 
DWORD dwMaxHwCodecStretch; 
DWORD dwReserved1; 
DWORD dwReserved2; 
DWORD dwReserved3; 
} DDCAPS_DX1;
typedef DDCAPS_DX1 FAR* LPDDCAPS_DX1;
typedef struct _DDCAPS_DX3
{
DWORD dwSize; 
DWORD dwCaps; 
DWORD dwCaps2; 
DWORD dwCKeyCaps; 
DWORD dwFXCaps; 
DWORD dwFXAlphaCaps; 
DWORD dwPalCaps; 
DWORD dwSVCaps; 
DWORD dwAlphaBltConstBitDepths; 
DWORD dwAlphaBltPixelBitDepths; 
DWORD dwAlphaBltSurfaceBitDepths; 
DWORD dwAlphaOverlayConstBitDepths; 
DWORD dwAlphaOverlayPixelBitDepths; 
DWORD dwAlphaOverlaySurfaceBitDepths; 
DWORD dwZBufferBitDepths; 
DWORD dwVidMemTotal; 
DWORD dwVidMemFree; 
DWORD dwMaxVisibleOverlays; 
DWORD dwCurrVisibleOverlays; 
DWORD dwNumFourCCCodes; 
DWORD dwAlignBoundarySrc; 
DWORD dwAlignSizeSrc; 
DWORD dwAlignBoundaryDest; 
DWORD dwAlignSizeDest; 
DWORD dwAlignStrideAlign; 
DWORD dwRops[DD_ROP_SPACE]; 
DDSCAPS ddsCaps; 
DWORD dwMinOverlayStretch; 
DWORD dwMaxOverlayStretch; 
DWORD dwMinLiveVideoStretch; 
DWORD dwMaxLiveVideoStretch; 
DWORD dwMinHwCodecStretch; 
DWORD dwMaxHwCodecStretch; 
DWORD dwReserved1; 
DWORD dwReserved2; 
DWORD dwReserved3; 
DWORD dwSVBCaps; 
DWORD dwSVBCKeyCaps; 
DWORD dwSVBFXCaps; 
DWORD dwSVBRops[DD_ROP_SPACE];
DWORD dwVSBCaps; 
DWORD dwVSBCKeyCaps; 
DWORD dwVSBFXCaps; 
DWORD dwVSBRops[DD_ROP_SPACE];
DWORD dwSSBCaps; 
DWORD dwSSBCKeyCaps; 
DWORD dwSSBFXCaps; 
DWORD dwSSBRops[DD_ROP_SPACE];
DWORD dwReserved4; 
DWORD dwReserved5; 
DWORD dwReserved6; 
} DDCAPS_DX3;
typedef DDCAPS_DX3 FAR* LPDDCAPS_DX3;
typedef struct _DDCAPS_DX5
{
DWORD dwSize; 
DWORD dwCaps; 
DWORD dwCaps2; 
DWORD dwCKeyCaps; 
DWORD dwFXCaps; 
DWORD dwFXAlphaCaps; 
DWORD dwPalCaps; 
DWORD dwSVCaps; 
DWORD dwAlphaBltConstBitDepths; 
DWORD dwAlphaBltPixelBitDepths; 
DWORD dwAlphaBltSurfaceBitDepths; 
DWORD dwAlphaOverlayConstBitDepths; 
DWORD dwAlphaOverlayPixelBitDepths; 
DWORD dwAlphaOverlaySurfaceBitDepths; 
DWORD dwZBufferBitDepths; 
DWORD dwVidMemTotal; 
DWORD dwVidMemFree; 
DWORD dwMaxVisibleOverlays; 
DWORD dwCurrVisibleOverlays; 
DWORD dwNumFourCCCodes; 
DWORD dwAlignBoundarySrc; 
DWORD dwAlignSizeSrc; 
DWORD dwAlignBoundaryDest; 
DWORD dwAlignSizeDest; 
DWORD dwAlignStrideAlign; 
DWORD dwRops[DD_ROP_SPACE]; 
DDSCAPS ddsCaps; 
DWORD dwMinOverlayStretch; 
DWORD dwMaxOverlayStretch; 
DWORD dwMinLiveVideoStretch; 
DWORD dwMaxLiveVideoStretch; 
DWORD dwMinHwCodecStretch; 
DWORD dwMaxHwCodecStretch; 
DWORD dwReserved1; 
DWORD dwReserved2; 
DWORD dwReserved3; 
DWORD dwSVBCaps; 
DWORD dwSVBCKeyCaps; 
DWORD dwSVBFXCaps; 
DWORD dwSVBRops[DD_ROP_SPACE];
DWORD dwVSBCaps; 
DWORD dwVSBCKeyCaps; 
DWORD dwVSBFXCaps; 
DWORD dwVSBRops[DD_ROP_SPACE];
DWORD dwSSBCaps; 
DWORD dwSSBCKeyCaps; 
DWORD dwSSBFXCaps; 
DWORD dwSSBRops[DD_ROP_SPACE];
DWORD dwMaxVideoPorts; 
DWORD dwCurrVideoPorts; 
DWORD dwSVBCaps2; 
DWORD dwNLVBCaps; 
DWORD dwNLVBCaps2; 
DWORD dwNLVBCKeyCaps; 
DWORD dwNLVBFXCaps; 
DWORD dwNLVBRops[DD_ROP_SPACE]; 
} DDCAPS_DX5;
typedef DDCAPS_DX5 FAR* LPDDCAPS_DX5;
typedef struct _DDCAPS_DX6
{
DWORD dwSize; 
DWORD dwCaps; 
DWORD dwCaps2; 
DWORD dwCKeyCaps; 
DWORD dwFXCaps; 
DWORD dwFXAlphaCaps; 
DWORD dwPalCaps; 
DWORD dwSVCaps; 
DWORD dwAlphaBltConstBitDepths; 
DWORD dwAlphaBltPixelBitDepths; 
DWORD dwAlphaBltSurfaceBitDepths; 
DWORD dwAlphaOverlayConstBitDepths; 
DWORD dwAlphaOverlayPixelBitDepths; 
DWORD dwAlphaOverlaySurfaceBitDepths; 
DWORD dwZBufferBitDepths; 
DWORD dwVidMemTotal; 
DWORD dwVidMemFree; 
DWORD dwMaxVisibleOverlays; 
DWORD dwCurrVisibleOverlays; 
DWORD dwNumFourCCCodes; 
DWORD dwAlignBoundarySrc; 
DWORD dwAlignSizeSrc; 
DWORD dwAlignBoundaryDest; 
DWORD dwAlignSizeDest; 
DWORD dwAlignStrideAlign; 
DWORD dwRops[DD_ROP_SPACE]; 
DDSCAPS ddsOldCaps; 
DWORD dwMinOverlayStretch; 
DWORD dwMaxOverlayStretch; 
DWORD dwMinLiveVideoStretch; 
DWORD dwMaxLiveVideoStretch; 
DWORD dwMinHwCodecStretch; 
DWORD dwMaxHwCodecStretch; 
DWORD dwReserved1; 
DWORD dwReserved2; 
DWORD dwReserved3; 
DWORD dwSVBCaps; 
DWORD dwSVBCKeyCaps; 
DWORD dwSVBFXCaps; 
DWORD dwSVBRops[DD_ROP_SPACE];
DWORD dwVSBCaps; 
DWORD dwVSBCKeyCaps; 
DWORD dwVSBFXCaps; 
DWORD dwVSBRops[DD_ROP_SPACE];
DWORD dwSSBCaps; 
DWORD dwSSBCKeyCaps; 
DWORD dwSSBFXCaps; 
DWORD dwSSBRops[DD_ROP_SPACE];
DWORD dwMaxVideoPorts; 
DWORD dwCurrVideoPorts; 
DWORD dwSVBCaps2; 
DWORD dwNLVBCaps; 
DWORD dwNLVBCaps2; 
DWORD dwNLVBCKeyCaps; 
DWORD dwNLVBFXCaps; 
DWORD dwNLVBRops[DD_ROP_SPACE]; 
DDSCAPS2 ddsCaps; 
} DDCAPS_DX6;
typedef DDCAPS_DX6 FAR* LPDDCAPS_DX6;
typedef struct _DDCAPS_DX7
{
DWORD dwSize; 
DWORD dwCaps; 
DWORD dwCaps2; 
DWORD dwCKeyCaps; 
DWORD dwFXCaps; 
DWORD dwFXAlphaCaps; 
DWORD dwPalCaps; 
DWORD dwSVCaps; 
DWORD dwAlphaBltConstBitDepths; 
DWORD dwAlphaBltPixelBitDepths; 
DWORD dwAlphaBltSurfaceBitDepths; 
DWORD dwAlphaOverlayConstBitDepths; 
DWORD dwAlphaOverlayPixelBitDepths; 
DWORD dwAlphaOverlaySurfaceBitDepths; 
DWORD dwZBufferBitDepths; 
DWORD dwVidMemTotal; 
DWORD dwVidMemFree; 
DWORD dwMaxVisibleOverlays; 
DWORD dwCurrVisibleOverlays; 
DWORD dwNumFourCCCodes; 
DWORD dwAlignBoundarySrc; 
DWORD dwAlignSizeSrc; 
DWORD dwAlignBoundaryDest; 
DWORD dwAlignSizeDest; 
DWORD dwAlignStrideAlign; 
DWORD dwRops[DD_ROP_SPACE]; 
DDSCAPS ddsOldCaps; 
DWORD dwMinOverlayStretch; 
DWORD dwMaxOverlayStretch; 
DWORD dwMinLiveVideoStretch; 
DWORD dwMaxLiveVideoStretch; 
DWORD dwMinHwCodecStretch; 
DWORD dwMaxHwCodecStretch; 
DWORD dwReserved1; 
DWORD dwReserved2; 
DWORD dwReserved3; 
DWORD dwSVBCaps; 
DWORD dwSVBCKeyCaps; 
DWORD dwSVBFXCaps; 
DWORD dwSVBRops[DD_ROP_SPACE];
DWORD dwVSBCaps; 
DWORD dwVSBCKeyCaps; 
DWORD dwVSBFXCaps; 
DWORD dwVSBRops[DD_ROP_SPACE];
DWORD dwSSBCaps; 
DWORD dwSSBCKeyCaps; 
DWORD dwSSBFXCaps; 
DWORD dwSSBRops[DD_ROP_SPACE];
DWORD dwMaxVideoPorts; 
DWORD dwCurrVideoPorts; 
DWORD dwSVBCaps2; 
DWORD dwNLVBCaps; 
DWORD dwNLVBCaps2; 
DWORD dwNLVBCKeyCaps; 
DWORD dwNLVBFXCaps; 
DWORD dwNLVBRops[DD_ROP_SPACE]; 
DDSCAPS2 ddsCaps; 
} DDCAPS_DX7;
typedef DDCAPS_DX7 FAR* LPDDCAPS_DX7;
#if DIRECTDRAW_VERSION <= 768
typedef DDCAPS_DX3 DDCAPS;
#elif DIRECTDRAW_VERSION <= 1280
typedef DDCAPS_DX5 DDCAPS;
#elif DIRECTDRAW_VERSION <= 1536
typedef DDCAPS_DX6 DDCAPS;
#else
typedef DDCAPS_DX7 DDCAPS;
#endif
typedef DDCAPS FAR* LPDDCAPS;
typedef struct _DDPIXELFORMAT
{
DWORD dwSize; 
DWORD dwFlags; 
DWORD dwFourCC; 
union
{
DWORD dwRGBBitCount; 
DWORD dwYUVBitCount; 
DWORD dwZBufferBitDepth; 
DWORD dwAlphaBitDepth; 
DWORD dwLuminanceBitCount; 
DWORD dwBumpBitCount; 
} DUMMYUNIONNAMEN(1);
union
{
DWORD dwRBitMask; 
DWORD dwYBitMask; 
DWORD dwStencilBitDepth; 
DWORD dwLuminanceBitMask; 
DWORD dwBumpDuBitMask; 
} DUMMYUNIONNAMEN(2);
union
{
DWORD dwGBitMask; 
DWORD dwUBitMask; 
DWORD dwZBitMask; 
DWORD dwBumpDvBitMask; 
} DUMMYUNIONNAMEN(3);
union
{
DWORD dwBBitMask; 
DWORD dwVBitMask; 
DWORD dwStencilBitMask; 
DWORD dwBumpLuminanceBitMask; 
} DUMMYUNIONNAMEN(4);
union
{
DWORD dwRGBAlphaBitMask; 
DWORD dwYUVAlphaBitMask; 
DWORD dwLuminanceAlphaBitMask;
DWORD dwRGBZBitMask; 
DWORD dwYUVZBitMask; 
} DUMMYUNIONNAMEN(5);
} DDPIXELFORMAT;
typedef DDPIXELFORMAT FAR* LPDDPIXELFORMAT;
typedef struct _DDOVERLAYFX
{
DWORD dwSize; 
DWORD dwAlphaEdgeBlendBitDepth; 
DWORD dwAlphaEdgeBlend; 
DWORD dwReserved;
DWORD dwAlphaDestConstBitDepth; 
union
{
DWORD dwAlphaDestConst; 
LPDIRECTDRAWSURFACE lpDDSAlphaDest; 
} DUMMYUNIONNAMEN(1);
DWORD dwAlphaSrcConstBitDepth; 
union
{
DWORD dwAlphaSrcConst; 
LPDIRECTDRAWSURFACE lpDDSAlphaSrc; 
} DUMMYUNIONNAMEN(2);
DDCOLORKEY dckDestColorkey; 
DDCOLORKEY dckSrcColorkey; 
DWORD dwDDFX; 
DWORD dwFlags; 
} DDOVERLAYFX;
typedef DDOVERLAYFX *LPDDOVERLAYFX;
typedef struct _DDBLTBATCH
{
LPRECT lprDest;
LPDIRECTDRAWSURFACE lpDDSSrc;
LPRECT lprSrc;
DWORD dwFlags;
LPDDBLTFX lpDDBltFx;
} DDBLTBATCH;
typedef DDBLTBATCH * LPDDBLTBATCH;
typedef struct _DDGAMMARAMP
{
WORD red[256];
WORD green[256];
WORD blue[256];
} DDGAMMARAMP;
typedef DDGAMMARAMP * LPDDGAMMARAMP;
#define MAX_DDDEVICEID_STRING 512
typedef struct tagDDDEVICEIDENTIFIER
{
char szDriver[MAX_DDDEVICEID_STRING];
char szDescription[MAX_DDDEVICEID_STRING];
#ifdef _WIN32
LARGE_INTEGER liDriverVersion; 
#else
DWORD dwDriverVersionLowPart; 
DWORD dwDriverVersionHighPart;
#endif
DWORD dwVendorId;
DWORD dwDeviceId;
DWORD dwSubSysId;
DWORD dwRevision;
GUID guidDeviceIdentifier;
} DDDEVICEIDENTIFIER, * LPDDDEVICEIDENTIFIER;
typedef struct tagDDDEVICEIDENTIFIER2
{
char szDriver[MAX_DDDEVICEID_STRING];
char szDescription[MAX_DDDEVICEID_STRING];
#ifdef _WIN32
LARGE_INTEGER liDriverVersion; 
#else
DWORD dwDriverVersionLowPart; 
DWORD dwDriverVersionHighPart;
#endif
DWORD dwVendorId;
DWORD dwDeviceId;
DWORD dwSubSysId;
DWORD dwRevision;
GUID guidDeviceIdentifier;
DWORD dwWHQLLevel;
} DDDEVICEIDENTIFIER2, * LPDDDEVICEIDENTIFIER2;
#define DDGDI_GETHOSTIDENTIFIER 1
#define GET_WHQL_YEAR(dwWHQLLevel) \
((dwWHQLLevel) / 0x10000)
#define GET_WHQL_MONTH(dwWHQLLevel) \
(((dwWHQLLevel) / 256) & 255)
#define GET_WHQL_DAY(dwWHQLLevel) \
((dwWHQLLevel) & 255)
typedef DWORD (FAR PASCAL *LPCLIPPERCALLBACK)(LPDIRECTDRAWCLIPPER lpDDClipper, HWND hWnd, DWORD code, LPVOID lpContext);
#ifdef STREAMING
typedef DWORD (FAR PASCAL *LPSURFACESTREAMINGCALLBACK)(DWORD);
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDraw
DECLARE_INTERFACE_(IDirectDraw, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(Compact)(THIS) ;
STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown *) ;
STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown *) ;
STDMETHOD(CreateSurface)(THIS_ LPDDSURFACEDESC, LPDIRECTDRAWSURFACE *, IUnknown *) ;
STDMETHOD(DuplicateSurface)(THIS_ LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE *) ;
STDMETHOD(EnumDisplayModes)(THIS_ DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMMODESCALLBACK) ;
STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC, LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(FlipToGDISurface)(THIS) ;
STDMETHOD(GetCaps)(THIS_ LPDDCAPS, LPDDCAPS) ;
STDMETHOD(GetDisplayMode)(THIS_ LPDDSURFACEDESC) ;
STDMETHOD(GetFourCCCodes)(THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE *) ;
STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) ;
STDMETHOD(GetScanLine)(THIS_ LPDWORD) ;
STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL) ;
STDMETHOD(Initialize)(THIS_ GUID *) ;
STDMETHOD(RestoreDisplayMode)(THIS) ;
STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) ;
STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD) ;
STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE) ;
};
#define IDirectDraw_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDraw_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDraw_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDraw_Compact(p) (p)->lpVtbl->Compact(p)
#define IDirectDraw_CreateClipper(p, a, b, c) (p)->lpVtbl->CreateClipper(p, a, b, c)
#define IDirectDraw_CreatePalette(p, a, b, c, d) (p)->lpVtbl->CreatePalette(p, a, b, c, d)
#define IDirectDraw_CreateSurface(p, a, b, c) (p)->lpVtbl->CreateSurface(p, a, b, c)
#define IDirectDraw_DuplicateSurface(p, a, b) (p)->lpVtbl->DuplicateSurface(p, a, b)
#define IDirectDraw_EnumDisplayModes(p, a, b, c, d) (p)->lpVtbl->EnumDisplayModes(p, a, b, c, d)
#define IDirectDraw_EnumSurfaces(p, a, b, c, d) (p)->lpVtbl->EnumSurfaces(p, a, b, c, d)
#define IDirectDraw_FlipToGDISurface(p) (p)->lpVtbl->FlipToGDISurface(p)
#define IDirectDraw_GetCaps(p, a, b) (p)->lpVtbl->GetCaps(p, a, b)
#define IDirectDraw_GetDisplayMode(p, a) (p)->lpVtbl->GetDisplayMode(p, a)
#define IDirectDraw_GetFourCCCodes(p, a, b) (p)->lpVtbl->GetFourCCCodes(p, a, b)
#define IDirectDraw_GetGDISurface(p, a) (p)->lpVtbl->GetGDISurface(p, a)
#define IDirectDraw_GetMonitorFrequency(p, a) (p)->lpVtbl->GetMonitorFrequency(p, a)
#define IDirectDraw_GetScanLine(p, a) (p)->lpVtbl->GetScanLine(p, a)
#define IDirectDraw_GetVerticalBlankStatus(p, a) (p)->lpVtbl->GetVerticalBlankStatus(p, a)
#define IDirectDraw_Initialize(p, a) (p)->lpVtbl->Initialize(p, a)
#define IDirectDraw_RestoreDisplayMode(p) (p)->lpVtbl->RestoreDisplayMode(p)
#define IDirectDraw_SetCooperativeLevel(p, a, b) (p)->lpVtbl->SetCooperativeLevel(p, a, b)
#define IDirectDraw_SetDisplayMode(p, a, b, c) (p)->lpVtbl->SetDisplayMode(p, a, b, c)
#define IDirectDraw_WaitForVerticalBlank(p, a, b) (p)->lpVtbl->WaitForVerticalBlank(p, a, b)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDraw2
DECLARE_INTERFACE_(IDirectDraw2, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(Compact)(THIS) ;
STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown *) ;
STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown *) ;
STDMETHOD(CreateSurface)(THIS_ LPDDSURFACEDESC, LPDIRECTDRAWSURFACE *, IUnknown *) ;
STDMETHOD(DuplicateSurface)(THIS_ LPDIRECTDRAWSURFACE, LPDIRECTDRAWSURFACE *) ;
STDMETHOD(EnumDisplayModes)(THIS_ DWORD, LPDDSURFACEDESC, LPVOID, LPDDENUMMODESCALLBACK) ;
STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC, LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(FlipToGDISurface)(THIS) ;
STDMETHOD(GetCaps)(THIS_ LPDDCAPS, LPDDCAPS) ;
STDMETHOD(GetDisplayMode)(THIS_ LPDDSURFACEDESC) ;
STDMETHOD(GetFourCCCodes)(THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE *) ;
STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) ;
STDMETHOD(GetScanLine)(THIS_ LPDWORD) ;
STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL) ;
STDMETHOD(Initialize)(THIS_ GUID *) ;
STDMETHOD(RestoreDisplayMode)(THIS) ;
STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) ;
STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD, DWORD, DWORD) ;
STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE) ;
STDMETHOD(GetAvailableVidMem)(THIS_ LPDDSCAPS, LPDWORD, LPDWORD) ;
};
#define IDirectDraw2_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDraw2_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDraw2_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDraw2_Compact(p) (p)->lpVtbl->Compact(p)
#define IDirectDraw2_CreateClipper(p, a, b, c) (p)->lpVtbl->CreateClipper(p, a, b, c)
#define IDirectDraw2_CreatePalette(p, a, b, c, d) (p)->lpVtbl->CreatePalette(p, a, b, c, d)
#define IDirectDraw2_CreateSurface(p, a, b, c) (p)->lpVtbl->CreateSurface(p, a, b, c)
#define IDirectDraw2_DuplicateSurface(p, a, b) (p)->lpVtbl->DuplicateSurface(p, a, b)
#define IDirectDraw2_EnumDisplayModes(p, a, b, c, d) (p)->lpVtbl->EnumDisplayModes(p, a, b, c, d)
#define IDirectDraw2_EnumSurfaces(p, a, b, c, d) (p)->lpVtbl->EnumSurfaces(p, a, b, c, d)
#define IDirectDraw2_FlipToGDISurface(p) (p)->lpVtbl->FlipToGDISurface(p)
#define IDirectDraw2_GetCaps(p, a, b) (p)->lpVtbl->GetCaps(p, a, b)
#define IDirectDraw2_GetDisplayMode(p, a) (p)->lpVtbl->GetDisplayMode(p, a)
#define IDirectDraw2_GetFourCCCodes(p, a, b) (p)->lpVtbl->GetFourCCCodes(p, a, b)
#define IDirectDraw2_GetGDISurface(p, a) (p)->lpVtbl->GetGDISurface(p, a)
#define IDirectDraw2_GetMonitorFrequency(p, a) (p)->lpVtbl->GetMonitorFrequency(p, a)
#define IDirectDraw2_GetScanLine(p, a) (p)->lpVtbl->GetScanLine(p, a)
#define IDirectDraw2_GetVerticalBlankStatus(p, a) (p)->lpVtbl->GetVerticalBlankStatus(p, a)
#define IDirectDraw2_Initialize(p, a) (p)->lpVtbl->Initialize(p, a)
#define IDirectDraw2_RestoreDisplayMode(p) (p)->lpVtbl->RestoreDisplayMode(p)
#define IDirectDraw2_SetCooperativeLevel(p, a, b) (p)->lpVtbl->SetCooperativeLevel(p, a, b)
#define IDirectDraw2_SetDisplayMode(p, a, b, c, d, e) (p)->lpVtbl->SetDisplayMode(p, a, b, c, d, e)
#define IDirectDraw2_WaitForVerticalBlank(p, a, b) (p)->lpVtbl->WaitForVerticalBlank(p, a, b)
#define IDirectDraw2_GetAvailableVidMem(p, a, b, c) (p)->lpVtbl->GetAvailableVidMem(p, a, b, c)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDraw4
DECLARE_INTERFACE_(IDirectDraw4, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(Compact)(THIS) ;
STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown *) ;
STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown *) ;
STDMETHOD(CreateSurface)(THIS_ LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE4 *, IUnknown *) ;
STDMETHOD(DuplicateSurface)(THIS_ LPDIRECTDRAWSURFACE4, LPDIRECTDRAWSURFACE4 *) ;
STDMETHOD(EnumDisplayModes)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2) ;
STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID,LPDDENUMSURFACESCALLBACK2) ;
STDMETHOD(FlipToGDISurface)(THIS) ;
STDMETHOD(GetCaps)(THIS_ LPDDCAPS, LPDDCAPS) ;
STDMETHOD(GetDisplayMode)(THIS_ LPDDSURFACEDESC2) ;
STDMETHOD(GetFourCCCodes)(THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE4 *) ;
STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) ;
STDMETHOD(GetScanLine)(THIS_ LPDWORD) ;
STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL) ;
STDMETHOD(Initialize)(THIS_ GUID *) ;
STDMETHOD(RestoreDisplayMode)(THIS) ;
STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) ;
STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD, DWORD, DWORD) ;
STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE) ;
STDMETHOD(GetAvailableVidMem)(THIS_ LPDDSCAPS2, LPDWORD, LPDWORD) ;
STDMETHOD(GetSurfaceFromDC) (THIS_ HDC, LPDIRECTDRAWSURFACE4 *) ;
STDMETHOD(RestoreAllSurfaces)(THIS) ;
STDMETHOD(TestCooperativeLevel)(THIS) ;
STDMETHOD(GetDeviceIdentifier)(THIS_ LPDDDEVICEIDENTIFIER, DWORD) ;
};
#define IDirectDraw4_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDraw4_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDraw4_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDraw4_Compact(p) (p)->lpVtbl->Compact(p)
#define IDirectDraw4_CreateClipper(p, a, b, c) (p)->lpVtbl->CreateClipper(p, a, b, c)
#define IDirectDraw4_CreatePalette(p, a, b, c, d) (p)->lpVtbl->CreatePalette(p, a, b, c, d)
#define IDirectDraw4_CreateSurface(p, a, b, c) (p)->lpVtbl->CreateSurface(p, a, b, c)
#define IDirectDraw4_DuplicateSurface(p, a, b) (p)->lpVtbl->DuplicateSurface(p, a, b)
#define IDirectDraw4_EnumDisplayModes(p, a, b, c, d) (p)->lpVtbl->EnumDisplayModes(p, a, b, c, d)
#define IDirectDraw4_EnumSurfaces(p, a, b, c, d) (p)->lpVtbl->EnumSurfaces(p, a, b, c, d)
#define IDirectDraw4_FlipToGDISurface(p) (p)->lpVtbl->FlipToGDISurface(p)
#define IDirectDraw4_GetCaps(p, a, b) (p)->lpVtbl->GetCaps(p, a, b)
#define IDirectDraw4_GetDisplayMode(p, a) (p)->lpVtbl->GetDisplayMode(p, a)
#define IDirectDraw4_GetFourCCCodes(p, a, b) (p)->lpVtbl->GetFourCCCodes(p, a, b)
#define IDirectDraw4_GetGDISurface(p, a) (p)->lpVtbl->GetGDISurface(p, a)
#define IDirectDraw4_GetMonitorFrequency(p, a) (p)->lpVtbl->GetMonitorFrequency(p, a)
#define IDirectDraw4_GetScanLine(p, a) (p)->lpVtbl->GetScanLine(p, a)
#define IDirectDraw4_GetVerticalBlankStatus(p, a) (p)->lpVtbl->GetVerticalBlankStatus(p, a)
#define IDirectDraw4_Initialize(p, a) (p)->lpVtbl->Initialize(p, a)
#define IDirectDraw4_RestoreDisplayMode(p) (p)->lpVtbl->RestoreDisplayMode(p)
#define IDirectDraw4_SetCooperativeLevel(p, a, b) (p)->lpVtbl->SetCooperativeLevel(p, a, b)
#define IDirectDraw4_SetDisplayMode(p, a, b, c, d, e) (p)->lpVtbl->SetDisplayMode(p, a, b, c, d, e)
#define IDirectDraw4_WaitForVerticalBlank(p, a, b) (p)->lpVtbl->WaitForVerticalBlank(p, a, b)
#define IDirectDraw4_GetAvailableVidMem(p, a, b, c) (p)->lpVtbl->GetAvailableVidMem(p, a, b, c)
#define IDirectDraw4_GetSurfaceFromDC(p, a, b) (p)->lpVtbl->GetSurfaceFromDC(p, a, b)
#define IDirectDraw4_RestoreAllSurfaces(p) (p)->lpVtbl->RestoreAllSurfaces(p)
#define IDirectDraw4_TestCooperativeLevel(p) (p)->lpVtbl->TestCooperativeLevel(p)
#define IDirectDraw4_GetDeviceIdentifier(p,a,b) (p)->lpVtbl->GetDeviceIdentifier(p,a,b)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDraw7
DECLARE_INTERFACE_(IDirectDraw7, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(Compact)(THIS) ;
STDMETHOD(CreateClipper)(THIS_ DWORD, LPDIRECTDRAWCLIPPER FAR*, IUnknown *) ;
STDMETHOD(CreatePalette)(THIS_ DWORD, LPPALETTEENTRY, LPDIRECTDRAWPALETTE FAR*, IUnknown *) ;
STDMETHOD(CreateSurface)(THIS_ LPDDSURFACEDESC2, LPDIRECTDRAWSURFACE7 *, IUnknown *) ;
STDMETHOD(DuplicateSurface)(THIS_ LPDIRECTDRAWSURFACE7, LPDIRECTDRAWSURFACE7 *) ;
STDMETHOD(EnumDisplayModes)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID, LPDDENUMMODESCALLBACK2) ;
STDMETHOD(EnumSurfaces)(THIS_ DWORD, LPDDSURFACEDESC2, LPVOID,LPDDENUMSURFACESCALLBACK7) ;
STDMETHOD(FlipToGDISurface)(THIS) ;
STDMETHOD(GetCaps)(THIS_ LPDDCAPS, LPDDCAPS) ;
STDMETHOD(GetDisplayMode)(THIS_ LPDDSURFACEDESC2) ;
STDMETHOD(GetFourCCCodes)(THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetGDISurface)(THIS_ LPDIRECTDRAWSURFACE7 *) ;
STDMETHOD(GetMonitorFrequency)(THIS_ LPDWORD) ;
STDMETHOD(GetScanLine)(THIS_ LPDWORD) ;
STDMETHOD(GetVerticalBlankStatus)(THIS_ LPBOOL) ;
STDMETHOD(Initialize)(THIS_ GUID *) ;
STDMETHOD(RestoreDisplayMode)(THIS) ;
STDMETHOD(SetCooperativeLevel)(THIS_ HWND, DWORD) ;
STDMETHOD(SetDisplayMode)(THIS_ DWORD, DWORD,DWORD, DWORD, DWORD) ;
STDMETHOD(WaitForVerticalBlank)(THIS_ DWORD, HANDLE) ;
STDMETHOD(GetAvailableVidMem)(THIS_ LPDDSCAPS2, LPDWORD, LPDWORD) ;
STDMETHOD(GetSurfaceFromDC) (THIS_ HDC, LPDIRECTDRAWSURFACE7 *) ;
STDMETHOD(RestoreAllSurfaces)(THIS) ;
STDMETHOD(TestCooperativeLevel)(THIS) ;
STDMETHOD(GetDeviceIdentifier)(THIS_ LPDDDEVICEIDENTIFIER2, DWORD) ;
STDMETHOD(StartModeTest)(THIS_ LPSIZE, DWORD, DWORD) ;
STDMETHOD(EvaluateMode)(THIS_ DWORD, DWORD *) ;
};
#define IDirectDraw7_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDraw7_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDraw7_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDraw7_Compact(p) (p)->lpVtbl->Compact(p)
#define IDirectDraw7_CreateClipper(p, a, b, c) (p)->lpVtbl->CreateClipper(p, a, b, c)
#define IDirectDraw7_CreatePalette(p, a, b, c, d) (p)->lpVtbl->CreatePalette(p, a, b, c, d)
#define IDirectDraw7_CreateSurface(p, a, b, c) (p)->lpVtbl->CreateSurface(p, a, b, c)
#define IDirectDraw7_DuplicateSurface(p, a, b) (p)->lpVtbl->DuplicateSurface(p, a, b)
#define IDirectDraw7_EnumDisplayModes(p, a, b, c, d) (p)->lpVtbl->EnumDisplayModes(p, a, b, c, d)
#define IDirectDraw7_EnumSurfaces(p, a, b, c, d) (p)->lpVtbl->EnumSurfaces(p, a, b, c, d)
#define IDirectDraw7_FlipToGDISurface(p) (p)->lpVtbl->FlipToGDISurface(p)
#define IDirectDraw7_GetCaps(p, a, b) (p)->lpVtbl->GetCaps(p, a, b)
#define IDirectDraw7_GetDisplayMode(p, a) (p)->lpVtbl->GetDisplayMode(p, a)
#define IDirectDraw7_GetFourCCCodes(p, a, b) (p)->lpVtbl->GetFourCCCodes(p, a, b)
#define IDirectDraw7_GetGDISurface(p, a) (p)->lpVtbl->GetGDISurface(p, a)
#define IDirectDraw7_GetMonitorFrequency(p, a) (p)->lpVtbl->GetMonitorFrequency(p, a)
#define IDirectDraw7_GetScanLine(p, a) (p)->lpVtbl->GetScanLine(p, a)
#define IDirectDraw7_GetVerticalBlankStatus(p, a) (p)->lpVtbl->GetVerticalBlankStatus(p, a)
#define IDirectDraw7_Initialize(p, a) (p)->lpVtbl->Initialize(p, a)
#define IDirectDraw7_RestoreDisplayMode(p) (p)->lpVtbl->RestoreDisplayMode(p)
#define IDirectDraw7_SetCooperativeLevel(p, a, b) (p)->lpVtbl->SetCooperativeLevel(p, a, b)
#define IDirectDraw7_SetDisplayMode(p, a, b, c, d, e) (p)->lpVtbl->SetDisplayMode(p, a, b, c, d, e)
#define IDirectDraw7_WaitForVerticalBlank(p, a, b) (p)->lpVtbl->WaitForVerticalBlank(p, a, b)
#define IDirectDraw7_GetAvailableVidMem(p, a, b, c) (p)->lpVtbl->GetAvailableVidMem(p, a, b, c)
#define IDirectDraw7_GetSurfaceFromDC(p, a, b) (p)->lpVtbl->GetSurfaceFromDC(p, a, b)
#define IDirectDraw7_RestoreAllSurfaces(p) (p)->lpVtbl->RestoreAllSurfaces(p)
#define IDirectDraw7_TestCooperativeLevel(p) (p)->lpVtbl->TestCooperativeLevel(p)
#define IDirectDraw7_GetDeviceIdentifier(p,a,b) (p)->lpVtbl->GetDeviceIdentifier(p,a,b)
#define IDirectDraw7_StartModeTest(p,a,b,c) (p)->lpVtbl->StartModeTest(p,a,b,c)
#define IDirectDraw7_EvaluateMode(p,a,b) (p)->lpVtbl->EvaluateMode(p,a,b)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDrawPalette
DECLARE_INTERFACE_(IDirectDrawPalette, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetCaps)(THIS_ LPDWORD) ;
STDMETHOD(GetEntries)(THIS_ DWORD,DWORD,DWORD,LPPALETTEENTRY) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, DWORD, LPPALETTEENTRY) ;
STDMETHOD(SetEntries)(THIS_ DWORD,DWORD,DWORD,LPPALETTEENTRY) ;
};
#define IDirectDrawPalette_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDrawPalette_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawPalette_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawPalette_GetCaps(p, a) (p)->lpVtbl->GetCaps(p, a)
#define IDirectDrawPalette_GetEntries(p, a, b, c, d) (p)->lpVtbl->GetEntries(p, a, b, c, d)
#define IDirectDrawPalette_Initialize(p, a, b, c) (p)->lpVtbl->Initialize(p, a, b, c)
#define IDirectDrawPalette_SetEntries(p, a, b, c, d) (p)->lpVtbl->SetEntries(p, a, b, c, d)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDrawClipper
DECLARE_INTERFACE_(IDirectDrawClipper, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetClipList)(THIS_ LPRECT, LPRGNDATA, LPDWORD) ;
STDMETHOD(GetHWnd)(THIS_ HWND *) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, DWORD) ;
STDMETHOD(IsClipListChanged)(THIS_ BOOL *) ;
STDMETHOD(SetClipList)(THIS_ LPRGNDATA,DWORD) ;
STDMETHOD(SetHWnd)(THIS_ DWORD, HWND) ;
};
#define IDirectDrawClipper_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDrawClipper_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawClipper_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawClipper_GetClipList(p, a, b, c) (p)->lpVtbl->GetClipList(p, a, b, c)
#define IDirectDrawClipper_GetHWnd(p, a) (p)->lpVtbl->GetHWnd(p, a)
#define IDirectDrawClipper_Initialize(p, a, b) (p)->lpVtbl->Initialize(p, a, b)
#define IDirectDrawClipper_IsClipListChanged(p, a) (p)->lpVtbl->IsClipListChanged(p, a)
#define IDirectDrawClipper_SetClipList(p, a, b) (p)->lpVtbl->SetClipList(p, a, b)
#define IDirectDrawClipper_SetHWnd(p, a, b) (p)->lpVtbl->SetHWnd(p, a, b)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDrawSurface
DECLARE_INTERFACE_(IDirectDrawSurface, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE) ;
STDMETHOD(AddOverlayDirtyRect)(THIS_ LPRECT) ;
STDMETHOD(Blt)(THIS_ LPRECT,LPDIRECTDRAWSURFACE, LPRECT,DWORD, LPDDBLTFX) ;
STDMETHOD(BltBatch)(THIS_ LPDDBLTBATCH, DWORD, DWORD) ;
STDMETHOD(BltFast)(THIS_ DWORD,DWORD,LPDIRECTDRAWSURFACE, LPRECT,DWORD) ;
STDMETHOD(DeleteAttachedSurface)(THIS_ DWORD,LPDIRECTDRAWSURFACE) ;
STDMETHOD(EnumAttachedSurfaces)(THIS_ LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(EnumOverlayZOrders)(THIS_ DWORD,LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(Flip)(THIS_ LPDIRECTDRAWSURFACE, DWORD) ;
STDMETHOD(GetAttachedSurface)(THIS_ LPDDSCAPS, LPDIRECTDRAWSURFACE *) ;
STDMETHOD(GetBltStatus)(THIS_ DWORD) ;
STDMETHOD(GetCaps)(THIS_ LPDDSCAPS) ;
STDMETHOD(GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR*) ;
STDMETHOD(GetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(GetDC)(THIS_ HDC *) ;
STDMETHOD(GetFlipStatus)(THIS_ DWORD) ;
STDMETHOD(GetOverlayPosition)(THIS_ LPLONG, LPLONG) ;
STDMETHOD(GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR*) ;
STDMETHOD(GetPixelFormat)(THIS_ LPDDPIXELFORMAT) ;
STDMETHOD(GetSurfaceDesc)(THIS_ LPDDSURFACEDESC) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, LPDDSURFACEDESC) ;
STDMETHOD(IsLost)(THIS) ;
STDMETHOD(Lock)(THIS_ LPRECT,LPDDSURFACEDESC,DWORD,HANDLE) ;
STDMETHOD(ReleaseDC)(THIS_ HDC) ;
STDMETHOD(Restore)(THIS) ;
STDMETHOD(SetClipper)(THIS_ LPDIRECTDRAWCLIPPER) ;
STDMETHOD(SetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(SetOverlayPosition)(THIS_ LONG, LONG) ;
STDMETHOD(SetPalette)(THIS_ LPDIRECTDRAWPALETTE) ;
STDMETHOD(Unlock)(THIS_ LPVOID) ;
STDMETHOD(UpdateOverlay)(THIS_ LPRECT, LPDIRECTDRAWSURFACE,LPRECT,DWORD, LPDDOVERLAYFX) ;
STDMETHOD(UpdateOverlayDisplay)(THIS_ DWORD) ;
STDMETHOD(UpdateOverlayZOrder)(THIS_ DWORD, LPDIRECTDRAWSURFACE) ;
};
#define IDirectDrawSurface_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectDrawSurface_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawSurface_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawSurface_AddAttachedSurface(p,a) (p)->lpVtbl->AddAttachedSurface(p,a)
#define IDirectDrawSurface_AddOverlayDirtyRect(p,a) (p)->lpVtbl->AddOverlayDirtyRect(p,a)
#define IDirectDrawSurface_Blt(p,a,b,c,d,e) (p)->lpVtbl->Blt(p,a,b,c,d,e)
#define IDirectDrawSurface_BltBatch(p,a,b,c) (p)->lpVtbl->BltBatch(p,a,b,c)
#define IDirectDrawSurface_BltFast(p,a,b,c,d,e) (p)->lpVtbl->BltFast(p,a,b,c,d,e)
#define IDirectDrawSurface_DeleteAttachedSurface(p,a,b) (p)->lpVtbl->DeleteAttachedSurface(p,a,b)
#define IDirectDrawSurface_EnumAttachedSurfaces(p,a,b) (p)->lpVtbl->EnumAttachedSurfaces(p,a,b)
#define IDirectDrawSurface_EnumOverlayZOrders(p,a,b,c) (p)->lpVtbl->EnumOverlayZOrders(p,a,b,c)
#define IDirectDrawSurface_Flip(p,a,b) (p)->lpVtbl->Flip(p,a,b)
#define IDirectDrawSurface_GetAttachedSurface(p,a,b) (p)->lpVtbl->GetAttachedSurface(p,a,b)
#define IDirectDrawSurface_GetBltStatus(p,a) (p)->lpVtbl->GetBltStatus(p,a)
#define IDirectDrawSurface_GetCaps(p,b) (p)->lpVtbl->GetCaps(p,b)
#define IDirectDrawSurface_GetClipper(p,a) (p)->lpVtbl->GetClipper(p,a)
#define IDirectDrawSurface_GetColorKey(p,a,b) (p)->lpVtbl->GetColorKey(p,a,b)
#define IDirectDrawSurface_GetDC(p,a) (p)->lpVtbl->GetDC(p,a)
#define IDirectDrawSurface_GetFlipStatus(p,a) (p)->lpVtbl->GetFlipStatus(p,a)
#define IDirectDrawSurface_GetOverlayPosition(p,a,b) (p)->lpVtbl->GetOverlayPosition(p,a,b)
#define IDirectDrawSurface_GetPalette(p,a) (p)->lpVtbl->GetPalette(p,a)
#define IDirectDrawSurface_GetPixelFormat(p,a) (p)->lpVtbl->GetPixelFormat(p,a)
#define IDirectDrawSurface_GetSurfaceDesc(p,a) (p)->lpVtbl->GetSurfaceDesc(p,a)
#define IDirectDrawSurface_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectDrawSurface_IsLost(p) (p)->lpVtbl->IsLost(p)
#define IDirectDrawSurface_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirectDrawSurface_ReleaseDC(p,a) (p)->lpVtbl->ReleaseDC(p,a)
#define IDirectDrawSurface_Restore(p) (p)->lpVtbl->Restore(p)
#define IDirectDrawSurface_SetClipper(p,a) (p)->lpVtbl->SetClipper(p,a)
#define IDirectDrawSurface_SetColorKey(p,a,b) (p)->lpVtbl->SetColorKey(p,a,b)
#define IDirectDrawSurface_SetOverlayPosition(p,a,b) (p)->lpVtbl->SetOverlayPosition(p,a,b)
#define IDirectDrawSurface_SetPalette(p,a) (p)->lpVtbl->SetPalette(p,a)
#define IDirectDrawSurface_Unlock(p,b) (p)->lpVtbl->Unlock(p,b)
#define IDirectDrawSurface_UpdateOverlay(p,a,b,c,d,e) (p)->lpVtbl->UpdateOverlay(p,a,b,c,d,e)
#define IDirectDrawSurface_UpdateOverlayDisplay(p,a) (p)->lpVtbl->UpdateOverlayDisplay(p,a)
#define IDirectDrawSurface_UpdateOverlayZOrder(p,a,b) (p)->lpVtbl->UpdateOverlayZOrder(p,a,b)
#undef INTERFACE
#define INTERFACE IDirectDrawSurface2
DECLARE_INTERFACE_(IDirectDrawSurface2, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE2) ;
STDMETHOD(AddOverlayDirtyRect)(THIS_ LPRECT) ;
STDMETHOD(Blt)(THIS_ LPRECT,LPDIRECTDRAWSURFACE2, LPRECT,DWORD, LPDDBLTFX) ;
STDMETHOD(BltBatch)(THIS_ LPDDBLTBATCH, DWORD, DWORD) ;
STDMETHOD(BltFast)(THIS_ DWORD,DWORD,LPDIRECTDRAWSURFACE2, LPRECT,DWORD) ;
STDMETHOD(DeleteAttachedSurface)(THIS_ DWORD,LPDIRECTDRAWSURFACE2) ;
STDMETHOD(EnumAttachedSurfaces)(THIS_ LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(EnumOverlayZOrders)(THIS_ DWORD,LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(Flip)(THIS_ LPDIRECTDRAWSURFACE2, DWORD) ;
STDMETHOD(GetAttachedSurface)(THIS_ LPDDSCAPS, LPDIRECTDRAWSURFACE2 *) ;
STDMETHOD(GetBltStatus)(THIS_ DWORD) ;
STDMETHOD(GetCaps)(THIS_ LPDDSCAPS) ;
STDMETHOD(GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR*) ;
STDMETHOD(GetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(GetDC)(THIS_ HDC *) ;
STDMETHOD(GetFlipStatus)(THIS_ DWORD) ;
STDMETHOD(GetOverlayPosition)(THIS_ LPLONG, LPLONG) ;
STDMETHOD(GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR*) ;
STDMETHOD(GetPixelFormat)(THIS_ LPDDPIXELFORMAT) ;
STDMETHOD(GetSurfaceDesc)(THIS_ LPDDSURFACEDESC) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, LPDDSURFACEDESC) ;
STDMETHOD(IsLost)(THIS) ;
STDMETHOD(Lock)(THIS_ LPRECT,LPDDSURFACEDESC,DWORD,HANDLE) ;
STDMETHOD(ReleaseDC)(THIS_ HDC) ;
STDMETHOD(Restore)(THIS) ;
STDMETHOD(SetClipper)(THIS_ LPDIRECTDRAWCLIPPER) ;
STDMETHOD(SetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(SetOverlayPosition)(THIS_ LONG, LONG) ;
STDMETHOD(SetPalette)(THIS_ LPDIRECTDRAWPALETTE) ;
STDMETHOD(Unlock)(THIS_ LPVOID) ;
STDMETHOD(UpdateOverlay)(THIS_ LPRECT, LPDIRECTDRAWSURFACE2,LPRECT,DWORD, LPDDOVERLAYFX) ;
STDMETHOD(UpdateOverlayDisplay)(THIS_ DWORD) ;
STDMETHOD(UpdateOverlayZOrder)(THIS_ DWORD, LPDIRECTDRAWSURFACE2) ;
STDMETHOD(GetDDInterface)(THIS_ LPVOID *) ;
STDMETHOD(PageLock)(THIS_ DWORD) ;
STDMETHOD(PageUnlock)(THIS_ DWORD) ;
};
#define IDirectDrawSurface2_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectDrawSurface2_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawSurface2_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawSurface2_AddAttachedSurface(p,a) (p)->lpVtbl->AddAttachedSurface(p,a)
#define IDirectDrawSurface2_AddOverlayDirtyRect(p,a) (p)->lpVtbl->AddOverlayDirtyRect(p,a)
#define IDirectDrawSurface2_Blt(p,a,b,c,d,e) (p)->lpVtbl->Blt(p,a,b,c,d,e)
#define IDirectDrawSurface2_BltBatch(p,a,b,c) (p)->lpVtbl->BltBatch(p,a,b,c)
#define IDirectDrawSurface2_BltFast(p,a,b,c,d,e) (p)->lpVtbl->BltFast(p,a,b,c,d,e)
#define IDirectDrawSurface2_DeleteAttachedSurface(p,a,b) (p)->lpVtbl->DeleteAttachedSurface(p,a,b)
#define IDirectDrawSurface2_EnumAttachedSurfaces(p,a,b) (p)->lpVtbl->EnumAttachedSurfaces(p,a,b)
#define IDirectDrawSurface2_EnumOverlayZOrders(p,a,b,c) (p)->lpVtbl->EnumOverlayZOrders(p,a,b,c)
#define IDirectDrawSurface2_Flip(p,a,b) (p)->lpVtbl->Flip(p,a,b)
#define IDirectDrawSurface2_GetAttachedSurface(p,a,b) (p)->lpVtbl->GetAttachedSurface(p,a,b)
#define IDirectDrawSurface2_GetBltStatus(p,a) (p)->lpVtbl->GetBltStatus(p,a)
#define IDirectDrawSurface2_GetCaps(p,b) (p)->lpVtbl->GetCaps(p,b)
#define IDirectDrawSurface2_GetClipper(p,a) (p)->lpVtbl->GetClipper(p,a)
#define IDirectDrawSurface2_GetColorKey(p,a,b) (p)->lpVtbl->GetColorKey(p,a,b)
#define IDirectDrawSurface2_GetDC(p,a) (p)->lpVtbl->GetDC(p,a)
#define IDirectDrawSurface2_GetFlipStatus(p,a) (p)->lpVtbl->GetFlipStatus(p,a)
#define IDirectDrawSurface2_GetOverlayPosition(p,a,b) (p)->lpVtbl->GetOverlayPosition(p,a,b)
#define IDirectDrawSurface2_GetPalette(p,a) (p)->lpVtbl->GetPalette(p,a)
#define IDirectDrawSurface2_GetPixelFormat(p,a) (p)->lpVtbl->GetPixelFormat(p,a)
#define IDirectDrawSurface2_GetSurfaceDesc(p,a) (p)->lpVtbl->GetSurfaceDesc(p,a)
#define IDirectDrawSurface2_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectDrawSurface2_IsLost(p) (p)->lpVtbl->IsLost(p)
#define IDirectDrawSurface2_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirectDrawSurface2_ReleaseDC(p,a) (p)->lpVtbl->ReleaseDC(p,a)
#define IDirectDrawSurface2_Restore(p) (p)->lpVtbl->Restore(p)
#define IDirectDrawSurface2_SetClipper(p,a) (p)->lpVtbl->SetClipper(p,a)
#define IDirectDrawSurface2_SetColorKey(p,a,b) (p)->lpVtbl->SetColorKey(p,a,b)
#define IDirectDrawSurface2_SetOverlayPosition(p,a,b) (p)->lpVtbl->SetOverlayPosition(p,a,b)
#define IDirectDrawSurface2_SetPalette(p,a) (p)->lpVtbl->SetPalette(p,a)
#define IDirectDrawSurface2_Unlock(p,b) (p)->lpVtbl->Unlock(p,b)
#define IDirectDrawSurface2_UpdateOverlay(p,a,b,c,d,e) (p)->lpVtbl->UpdateOverlay(p,a,b,c,d,e)
#define IDirectDrawSurface2_UpdateOverlayDisplay(p,a) (p)->lpVtbl->UpdateOverlayDisplay(p,a)
#define IDirectDrawSurface2_UpdateOverlayZOrder(p,a,b) (p)->lpVtbl->UpdateOverlayZOrder(p,a,b)
#define IDirectDrawSurface2_GetDDInterface(p,a) (p)->lpVtbl->GetDDInterface(p,a)
#define IDirectDrawSurface2_PageLock(p,a) (p)->lpVtbl->PageLock(p,a)
#define IDirectDrawSurface2_PageUnlock(p,a) (p)->lpVtbl->PageUnlock(p,a)
#undef INTERFACE
#define INTERFACE IDirectDrawSurface3
DECLARE_INTERFACE_(IDirectDrawSurface3, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE3) ;
STDMETHOD(AddOverlayDirtyRect)(THIS_ LPRECT) ;
STDMETHOD(Blt)(THIS_ LPRECT,LPDIRECTDRAWSURFACE3, LPRECT,DWORD, LPDDBLTFX) ;
STDMETHOD(BltBatch)(THIS_ LPDDBLTBATCH, DWORD, DWORD) ;
STDMETHOD(BltFast)(THIS_ DWORD,DWORD,LPDIRECTDRAWSURFACE3, LPRECT,DWORD) ;
STDMETHOD(DeleteAttachedSurface)(THIS_ DWORD,LPDIRECTDRAWSURFACE3) ;
STDMETHOD(EnumAttachedSurfaces)(THIS_ LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(EnumOverlayZOrders)(THIS_ DWORD,LPVOID,LPDDENUMSURFACESCALLBACK) ;
STDMETHOD(Flip)(THIS_ LPDIRECTDRAWSURFACE3, DWORD) ;
STDMETHOD(GetAttachedSurface)(THIS_ LPDDSCAPS, LPDIRECTDRAWSURFACE3 *) ;
STDMETHOD(GetBltStatus)(THIS_ DWORD) ;
STDMETHOD(GetCaps)(THIS_ LPDDSCAPS) ;
STDMETHOD(GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR*) ;
STDMETHOD(GetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(GetDC)(THIS_ HDC *) ;
STDMETHOD(GetFlipStatus)(THIS_ DWORD) ;
STDMETHOD(GetOverlayPosition)(THIS_ LPLONG, LPLONG) ;
STDMETHOD(GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR*) ;
STDMETHOD(GetPixelFormat)(THIS_ LPDDPIXELFORMAT) ;
STDMETHOD(GetSurfaceDesc)(THIS_ LPDDSURFACEDESC) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, LPDDSURFACEDESC) ;
STDMETHOD(IsLost)(THIS) ;
STDMETHOD(Lock)(THIS_ LPRECT,LPDDSURFACEDESC,DWORD,HANDLE) ;
STDMETHOD(ReleaseDC)(THIS_ HDC) ;
STDMETHOD(Restore)(THIS) ;
STDMETHOD(SetClipper)(THIS_ LPDIRECTDRAWCLIPPER) ;
STDMETHOD(SetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(SetOverlayPosition)(THIS_ LONG, LONG) ;
STDMETHOD(SetPalette)(THIS_ LPDIRECTDRAWPALETTE) ;
STDMETHOD(Unlock)(THIS_ LPVOID) ;
STDMETHOD(UpdateOverlay)(THIS_ LPRECT, LPDIRECTDRAWSURFACE3,LPRECT,DWORD, LPDDOVERLAYFX) ;
STDMETHOD(UpdateOverlayDisplay)(THIS_ DWORD) ;
STDMETHOD(UpdateOverlayZOrder)(THIS_ DWORD, LPDIRECTDRAWSURFACE3) ;
STDMETHOD(GetDDInterface)(THIS_ LPVOID *) ;
STDMETHOD(PageLock)(THIS_ DWORD) ;
STDMETHOD(PageUnlock)(THIS_ DWORD) ;
STDMETHOD(SetSurfaceDesc)(THIS_ LPDDSURFACEDESC, DWORD) ;
};
#define IDirectDrawSurface3_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectDrawSurface3_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawSurface3_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawSurface3_AddAttachedSurface(p,a) (p)->lpVtbl->AddAttachedSurface(p,a)
#define IDirectDrawSurface3_AddOverlayDirtyRect(p,a) (p)->lpVtbl->AddOverlayDirtyRect(p,a)
#define IDirectDrawSurface3_Blt(p,a,b,c,d,e) (p)->lpVtbl->Blt(p,a,b,c,d,e)
#define IDirectDrawSurface3_BltBatch(p,a,b,c) (p)->lpVtbl->BltBatch(p,a,b,c)
#define IDirectDrawSurface3_BltFast(p,a,b,c,d,e) (p)->lpVtbl->BltFast(p,a,b,c,d,e)
#define IDirectDrawSurface3_DeleteAttachedSurface(p,a,b) (p)->lpVtbl->DeleteAttachedSurface(p,a,b)
#define IDirectDrawSurface3_EnumAttachedSurfaces(p,a,b) (p)->lpVtbl->EnumAttachedSurfaces(p,a,b)
#define IDirectDrawSurface3_EnumOverlayZOrders(p,a,b,c) (p)->lpVtbl->EnumOverlayZOrders(p,a,b,c)
#define IDirectDrawSurface3_Flip(p,a,b) (p)->lpVtbl->Flip(p,a,b)
#define IDirectDrawSurface3_GetAttachedSurface(p,a,b) (p)->lpVtbl->GetAttachedSurface(p,a,b)
#define IDirectDrawSurface3_GetBltStatus(p,a) (p)->lpVtbl->GetBltStatus(p,a)
#define IDirectDrawSurface3_GetCaps(p,b) (p)->lpVtbl->GetCaps(p,b)
#define IDirectDrawSurface3_GetClipper(p,a) (p)->lpVtbl->GetClipper(p,a)
#define IDirectDrawSurface3_GetColorKey(p,a,b) (p)->lpVtbl->GetColorKey(p,a,b)
#define IDirectDrawSurface3_GetDC(p,a) (p)->lpVtbl->GetDC(p,a)
#define IDirectDrawSurface3_GetFlipStatus(p,a) (p)->lpVtbl->GetFlipStatus(p,a)
#define IDirectDrawSurface3_GetOverlayPosition(p,a,b) (p)->lpVtbl->GetOverlayPosition(p,a,b)
#define IDirectDrawSurface3_GetPalette(p,a) (p)->lpVtbl->GetPalette(p,a)
#define IDirectDrawSurface3_GetPixelFormat(p,a) (p)->lpVtbl->GetPixelFormat(p,a)
#define IDirectDrawSurface3_GetSurfaceDesc(p,a) (p)->lpVtbl->GetSurfaceDesc(p,a)
#define IDirectDrawSurface3_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectDrawSurface3_IsLost(p) (p)->lpVtbl->IsLost(p)
#define IDirectDrawSurface3_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirectDrawSurface3_ReleaseDC(p,a) (p)->lpVtbl->ReleaseDC(p,a)
#define IDirectDrawSurface3_Restore(p) (p)->lpVtbl->Restore(p)
#define IDirectDrawSurface3_SetClipper(p,a) (p)->lpVtbl->SetClipper(p,a)
#define IDirectDrawSurface3_SetColorKey(p,a,b) (p)->lpVtbl->SetColorKey(p,a,b)
#define IDirectDrawSurface3_SetOverlayPosition(p,a,b) (p)->lpVtbl->SetOverlayPosition(p,a,b)
#define IDirectDrawSurface3_SetPalette(p,a) (p)->lpVtbl->SetPalette(p,a)
#define IDirectDrawSurface3_Unlock(p,b) (p)->lpVtbl->Unlock(p,b)
#define IDirectDrawSurface3_UpdateOverlay(p,a,b,c,d,e) (p)->lpVtbl->UpdateOverlay(p,a,b,c,d,e)
#define IDirectDrawSurface3_UpdateOverlayDisplay(p,a) (p)->lpVtbl->UpdateOverlayDisplay(p,a)
#define IDirectDrawSurface3_UpdateOverlayZOrder(p,a,b) (p)->lpVtbl->UpdateOverlayZOrder(p,a,b)
#define IDirectDrawSurface3_GetDDInterface(p,a) (p)->lpVtbl->GetDDInterface(p,a)
#define IDirectDrawSurface3_PageLock(p,a) (p)->lpVtbl->PageLock(p,a)
#define IDirectDrawSurface3_PageUnlock(p,a) (p)->lpVtbl->PageUnlock(p,a)
#define IDirectDrawSurface3_SetSurfaceDesc(p,a,b) (p)->lpVtbl->SetSurfaceDesc(p,a,b)
#undef INTERFACE
#define INTERFACE IDirectDrawSurface4
DECLARE_INTERFACE_(IDirectDrawSurface4, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE4) ;
STDMETHOD(AddOverlayDirtyRect)(THIS_ LPRECT) ;
STDMETHOD(Blt)(THIS_ LPRECT,LPDIRECTDRAWSURFACE4, LPRECT,DWORD, LPDDBLTFX) ;
STDMETHOD(BltBatch)(THIS_ LPDDBLTBATCH, DWORD, DWORD) ;
STDMETHOD(BltFast)(THIS_ DWORD,DWORD,LPDIRECTDRAWSURFACE4, LPRECT,DWORD) ;
STDMETHOD(DeleteAttachedSurface)(THIS_ DWORD,LPDIRECTDRAWSURFACE4) ;
STDMETHOD(EnumAttachedSurfaces)(THIS_ LPVOID,LPDDENUMSURFACESCALLBACK2) ;
STDMETHOD(EnumOverlayZOrders)(THIS_ DWORD,LPVOID,LPDDENUMSURFACESCALLBACK2) ;
STDMETHOD(Flip)(THIS_ LPDIRECTDRAWSURFACE4, DWORD) ;
STDMETHOD(GetAttachedSurface)(THIS_ LPDDSCAPS2, LPDIRECTDRAWSURFACE4 *) ;
STDMETHOD(GetBltStatus)(THIS_ DWORD) ;
STDMETHOD(GetCaps)(THIS_ LPDDSCAPS2) ;
STDMETHOD(GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR*) ;
STDMETHOD(GetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(GetDC)(THIS_ HDC *) ;
STDMETHOD(GetFlipStatus)(THIS_ DWORD) ;
STDMETHOD(GetOverlayPosition)(THIS_ LPLONG, LPLONG) ;
STDMETHOD(GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR*) ;
STDMETHOD(GetPixelFormat)(THIS_ LPDDPIXELFORMAT) ;
STDMETHOD(GetSurfaceDesc)(THIS_ LPDDSURFACEDESC2) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, LPDDSURFACEDESC2) ;
STDMETHOD(IsLost)(THIS) ;
STDMETHOD(Lock)(THIS_ LPRECT,LPDDSURFACEDESC2,DWORD,HANDLE) ;
STDMETHOD(ReleaseDC)(THIS_ HDC) ;
STDMETHOD(Restore)(THIS) ;
STDMETHOD(SetClipper)(THIS_ LPDIRECTDRAWCLIPPER) ;
STDMETHOD(SetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(SetOverlayPosition)(THIS_ LONG, LONG) ;
STDMETHOD(SetPalette)(THIS_ LPDIRECTDRAWPALETTE) ;
STDMETHOD(Unlock)(THIS_ LPRECT) ;
STDMETHOD(UpdateOverlay)(THIS_ LPRECT, LPDIRECTDRAWSURFACE4,LPRECT,DWORD, LPDDOVERLAYFX) ;
STDMETHOD(UpdateOverlayDisplay)(THIS_ DWORD) ;
STDMETHOD(UpdateOverlayZOrder)(THIS_ DWORD, LPDIRECTDRAWSURFACE4) ;
STDMETHOD(GetDDInterface)(THIS_ LPVOID *) ;
STDMETHOD(PageLock)(THIS_ DWORD) ;
STDMETHOD(PageUnlock)(THIS_ DWORD) ;
STDMETHOD(SetSurfaceDesc)(THIS_ LPDDSURFACEDESC2, DWORD) ;
STDMETHOD(SetPrivateData)(THIS_ REFGUID, LPVOID, DWORD, DWORD) ;
STDMETHOD(GetPrivateData)(THIS_ REFGUID, LPVOID, LPDWORD) ;
STDMETHOD(FreePrivateData)(THIS_ REFGUID) ;
STDMETHOD(GetUniquenessValue)(THIS_ LPDWORD) ;
STDMETHOD(ChangeUniquenessValue)(THIS) ;
};
#define IDirectDrawSurface4_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectDrawSurface4_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawSurface4_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawSurface4_AddAttachedSurface(p,a) (p)->lpVtbl->AddAttachedSurface(p,a)
#define IDirectDrawSurface4_AddOverlayDirtyRect(p,a) (p)->lpVtbl->AddOverlayDirtyRect(p,a)
#define IDirectDrawSurface4_Blt(p,a,b,c,d,e) (p)->lpVtbl->Blt(p,a,b,c,d,e)
#define IDirectDrawSurface4_BltBatch(p,a,b,c) (p)->lpVtbl->BltBatch(p,a,b,c)
#define IDirectDrawSurface4_BltFast(p,a,b,c,d,e) (p)->lpVtbl->BltFast(p,a,b,c,d,e)
#define IDirectDrawSurface4_DeleteAttachedSurface(p,a,b) (p)->lpVtbl->DeleteAttachedSurface(p,a,b)
#define IDirectDrawSurface4_EnumAttachedSurfaces(p,a,b) (p)->lpVtbl->EnumAttachedSurfaces(p,a,b)
#define IDirectDrawSurface4_EnumOverlayZOrders(p,a,b,c) (p)->lpVtbl->EnumOverlayZOrders(p,a,b,c)
#define IDirectDrawSurface4_Flip(p,a,b) (p)->lpVtbl->Flip(p,a,b)
#define IDirectDrawSurface4_GetAttachedSurface(p,a,b) (p)->lpVtbl->GetAttachedSurface(p,a,b)
#define IDirectDrawSurface4_GetBltStatus(p,a) (p)->lpVtbl->GetBltStatus(p,a)
#define IDirectDrawSurface4_GetCaps(p,b) (p)->lpVtbl->GetCaps(p,b)
#define IDirectDrawSurface4_GetClipper(p,a) (p)->lpVtbl->GetClipper(p,a)
#define IDirectDrawSurface4_GetColorKey(p,a,b) (p)->lpVtbl->GetColorKey(p,a,b)
#define IDirectDrawSurface4_GetDC(p,a) (p)->lpVtbl->GetDC(p,a)
#define IDirectDrawSurface4_GetFlipStatus(p,a) (p)->lpVtbl->GetFlipStatus(p,a)
#define IDirectDrawSurface4_GetOverlayPosition(p,a,b) (p)->lpVtbl->GetOverlayPosition(p,a,b)
#define IDirectDrawSurface4_GetPalette(p,a) (p)->lpVtbl->GetPalette(p,a)
#define IDirectDrawSurface4_GetPixelFormat(p,a) (p)->lpVtbl->GetPixelFormat(p,a)
#define IDirectDrawSurface4_GetSurfaceDesc(p,a) (p)->lpVtbl->GetSurfaceDesc(p,a)
#define IDirectDrawSurface4_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectDrawSurface4_IsLost(p) (p)->lpVtbl->IsLost(p)
#define IDirectDrawSurface4_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirectDrawSurface4_ReleaseDC(p,a) (p)->lpVtbl->ReleaseDC(p,a)
#define IDirectDrawSurface4_Restore(p) (p)->lpVtbl->Restore(p)
#define IDirectDrawSurface4_SetClipper(p,a) (p)->lpVtbl->SetClipper(p,a)
#define IDirectDrawSurface4_SetColorKey(p,a,b) (p)->lpVtbl->SetColorKey(p,a,b)
#define IDirectDrawSurface4_SetOverlayPosition(p,a,b) (p)->lpVtbl->SetOverlayPosition(p,a,b)
#define IDirectDrawSurface4_SetPalette(p,a) (p)->lpVtbl->SetPalette(p,a)
#define IDirectDrawSurface4_Unlock(p,b) (p)->lpVtbl->Unlock(p,b)
#define IDirectDrawSurface4_UpdateOverlay(p,a,b,c,d,e) (p)->lpVtbl->UpdateOverlay(p,a,b,c,d,e)
#define IDirectDrawSurface4_UpdateOverlayDisplay(p,a) (p)->lpVtbl->UpdateOverlayDisplay(p,a)
#define IDirectDrawSurface4_UpdateOverlayZOrder(p,a,b) (p)->lpVtbl->UpdateOverlayZOrder(p,a,b)
#define IDirectDrawSurface4_GetDDInterface(p,a) (p)->lpVtbl->GetDDInterface(p,a)
#define IDirectDrawSurface4_PageLock(p,a) (p)->lpVtbl->PageLock(p,a)
#define IDirectDrawSurface4_PageUnlock(p,a) (p)->lpVtbl->PageUnlock(p,a)
#define IDirectDrawSurface4_SetSurfaceDesc(p,a,b) (p)->lpVtbl->SetSurfaceDesc(p,a,b)
#define IDirectDrawSurface4_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirectDrawSurface4_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirectDrawSurface4_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirectDrawSurface4_GetUniquenessValue(p, a) (p)->lpVtbl->GetUniquenessValue(p, a)
#define IDirectDrawSurface4_ChangeUniquenessValue(p) (p)->lpVtbl->ChangeUniquenessValue(p)
#undef INTERFACE
#define INTERFACE IDirectDrawSurface7
DECLARE_INTERFACE_(IDirectDrawSurface7, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(AddAttachedSurface)(THIS_ LPDIRECTDRAWSURFACE7) ;
STDMETHOD(AddOverlayDirtyRect)(THIS_ LPRECT) ;
STDMETHOD(Blt)(THIS_ LPRECT,LPDIRECTDRAWSURFACE7, LPRECT,DWORD, LPDDBLTFX) ;
STDMETHOD(BltBatch)(THIS_ LPDDBLTBATCH, DWORD, DWORD) ;
STDMETHOD(BltFast)(THIS_ DWORD,DWORD,LPDIRECTDRAWSURFACE7, LPRECT,DWORD) ;
STDMETHOD(DeleteAttachedSurface)(THIS_ DWORD,LPDIRECTDRAWSURFACE7) ;
STDMETHOD(EnumAttachedSurfaces)(THIS_ LPVOID,LPDDENUMSURFACESCALLBACK7) ;
STDMETHOD(EnumOverlayZOrders)(THIS_ DWORD,LPVOID,LPDDENUMSURFACESCALLBACK7) ;
STDMETHOD(Flip)(THIS_ LPDIRECTDRAWSURFACE7, DWORD) ;
STDMETHOD(GetAttachedSurface)(THIS_ LPDDSCAPS2, LPDIRECTDRAWSURFACE7 *) ;
STDMETHOD(GetBltStatus)(THIS_ DWORD) ;
STDMETHOD(GetCaps)(THIS_ LPDDSCAPS2) ;
STDMETHOD(GetClipper)(THIS_ LPDIRECTDRAWCLIPPER FAR*) ;
STDMETHOD(GetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(GetDC)(THIS_ HDC *) ;
STDMETHOD(GetFlipStatus)(THIS_ DWORD) ;
STDMETHOD(GetOverlayPosition)(THIS_ LPLONG, LPLONG) ;
STDMETHOD(GetPalette)(THIS_ LPDIRECTDRAWPALETTE FAR*) ;
STDMETHOD(GetPixelFormat)(THIS_ LPDDPIXELFORMAT) ;
STDMETHOD(GetSurfaceDesc)(THIS_ LPDDSURFACEDESC2) ;
STDMETHOD(Initialize)(THIS_ LPDIRECTDRAW, LPDDSURFACEDESC2) ;
STDMETHOD(IsLost)(THIS) ;
STDMETHOD(Lock)(THIS_ LPRECT,LPDDSURFACEDESC2,DWORD,HANDLE) ;
STDMETHOD(ReleaseDC)(THIS_ HDC) ;
STDMETHOD(Restore)(THIS) ;
STDMETHOD(SetClipper)(THIS_ LPDIRECTDRAWCLIPPER) ;
STDMETHOD(SetColorKey)(THIS_ DWORD, LPDDCOLORKEY) ;
STDMETHOD(SetOverlayPosition)(THIS_ LONG, LONG) ;
STDMETHOD(SetPalette)(THIS_ LPDIRECTDRAWPALETTE) ;
STDMETHOD(Unlock)(THIS_ LPRECT) ;
STDMETHOD(UpdateOverlay)(THIS_ LPRECT, LPDIRECTDRAWSURFACE7,LPRECT,DWORD, LPDDOVERLAYFX) ;
STDMETHOD(UpdateOverlayDisplay)(THIS_ DWORD) ;
STDMETHOD(UpdateOverlayZOrder)(THIS_ DWORD, LPDIRECTDRAWSURFACE7) ;
STDMETHOD(GetDDInterface)(THIS_ LPVOID *) ;
STDMETHOD(PageLock)(THIS_ DWORD) ;
STDMETHOD(PageUnlock)(THIS_ DWORD) ;
STDMETHOD(SetSurfaceDesc)(THIS_ LPDDSURFACEDESC2, DWORD) ;
STDMETHOD(SetPrivateData)(THIS_ REFGUID, LPVOID, DWORD, DWORD) ;
STDMETHOD(GetPrivateData)(THIS_ REFGUID, LPVOID, LPDWORD) ;
STDMETHOD(FreePrivateData)(THIS_ REFGUID) ;
STDMETHOD(GetUniquenessValue)(THIS_ LPDWORD) ;
STDMETHOD(ChangeUniquenessValue)(THIS) ;
STDMETHOD(SetPriority)(THIS_ DWORD) ;
STDMETHOD(GetPriority)(THIS_ LPDWORD) ;
STDMETHOD(SetLOD)(THIS_ DWORD) ;
STDMETHOD(GetLOD)(THIS_ LPDWORD) ;
};
#define IDirectDrawSurface7_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirectDrawSurface7_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawSurface7_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawSurface7_AddAttachedSurface(p,a) (p)->lpVtbl->AddAttachedSurface(p,a)
#define IDirectDrawSurface7_AddOverlayDirtyRect(p,a) (p)->lpVtbl->AddOverlayDirtyRect(p,a)
#define IDirectDrawSurface7_Blt(p,a,b,c,d,e) (p)->lpVtbl->Blt(p,a,b,c,d,e)
#define IDirectDrawSurface7_BltBatch(p,a,b,c) (p)->lpVtbl->BltBatch(p,a,b,c)
#define IDirectDrawSurface7_BltFast(p,a,b,c,d,e) (p)->lpVtbl->BltFast(p,a,b,c,d,e)
#define IDirectDrawSurface7_DeleteAttachedSurface(p,a,b) (p)->lpVtbl->DeleteAttachedSurface(p,a,b)
#define IDirectDrawSurface7_EnumAttachedSurfaces(p,a,b) (p)->lpVtbl->EnumAttachedSurfaces(p,a,b)
#define IDirectDrawSurface7_EnumOverlayZOrders(p,a,b,c) (p)->lpVtbl->EnumOverlayZOrders(p,a,b,c)
#define IDirectDrawSurface7_Flip(p,a,b) (p)->lpVtbl->Flip(p,a,b)
#define IDirectDrawSurface7_GetAttachedSurface(p,a,b) (p)->lpVtbl->GetAttachedSurface(p,a,b)
#define IDirectDrawSurface7_GetBltStatus(p,a) (p)->lpVtbl->GetBltStatus(p,a)
#define IDirectDrawSurface7_GetCaps(p,b) (p)->lpVtbl->GetCaps(p,b)
#define IDirectDrawSurface7_GetClipper(p,a) (p)->lpVtbl->GetClipper(p,a)
#define IDirectDrawSurface7_GetColorKey(p,a,b) (p)->lpVtbl->GetColorKey(p,a,b)
#define IDirectDrawSurface7_GetDC(p,a) (p)->lpVtbl->GetDC(p,a)
#define IDirectDrawSurface7_GetFlipStatus(p,a) (p)->lpVtbl->GetFlipStatus(p,a)
#define IDirectDrawSurface7_GetOverlayPosition(p,a,b) (p)->lpVtbl->GetOverlayPosition(p,a,b)
#define IDirectDrawSurface7_GetPalette(p,a) (p)->lpVtbl->GetPalette(p,a)
#define IDirectDrawSurface7_GetPixelFormat(p,a) (p)->lpVtbl->GetPixelFormat(p,a)
#define IDirectDrawSurface7_GetSurfaceDesc(p,a) (p)->lpVtbl->GetSurfaceDesc(p,a)
#define IDirectDrawSurface7_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectDrawSurface7_IsLost(p) (p)->lpVtbl->IsLost(p)
#define IDirectDrawSurface7_Lock(p,a,b,c,d) (p)->lpVtbl->Lock(p,a,b,c,d)
#define IDirectDrawSurface7_ReleaseDC(p,a) (p)->lpVtbl->ReleaseDC(p,a)
#define IDirectDrawSurface7_Restore(p) (p)->lpVtbl->Restore(p)
#define IDirectDrawSurface7_SetClipper(p,a) (p)->lpVtbl->SetClipper(p,a)
#define IDirectDrawSurface7_SetColorKey(p,a,b) (p)->lpVtbl->SetColorKey(p,a,b)
#define IDirectDrawSurface7_SetOverlayPosition(p,a,b) (p)->lpVtbl->SetOverlayPosition(p,a,b)
#define IDirectDrawSurface7_SetPalette(p,a) (p)->lpVtbl->SetPalette(p,a)
#define IDirectDrawSurface7_Unlock(p,b) (p)->lpVtbl->Unlock(p,b)
#define IDirectDrawSurface7_UpdateOverlay(p,a,b,c,d,e) (p)->lpVtbl->UpdateOverlay(p,a,b,c,d,e)
#define IDirectDrawSurface7_UpdateOverlayDisplay(p,a) (p)->lpVtbl->UpdateOverlayDisplay(p,a)
#define IDirectDrawSurface7_UpdateOverlayZOrder(p,a,b) (p)->lpVtbl->UpdateOverlayZOrder(p,a,b)
#define IDirectDrawSurface7_GetDDInterface(p,a) (p)->lpVtbl->GetDDInterface(p,a)
#define IDirectDrawSurface7_PageLock(p,a) (p)->lpVtbl->PageLock(p,a)
#define IDirectDrawSurface7_PageUnlock(p,a) (p)->lpVtbl->PageUnlock(p,a)
#define IDirectDrawSurface7_SetSurfaceDesc(p,a,b) (p)->lpVtbl->SetSurfaceDesc(p,a,b)
#define IDirectDrawSurface7_SetPrivateData(p,a,b,c,d) (p)->lpVtbl->SetPrivateData(p,a,b,c,d)
#define IDirectDrawSurface7_GetPrivateData(p,a,b,c) (p)->lpVtbl->GetPrivateData(p,a,b,c)
#define IDirectDrawSurface7_FreePrivateData(p,a) (p)->lpVtbl->FreePrivateData(p,a)
#define IDirectDrawSurface7_GetUniquenessValue(p, a) (p)->lpVtbl->GetUniquenessValue(p, a)
#define IDirectDrawSurface7_ChangeUniquenessValue(p) (p)->lpVtbl->ChangeUniquenessValue(p)
#define IDirectDrawSurface7_SetPriority(p,a) (p)->lpVtbl->SetPriority(p,a)
#define IDirectDrawSurface7_GetPriority(p,a) (p)->lpVtbl->GetPriority(p,a)
#define IDirectDrawSurface7_SetLOD(p,a) (p)->lpVtbl->SetLOD(p,a)
#define IDirectDrawSurface7_GetLOD(p,a) (p)->lpVtbl->GetLOD(p,a)
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDrawColorControl
DECLARE_INTERFACE_(IDirectDrawColorControl, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetColorControls)(THIS_ LPDDCOLORCONTROL) ;
STDMETHOD(SetColorControls)(THIS_ LPDDCOLORCONTROL) ;
};
#define IDirectDrawColorControl_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDrawColorControl_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawColorControl_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawColorControl_GetColorControls(p, a) (p)->lpVtbl->GetColorControls(p, a)
#define IDirectDrawColorControl_SetColorControls(p, a) (p)->lpVtbl->SetColorControls(p, a)
#endif
#if defined(_WIN32) && !defined(_NO_COM)
#undef INTERFACE
#define INTERFACE IDirectDrawGammaControl
DECLARE_INTERFACE_(IDirectDrawGammaControl, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetGammaRamp)(THIS_ DWORD, LPDDGAMMARAMP) ;
STDMETHOD(SetGammaRamp)(THIS_ DWORD, LPDDGAMMARAMP) ;
};
#define IDirectDrawGammaControl_QueryInterface(p, a, b) (p)->lpVtbl->QueryInterface(p, a, b)
#define IDirectDrawGammaControl_AddRef(p) (p)->lpVtbl->AddRef(p)
#define IDirectDrawGammaControl_Release(p) (p)->lpVtbl->Release(p)
#define IDirectDrawGammaControl_GetGammaRamp(p, a, b) (p)->lpVtbl->GetGammaRamp(p, a, b)
#define IDirectDrawGammaControl_SetGammaRamp(p, a, b) (p)->lpVtbl->SetGammaRamp(p, a, b)
#endif
#endif
typedef struct _DDSURFACEDESC
{
DWORD dwSize; 
DWORD dwFlags; 
DWORD dwHeight; 
DWORD dwWidth; 
union
{
LONG lPitch; 
DWORD dwLinearSize; 
} DUMMYUNIONNAMEN(1);
DWORD dwBackBufferCount; 
union
{
DWORD dwMipMapCount; 
DWORD dwZBufferBitDepth; 
DWORD dwRefreshRate; 
} DUMMYUNIONNAMEN(2);
DWORD dwAlphaBitDepth; 
DWORD dwReserved; 
LPVOID lpSurface; 
DDCOLORKEY ddckCKDestOverlay; 
DDCOLORKEY ddckCKDestBlt; 
DDCOLORKEY ddckCKSrcOverlay; 
DDCOLORKEY ddckCKSrcBlt; 
DDPIXELFORMAT ddpfPixelFormat; 
DDSCAPS ddsCaps; 
} DDSURFACEDESC;
typedef struct _DDSURFACEDESC2
{
DWORD dwSize; 
DWORD dwFlags; 
DWORD dwHeight; 
DWORD dwWidth; 
union
{
LONG lPitch; 
DWORD dwLinearSize; 
} DUMMYUNIONNAMEN(1);
DWORD dwBackBufferCount; 
union
{
DWORD dwMipMapCount; 
DWORD dwRefreshRate; 
DWORD dwSrcVBHandle; 
} DUMMYUNIONNAMEN(2);
DWORD dwAlphaBitDepth; 
DWORD dwReserved; 
LPVOID lpSurface; 
union
{
DDCOLORKEY ddckCKDestOverlay; 
DWORD dwEmptyFaceColor; 
} DUMMYUNIONNAMEN(3);
DDCOLORKEY ddckCKDestBlt; 
DDCOLORKEY ddckCKSrcOverlay; 
DDCOLORKEY ddckCKSrcBlt; 
union
{
DDPIXELFORMAT ddpfPixelFormat; 
DWORD dwFVF; 
} DUMMYUNIONNAMEN(4);
DDSCAPS2 ddsCaps; 
DWORD dwTextureStage; 
} DDSURFACEDESC2;
#define DDSD_CAPS 1
#define DDSD_HEIGHT 2
#define DDSD_WIDTH 4
#define DDSD_PITCH 8
#define DDSD_BACKBUFFERCOUNT 32
#define DDSD_ZBUFFERBITDEPTH 64
#define DDSD_ALPHABITDEPTH 128
#define DDSD_LPSURFACE 2048
#define DDSD_PIXELFORMAT 4096
#define DDSD_CKDESTOVERLAY 0x2000
#define DDSD_CKDESTBLT 0x4000
#define DDSD_CKSRCOVERLAY 0x8000
#define DDSD_CKSRCBLT 0x10000
#define DDSD_MIPMAPCOUNT 0x20000
#define DDSD_REFRESHRATE 0x40000
#define DDSD_LINEARSIZE 0x80000
#define DDSD_TEXTURESTAGE 0x100000
#define DDSD_FVF 0x200000
#define DDSD_SRCVBHANDLE 0x400000
#define DDSD_ALL 0x7ff9ee
typedef struct _DDOPTSURFACEDESC
{
DWORD dwSize; 
DWORD dwFlags; 
DDSCAPS2 ddSCaps; 
DDOSCAPS ddOSCaps; 
GUID guid; 
DWORD dwCompressionRatio; 
} DDOPTSURFACEDESC;
#define DDOSD_GUID 1
#define DDOSD_COMPRESSION_RATIO 2
#define DDOSD_SCAPS 4
#define DDOSD_OSCAPS 8
#define DDOSD_ALL 15
#define DDOSDCAPS_OPTCOMPRESSED 1
#define DDOSDCAPS_OPTREORDERED 2
#define DDOSDCAPS_MONOLITHICMIPMAP 4
#define DDOSDCAPS_VALIDSCAPS 0x30004800
#define DDOSDCAPS_VALIDOSCAPS 7
typedef struct _DDCOLORCONTROL
{
DWORD dwSize;
DWORD dwFlags;
LONG lBrightness;
LONG lContrast;
LONG lHue;
LONG lSaturation;
LONG lSharpness;
LONG lGamma;
LONG lColorEnable;
DWORD dwReserved1;
} DDCOLORCONTROL;
#define DDCOLOR_BRIGHTNESS 1
#define DDCOLOR_CONTRAST 2
#define DDCOLOR_HUE 4
#define DDCOLOR_SATURATION 8
#define DDCOLOR_SHARPNESS 16
#define DDCOLOR_GAMMA 32
#define DDCOLOR_COLORENABLE 64
#define DDSCAPS_RESERVED1 1
#define DDSCAPS_ALPHA 2
#define DDSCAPS_BACKBUFFER 4
#define DDSCAPS_COMPLEX 8
#define DDSCAPS_FLIP 16
#define DDSCAPS_FRONTBUFFER 32
#define DDSCAPS_OFFSCREENPLAIN 64
#define DDSCAPS_OVERLAY 128
#define DDSCAPS_PALETTE 256
#define DDSCAPS_PRIMARYSURFACE 512
#define DDSCAPS_RESERVED3 1024
#define DDSCAPS_SYSTEMMEMORY 2048
#define DDSCAPS_TEXTURE 4096
#define DDSCAPS_3DDEVICE 0x2000
#define DDSCAPS_VIDEOMEMORY 0x4000
#define DDSCAPS_VISIBLE 0x8000
#define DDSCAPS_WRITEONLY 0x10000
#define DDSCAPS_ZBUFFER 0x20000
#define DDSCAPS_OWNDC 0x40000
#define DDSCAPS_LIVEVIDEO 0x80000
#define DDSCAPS_HWCODEC 0x100000
#define DDSCAPS_MODEX 0x200000
#define DDSCAPS_MIPMAP 0x400000
#define DDSCAPS_RESERVED2 0x800000
#define DDSCAPS_ALLOCONLOAD 0x4000000
#define DDSCAPS_VIDEOPORT 0x8000000
#define DDSCAPS_LOCALVIDMEM 0x10000000
#define DDSCAPS_NONLOCALVIDMEM 0x20000000
#define DDSCAPS_STANDARDVGAMODE 0x40000000
#define DDSCAPS_OPTIMIZED 0x80000000
#define DDSCAPS2_HARDWAREDEINTERLACE 2
#define DDSCAPS2_HINTDYNAMIC 4
#define DDSCAPS2_HINTSTATIC 8
#define DDSCAPS2_TEXTUREMANAGE 16
#define DDSCAPS2_RESERVED1 32
#define DDSCAPS2_RESERVED2 64
#define DDSCAPS2_OPAQUE 128
#define DDSCAPS2_HINTANTIALIASING 256
#define DDSCAPS2_CUBEMAP 512
#define DDSCAPS2_CUBEMAP_POSITIVEX 1024
#define DDSCAPS2_CUBEMAP_NEGATIVEX 2048
#define DDSCAPS2_CUBEMAP_POSITIVEY 4096
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0x2000
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0x4000
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0x8000
#define DDSCAPS2_CUBEMAP_ALLFACES (DDSCAPS2_CUBEMAP_POSITIVEX | DDSCAPS2_CUBEMAP_NEGATIVEX | DDSCAPS2_CUBEMAP_POSITIVEY | DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ | DDSCAPS2_CUBEMAP_NEGATIVEZ)
#define DDSCAPS2_MIPMAPSUBLEVEL 0x10000
#define DDSCAPS2_D3DTEXTUREMANAGE 0x20000
#define DDSCAPS2_DONOTPERSIST 0x40000
#define DDSCAPS2_STEREOSURFACELEFT 0x80000
#define DDCAPS_3D 1
#define DDCAPS_ALIGNBOUNDARYDEST 2
#define DDCAPS_ALIGNSIZEDEST 4
#define DDCAPS_ALIGNBOUNDARYSRC 8
#define DDCAPS_ALIGNSIZESRC 16
#define DDCAPS_ALIGNSTRIDE 32
#define DDCAPS_BLT 64
#define DDCAPS_BLTQUEUE 128
#define DDCAPS_BLTFOURCC 256
#define DDCAPS_BLTSTRETCH 512
#define DDCAPS_GDI 1024
#define DDCAPS_OVERLAY 2048
#define DDCAPS_OVERLAYCANTCLIP 4096
#define DDCAPS_OVERLAYFOURCC 0x2000
#define DDCAPS_OVERLAYSTRETCH 0x4000
#define DDCAPS_PALETTE 0x8000
#define DDCAPS_PALETTEVSYNC 0x10000
#define DDCAPS_READSCANLINE 0x20000
#define DDCAPS_RESERVED1 0x40000
#define DDCAPS_VBI 0x80000
#define DDCAPS_ZBLTS 0x100000
#define DDCAPS_ZOVERLAYS 0x200000
#define DDCAPS_COLORKEY 0x400000
#define DDCAPS_ALPHA 0x800000
#define DDCAPS_COLORKEYHWASSIST 0x1000000
#define DDCAPS_NOHARDWARE 0x2000000
#define DDCAPS_BLTCOLORFILL 0x4000000
#define DDCAPS_BANKSWITCHED 0x8000000
#define DDCAPS_BLTDEPTHFILL 0x10000000
#define DDCAPS_CANCLIP 0x20000000
#define DDCAPS_CANCLIPSTRETCHED 0x40000000
#define DDCAPS_CANBLTSYSMEM 0x80000000
#define DDCAPS2_CERTIFIED 1
#define DDCAPS2_NO2DDURING3DSCENE 2
#define DDCAPS2_VIDEOPORT 4
#define DDCAPS2_AUTOFLIPOVERLAY 8
#define DDCAPS2_CANBOBINTERLEAVED 16
#define DDCAPS2_CANBOBNONINTERLEAVED 32
#define DDCAPS2_COLORCONTROLOVERLAY 64
#define DDCAPS2_COLORCONTROLPRIMARY 128
#define DDCAPS2_CANDROPZ16BIT 256
#define DDCAPS2_NONLOCALVIDMEM 512
#define DDCAPS2_NONLOCALVIDMEMCAPS 1024
#define DDCAPS2_NOPAGELOCKREQUIRED 2048
#define DDCAPS2_WIDESURFACES 4096
#define DDCAPS2_CANFLIPODDEVEN 0x2000
#define DDCAPS2_CANBOBHARDWARE 0x4000
#define DDCAPS2_COPYFOURCC 0x8000
#define DDCAPS2_PRIMARYGAMMA 0x20000
#define DDCAPS2_CANRENDERWINDOWED 0x80000
#define DDCAPS2_CANCALIBRATEGAMMA 0x100000
#define DDCAPS2_FLIPINTERVAL 0x200000
#define DDCAPS2_FLIPNOVSYNC 0x400000
#define DDCAPS2_CANMANAGETEXTURE 0x800000
#define DDCAPS2_TEXMANINNONLOCALVIDMEM 0x1000000
#define DDCAPS2_STEREO 0x2000000
#define DDCAPS2_SYSTONONLOCAL_AS_SYSTOLOCAL 0x4000000
#define DDFXALPHACAPS_BLTALPHAEDGEBLEND 1
#define DDFXALPHACAPS_BLTALPHAPIXELS 2
#define DDFXALPHACAPS_BLTALPHAPIXELSNEG 4
#define DDFXALPHACAPS_BLTALPHASURFACES 8
#define DDFXALPHACAPS_BLTALPHASURFACESNEG 16
#define DDFXALPHACAPS_OVERLAYALPHAEDGEBLEND 32
#define DDFXALPHACAPS_OVERLAYALPHAPIXELS 64
#define DDFXALPHACAPS_OVERLAYALPHAPIXELSNEG 128
#define DDFXALPHACAPS_OVERLAYALPHASURFACES 256
#define DDFXALPHACAPS_OVERLAYALPHASURFACESNEG 512
#if DIRECTDRAW_VERSION < 1536
#endif 
#define DDFXCAPS_BLTARITHSTRETCHY 32
#define DDFXCAPS_BLTARITHSTRETCHYN 16
#define DDFXCAPS_BLTMIRRORLEFTRIGHT 64
#define DDFXCAPS_BLTMIRRORUPDOWN 128
#define DDFXCAPS_BLTROTATION 256
#define DDFXCAPS_BLTROTATION90 512
#define DDFXCAPS_BLTSHRINKX 1024
#define DDFXCAPS_BLTSHRINKXN 2048
#define DDFXCAPS_BLTSHRINKY 4096
#define DDFXCAPS_BLTSHRINKYN 0x2000
#define DDFXCAPS_BLTSTRETCHX 0x4000
#define DDFXCAPS_BLTSTRETCHXN 0x8000
#define DDFXCAPS_BLTSTRETCHY 0x10000
#define DDFXCAPS_BLTSTRETCHYN 0x20000
#define DDFXCAPS_OVERLAYARITHSTRETCHY 0x40000
#define DDFXCAPS_OVERLAYARITHSTRETCHYN 8
#define DDFXCAPS_OVERLAYSHRINKX 0x80000
#define DDFXCAPS_OVERLAYSHRINKXN 0x100000
#define DDFXCAPS_OVERLAYSHRINKY 0x200000
#define DDFXCAPS_OVERLAYSHRINKYN 0x400000
#define DDFXCAPS_OVERLAYSTRETCHX 0x800000
#define DDFXCAPS_OVERLAYSTRETCHXN 0x1000000
#define DDFXCAPS_OVERLAYSTRETCHY 0x2000000
#define DDFXCAPS_OVERLAYSTRETCHYN 0x4000000
#define DDFXCAPS_OVERLAYMIRRORLEFTRIGHT 0x8000000
#define DDFXCAPS_OVERLAYMIRRORUPDOWN 0x10000000
#define DDFXCAPS_BLTALPHA 1
#define DDFXCAPS_BLTFILTER DDFXCAPS_BLTARITHSTRETCHY
#define DDFXCAPS_OVERLAYALPHA 4
#define DDFXCAPS_OVERLAYFILTER DDFXCAPS_OVERLAYARITHSTRETCHY
#define DDSVCAPS_RESERVED1 1
#define DDSVCAPS_RESERVED2 2
#define DDSVCAPS_RESERVED3 4
#define DDSVCAPS_RESERVED4 8
#define DDSVCAPS_STEREOSEQUENTIAL 16
#define DDPCAPS_4BIT 1
#define DDPCAPS_8BITENTRIES 2
#define DDPCAPS_8BIT 4
#define DDPCAPS_INITIALIZE 0
#define DDPCAPS_PRIMARYSURFACE 16
#define DDPCAPS_PRIMARYSURFACELEFT 32
#define DDPCAPS_ALLOW256 64
#define DDPCAPS_VSYNC 128
#define DDPCAPS_1BIT 256
#define DDPCAPS_2BIT 512
#define DDPCAPS_ALPHA 1024
#define DDSPD_IUNKNOWNPOINTER 1
#define DDSPD_VOLATILE 2
#define DDBD_1 0x4000
#define DDBD_2 0x2000
#define DDBD_4 4096
#define DDBD_8 2048
#define DDBD_16 1024
#define DDBD_24 0X00000200l
#define DDBD_32 256
#define DDCKEY_COLORSPACE 1
#define DDCKEY_DESTBLT 2
#define DDCKEY_DESTOVERLAY 4
#define DDCKEY_SRCBLT 8
#define DDCKEY_SRCOVERLAY 16
#define DDCKEYCAPS_DESTBLT 1
#define DDCKEYCAPS_DESTBLTCLRSPACE 2
#define DDCKEYCAPS_DESTBLTCLRSPACEYUV 4
#define DDCKEYCAPS_DESTBLTYUV 8
#define DDCKEYCAPS_DESTOVERLAY 16
#define DDCKEYCAPS_DESTOVERLAYCLRSPACE 32
#define DDCKEYCAPS_DESTOVERLAYCLRSPACEYUV 64
#define DDCKEYCAPS_DESTOVERLAYONEACTIVE 128
#define DDCKEYCAPS_DESTOVERLAYYUV 256
#define DDCKEYCAPS_SRCBLT 512
#define DDCKEYCAPS_SRCBLTCLRSPACE 1024
#define DDCKEYCAPS_SRCBLTCLRSPACEYUV 2048
#define DDCKEYCAPS_SRCBLTYUV 4096
#define DDCKEYCAPS_SRCOVERLAY 0x2000
#define DDCKEYCAPS_SRCOVERLAYCLRSPACE 0x4000
#define DDCKEYCAPS_SRCOVERLAYCLRSPACEYUV 0x8000
#define DDCKEYCAPS_SRCOVERLAYONEACTIVE 0x10000
#define DDCKEYCAPS_SRCOVERLAYYUV 0x20000
#define DDCKEYCAPS_NOCOSTOVERLAY 0x40000
#define DDPF_ALPHAPIXELS 1
#define DDPF_ALPHA 2
#define DDPF_FOURCC 4
#define DDPF_PALETTEINDEXED4 8
#define DDPF_PALETTEINDEXEDTO8 16
#define DDPF_PALETTEINDEXED8 32
#define DDPF_RGB 64
#define DDPF_COMPRESSED 128
#define DDPF_RGBTOYUV 256
#define DDPF_YUV 512
#define DDPF_ZBUFFER 1024
#define DDPF_PALETTEINDEXED1 2048
#define DDPF_PALETTEINDEXED2 4096
#define DDPF_ZPIXELS 0x2000
#define DDPF_STENCILBUFFER 0x4000
#define DDPF_ALPHAPREMULT 0x8000
#define DDPF_LUMINANCE 0x20000
#define DDPF_BUMPLUMINANCE 0x40000
#define DDPF_BUMPDUDV 0x80000
#define DDENUMSURFACES_ALL 1
#define DDENUMSURFACES_MATCH 2
#define DDENUMSURFACES_NOMATCH 4
#define DDENUMSURFACES_CANBECREATED 8
#define DDENUMSURFACES_DOESEXIST 16
#define DDSDM_STANDARDVGAMODE 1
#define DDEDM_REFRESHRATES 1
#define DDEDM_STANDARDVGAMODES 2
#define DDSCL_FULLSCREEN 1
#define DDSCL_ALLOWREBOOT 2
#define DDSCL_NOWINDOWCHANGES 4
#define DDSCL_NORMAL 8
#define DDSCL_EXCLUSIVE 16
#define DDSCL_ALLOWMODEX 64
#define DDSCL_SETFOCUSWINDOW 128
#define DDSCL_SETDEVICEWINDOW 256
#define DDSCL_CREATEDEVICEWINDOW 512
#define DDSCL_MULTITHREADED 1024
#define DDSCL_FPUSETUP 2048
#define DDSCL_FPUPRESERVE 4096
#define DDBLT_ALPHADEST 1
#define DDBLT_ALPHADESTCONSTOVERRIDE 2
#define DDBLT_ALPHADESTNEG 4
#define DDBLT_ALPHADESTSURFACEOVERRIDE 8
#define DDBLT_ALPHAEDGEBLEND 16
#define DDBLT_ALPHASRC 32
#define DDBLT_ALPHASRCCONSTOVERRIDE 64
#define DDBLT_ALPHASRCNEG 128
#define DDBLT_ALPHASRCSURFACEOVERRIDE 256
#define DDBLT_ASYNC 512
#define DDBLT_COLORFILL 1024
#define DDBLT_DDFX 2048
#define DDBLT_DDROPS 4096
#define DDBLT_KEYDEST 0x2000
#define DDBLT_KEYDESTOVERRIDE 0x4000
#define DDBLT_KEYSRC 0x8000
#define DDBLT_KEYSRCOVERRIDE 0x10000
#define DDBLT_ROP 0x20000
#define DDBLT_ROTATIONANGLE 0x40000
#define DDBLT_ZBUFFER 0x80000
#define DDBLT_ZBUFFERDESTCONSTOVERRIDE 0x100000
#define DDBLT_ZBUFFERDESTOVERRIDE 0x200000
#define DDBLT_ZBUFFERSRCCONSTOVERRIDE 0x400000
#define DDBLT_ZBUFFERSRCOVERRIDE 0x800000
#define DDBLT_WAIT 0x1000000
#define DDBLT_DEPTHFILL 0x2000000
#define DDBLT_DONOTWAIT 0x8000000
#define DDBLTFAST_NOCOLORKEY 0
#define DDBLTFAST_SRCCOLORKEY 1
#define DDBLTFAST_DESTCOLORKEY 2
#define DDBLTFAST_WAIT 16
#define DDBLTFAST_DONOTWAIT 32
#define DDFLIP_WAIT 1
#define DDFLIP_EVEN 2
#define DDFLIP_ODD 4
#define DDFLIP_NOVSYNC 8
#define DDFLIP_INTERVAL2 0x2000000
#define DDFLIP_INTERVAL3 0x3000000
#define DDFLIP_INTERVAL4 0x4000000
#define DDFLIP_STEREO 16
#define DDFLIP_DONOTWAIT 32
#define DDOVER_ALPHADEST 1
#define DDOVER_ALPHADESTCONSTOVERRIDE 2
#define DDOVER_ALPHADESTNEG 4
#define DDOVER_ALPHADESTSURFACEOVERRIDE 8
#define DDOVER_ALPHAEDGEBLEND 16
#define DDOVER_ALPHASRC 32
#define DDOVER_ALPHASRCCONSTOVERRIDE 64
#define DDOVER_ALPHASRCNEG 128
#define DDOVER_ALPHASRCSURFACEOVERRIDE 256
#define DDOVER_HIDE 512
#define DDOVER_KEYDEST 1024
#define DDOVER_KEYDESTOVERRIDE 2048
#define DDOVER_KEYSRC 4096
#define DDOVER_KEYSRCOVERRIDE 0x2000
#define DDOVER_SHOW 0x4000
#define DDOVER_ADDDIRTYRECT 0x8000
#define DDOVER_REFRESHDIRTYRECTS 0x10000
#define DDOVER_REFRESHALL 0x20000
#define DDOVER_DDFX 0x80000
#define DDOVER_AUTOFLIP 0x100000
#define DDOVER_BOB 0x200000
#define DDOVER_OVERRIDEBOBWEAVE 0x400000
#define DDOVER_INTERLEAVED 0x800000
#define DDOVER_BOBHARDWARE 0x1000000
#define DDOVER_ARGBSCALEFACTORS 0x2000000
#define DDOVER_DEGRADEARGBSCALING 0x4000000
#define DDLOCK_SURFACEMEMORYPTR 0
#define DDLOCK_WAIT 1
#define DDLOCK_EVENT 2
#define DDLOCK_READONLY 16
#define DDLOCK_WRITEONLY 32
#define DDLOCK_NOSYSLOCK 2048
#define DDLOCK_NOOVERWRITE 4096
#define DDLOCK_DISCARDCONTENTS 0x2000
#define DDLOCK_OKTOSWAP 0x2000
#define DDLOCK_DONOTWAIT 0x4000
#define DDBLTFX_ARITHSTRETCHY 1
#define DDBLTFX_MIRRORLEFTRIGHT 2
#define DDBLTFX_MIRRORUPDOWN 4
#define DDBLTFX_NOTEARING 8
#define DDBLTFX_ROTATE180 16
#define DDBLTFX_ROTATE270 32
#define DDBLTFX_ROTATE90 64
#define DDBLTFX_ZBUFFERRANGE 128
#define DDBLTFX_ZBUFFERBASEDEST 256
#define DDOVERFX_ARITHSTRETCHY 1
#define DDOVERFX_MIRRORLEFTRIGHT 2
#define DDOVERFX_MIRRORUPDOWN 4
#define DDWAITVB_BLOCKBEGIN 1
#define DDWAITVB_BLOCKBEGINEVENT 2
#define DDWAITVB_BLOCKEND 4
#define DDGFS_CANFLIP 1
#define DDGFS_ISFLIPDONE 2
#define DDGBS_CANBLT 1
#define DDGBS_ISBLTDONE 2
#define DDENUMOVERLAYZ_BACKTOFRONT 0
#define DDENUMOVERLAYZ_FRONTTOBACK 1
#define DDOVERZ_SENDTOFRONT 0
#define DDOVERZ_SENDTOBACK 1
#define DDOVERZ_MOVEFORWARD 2
#define DDOVERZ_MOVEBACKWARD 3
#define DDOVERZ_INSERTINFRONTOF 4
#define DDOVERZ_INSERTINBACKOF 5
#define DDSGR_CALIBRATE 1
#define DDSMT_ISTESTREQUIRED 1
#define DDEM_MODEPASSED 1
#define DDEM_MODEFAILED 2
#define DD_OK 0
#define DD_FALSE S_FALSE
#define DDENUMRET_CANCEL 0
#define DDENUMRET_OK 1
#define DDERR_ALREADYINITIALIZED MAKE_DDHRESULT(5)
#define DDERR_CANNOTATTACHSURFACE MAKE_DDHRESULT(10)
#define DDERR_CANNOTDETACHSURFACE MAKE_DDHRESULT(20)
#define DDERR_CURRENTLYNOTAVAIL MAKE_DDHRESULT(40)
#define DDERR_EXCEPTION MAKE_DDHRESULT(55)
#define DDERR_GENERIC E_FAIL
#define DDERR_HEIGHTALIGN MAKE_DDHRESULT(90)
#define DDERR_INCOMPATIBLEPRIMARY MAKE_DDHRESULT(95)
#define DDERR_INVALIDCAPS MAKE_DDHRESULT(100)
#define DDERR_INVALIDCLIPLIST MAKE_DDHRESULT(110)
#define DDERR_INVALIDMODE MAKE_DDHRESULT(120)
#define DDERR_INVALIDOBJECT MAKE_DDHRESULT(130)
#define DDERR_INVALIDPARAMS E_INVALIDARG
#define DDERR_INVALIDPIXELFORMAT MAKE_DDHRESULT(145)
#define DDERR_INVALIDRECT MAKE_DDHRESULT(150)
#define DDERR_LOCKEDSURFACES MAKE_DDHRESULT(160)
#define DDERR_NO3D MAKE_DDHRESULT(170)
#define DDERR_NOALPHAHW MAKE_DDHRESULT(180)
#define DDERR_NOSTEREOHARDWARE MAKE_DDHRESULT(181)
#define DDERR_NOSURFACELEFT MAKE_DDHRESULT(182)
#define DDERR_NOCLIPLIST MAKE_DDHRESULT(205)
#define DDERR_NOCOLORCONVHW MAKE_DDHRESULT(210)
#define DDERR_NOCOOPERATIVELEVELSET MAKE_DDHRESULT(212)
#define DDERR_NOCOLORKEY MAKE_DDHRESULT(215)
#define DDERR_NOCOLORKEYHW MAKE_DDHRESULT(220)
#define DDERR_NODIRECTDRAWSUPPORT MAKE_DDHRESULT(222)
#define DDERR_NOEXCLUSIVEMODE MAKE_DDHRESULT(225)
#define DDERR_NOFLIPHW MAKE_DDHRESULT(230)
#define DDERR_NOGDI MAKE_DDHRESULT(240)
#define DDERR_NOMIRRORHW MAKE_DDHRESULT(250)
#define DDERR_NOTFOUND MAKE_DDHRESULT(255)
#define DDERR_NOOVERLAYHW MAKE_DDHRESULT(260)
#define DDERR_OVERLAPPINGRECTS MAKE_DDHRESULT(270)
#define DDERR_NORASTEROPHW MAKE_DDHRESULT(280)
#define DDERR_NOROTATIONHW MAKE_DDHRESULT(290)
#define DDERR_NOSTRETCHHW MAKE_DDHRESULT(310)
#define DDERR_NOT4BITCOLOR MAKE_DDHRESULT(316)
#define DDERR_NOT4BITCOLORINDEX MAKE_DDHRESULT(317)
#define DDERR_NOT8BITCOLOR MAKE_DDHRESULT(320)
#define DDERR_NOTEXTUREHW MAKE_DDHRESULT(330)
#define DDERR_NOVSYNCHW MAKE_DDHRESULT(335)
#define DDERR_NOZBUFFERHW MAKE_DDHRESULT(340)
#define DDERR_NOZOVERLAYHW MAKE_DDHRESULT(350)
#define DDERR_OUTOFCAPS MAKE_DDHRESULT(360)
#define DDERR_OUTOFMEMORY E_OUTOFMEMORY
#define DDERR_OUTOFVIDEOMEMORY MAKE_DDHRESULT(380)
#define DDERR_OVERLAYCANTCLIP MAKE_DDHRESULT(382)
#define DDERR_OVERLAYCOLORKEYONLYONEACTIVE MAKE_DDHRESULT(384)
#define DDERR_PALETTEBUSY MAKE_DDHRESULT(387)
#define DDERR_COLORKEYNOTSET MAKE_DDHRESULT(400)
#define DDERR_SURFACEALREADYATTACHED MAKE_DDHRESULT(410)
#define DDERR_SURFACEALREADYDEPENDENT MAKE_DDHRESULT(420)
#define DDERR_SURFACEBUSY MAKE_DDHRESULT(430)
#define DDERR_CANTLOCKSURFACE MAKE_DDHRESULT(435)
#define DDERR_SURFACEISOBSCURED MAKE_DDHRESULT(440)
#define DDERR_SURFACELOST MAKE_DDHRESULT(450)
#define DDERR_SURFACENOTATTACHED MAKE_DDHRESULT(460)
#define DDERR_TOOBIGHEIGHT MAKE_DDHRESULT(470)
#define DDERR_TOOBIGSIZE MAKE_DDHRESULT(480)
#define DDERR_TOOBIGWIDTH MAKE_DDHRESULT(490)
#define DDERR_UNSUPPORTED E_NOTIMPL
#define DDERR_UNSUPPORTEDFORMAT MAKE_DDHRESULT(510)
#define DDERR_UNSUPPORTEDMASK MAKE_DDHRESULT(520)
#define DDERR_INVALIDSTREAM MAKE_DDHRESULT(521)
#define DDERR_VERTICALBLANKINPROGRESS MAKE_DDHRESULT(537)
#define DDERR_WASSTILLDRAWING MAKE_DDHRESULT(540)
#define DDERR_DDSCAPSCOMPLEXREQUIRED MAKE_DDHRESULT(542)
#define DDERR_XALIGN MAKE_DDHRESULT(560)
#define DDERR_INVALIDDIRECTDRAWGUID MAKE_DDHRESULT(561)
#define DDERR_DIRECTDRAWALREADYCREATED MAKE_DDHRESULT(562)
#define DDERR_NODIRECTDRAWHW MAKE_DDHRESULT(563)
#define DDERR_PRIMARYSURFACEALREADYEXISTS MAKE_DDHRESULT(564)
#define DDERR_NOEMULATION MAKE_DDHRESULT(565)
#define DDERR_REGIONTOOSMALL MAKE_DDHRESULT(566)
#define DDERR_CLIPPERISUSINGHWND MAKE_DDHRESULT(567)
#define DDERR_NOCLIPPERATTACHED MAKE_DDHRESULT(568)
#define DDERR_NOHWND MAKE_DDHRESULT(569)
#define DDERR_HWNDSUBCLASSED MAKE_DDHRESULT(570)
#define DDERR_HWNDALREADYSET MAKE_DDHRESULT(571)
#define DDERR_NOPALETTEATTACHED MAKE_DDHRESULT(572)
#define DDERR_NOPALETTEHW MAKE_DDHRESULT(573)
#define DDERR_BLTFASTCANTCLIP MAKE_DDHRESULT(574)
#define DDERR_NOBLTHW MAKE_DDHRESULT(575)
#define DDERR_NODDROPSHW MAKE_DDHRESULT(576)
#define DDERR_OVERLAYNOTVISIBLE MAKE_DDHRESULT(577)
#define DDERR_NOOVERLAYDEST MAKE_DDHRESULT(578)
#define DDERR_INVALIDPOSITION MAKE_DDHRESULT(579)
#define DDERR_NOTAOVERLAYSURFACE MAKE_DDHRESULT(580)
#define DDERR_EXCLUSIVEMODEALREADYSET MAKE_DDHRESULT(581)
#define DDERR_NOTFLIPPABLE MAKE_DDHRESULT(582)
#define DDERR_CANTDUPLICATE MAKE_DDHRESULT(583)
#define DDERR_NOTLOCKED MAKE_DDHRESULT(584)
#define DDERR_CANTCREATEDC MAKE_DDHRESULT(585)
#define DDERR_NODC MAKE_DDHRESULT(586)
#define DDERR_WRONGMODE MAKE_DDHRESULT(587)
#define DDERR_IMPLICITLYCREATED MAKE_DDHRESULT(588)
#define DDERR_NOTPALETTIZED MAKE_DDHRESULT(589)
#define DDERR_UNSUPPORTEDMODE MAKE_DDHRESULT(590)
#define DDERR_NOMIPMAPHW MAKE_DDHRESULT(591)
#define DDERR_INVALIDSURFACETYPE MAKE_DDHRESULT(592)
#define DDERR_NOOPTIMIZEHW MAKE_DDHRESULT(600)
#define DDERR_NOTLOADED MAKE_DDHRESULT(601)
#define DDERR_NOFOCUSWINDOW MAKE_DDHRESULT(602)
#define DDERR_NOTONMIPMAPSUBLEVEL MAKE_DDHRESULT(603)
#define DDERR_DCALREADYCREATED MAKE_DDHRESULT(620)
#define DDERR_NONONLOCALVIDMEM MAKE_DDHRESULT(630)
#define DDERR_CANTPAGELOCK MAKE_DDHRESULT(640)
#define DDERR_CANTPAGEUNLOCK MAKE_DDHRESULT(660)
#define DDERR_NOTPAGELOCKED MAKE_DDHRESULT(680)
#define DDERR_MOREDATA MAKE_DDHRESULT(690)
#define DDERR_EXPIRED MAKE_DDHRESULT(691)
#define DDERR_TESTFINISHED MAKE_DDHRESULT(692)
#define DDERR_NEWMODE MAKE_DDHRESULT(693)
#define DDERR_D3DNOTINITIALIZED MAKE_DDHRESULT(694)
#define DDERR_VIDEONOTACTIVE MAKE_DDHRESULT(695)
#define DDERR_NOMONITORINFORMATION MAKE_DDHRESULT(696)
#define DDERR_NODRIVERSUPPORT MAKE_DDHRESULT(697)
#define DDERR_DEVICEDOESNTOWNSURFACE MAKE_DDHRESULT(699)
#define DDERR_NOTINITIALIZED CO_E_NOTINITIALIZED
#endif 
