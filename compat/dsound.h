#ifndef __dsound_h__
#define __dsound_h__
#include "d3dtypes.h"
#define COM_NO_WINDOWS_H
#include <objbase.h>
#define _FACDS 2168
#define MAKE_DSHRESULT(code) MAKE_HRESULT(1, _FACDS, code)
#ifndef DIRECTSOUND_VERSION
#define DIRECTSOUND_VERSION 1792
#endif 
DEFINE_GUID(CLSID_DirectSound, 0x47d4d946, 0x62e8, 4559, 147, 188, 68, 69, 83, 84, 0, 0);
DEFINE_GUID(CLSID_DirectSoundCapture, 0xb0210780, 0x89cd, 4560, 175, 8, 0, 160, 201, 37, 205, 22);
typedef struct IDirectSound *LPDIRECTSOUND;
typedef struct IDirectSoundBuffer *LPDIRECTSOUNDBUFFER;
typedef struct IDirectSound3DListener *LPDIRECTSOUND3DLISTENER;
typedef struct IDirectSound3DBuffer *LPDIRECTSOUND3DBUFFER;
typedef struct IDirectSoundCapture *LPDIRECTSOUNDCAPTURE;
typedef struct IDirectSoundCaptureBuffer *LPDIRECTSOUNDCAPTUREBUFFER;
typedef struct IDirectSoundNotify *LPDIRECTSOUNDNOTIFY;
#ifndef _LPCWAVEFORMATEX_DEFINED
#define _LPCWAVEFORMATEX_DEFINED
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
        WORD wFormatTag;
        WORD nChannels;
        DWORD nSamplesPerSec;
        DWORD nAvgBytesPerSec;
        WORD nBlockAlign;
        WORD wBitsPerSample;
        WORD cbSize;
}       WAVEFORMATEX;
typedef WAVEFORMATEX *PWAVEFORMATEX;
typedef WAVEFORMATEX *NPWAVEFORMATEX;
typedef WAVEFORMATEX *LPWAVEFORMATEX;
#define _WAVEFORMATEX_
#endif
typedef const WAVEFORMATEX *LPCWAVEFORMATEX;
#endif 
#ifndef __LPCGUID_DEFINED__
#define __LPCGUID_DEFINED__
typedef const GUID *LPCGUID;
#endif 
typedef LPDIRECTSOUND *LPLPDIRECTSOUND;
typedef LPDIRECTSOUNDBUFFER *LPLPDIRECTSOUNDBUFFER;
typedef LPDIRECTSOUND3DLISTENER *LPLPDIRECTSOUND3DLISTENER;
typedef LPDIRECTSOUND3DBUFFER *LPLPDIRECTSOUND3DBUFFER;
typedef LPDIRECTSOUNDCAPTURE *LPLPDIRECTSOUNDCAPTURE;
typedef LPDIRECTSOUNDCAPTUREBUFFER *LPLPDIRECTSOUNDCAPTUREBUFFER;
typedef LPDIRECTSOUNDNOTIFY *LPLPDIRECTSOUNDNOTIFY;
typedef struct _DSCAPS
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwMinSecondarySampleRate;
DWORD dwMaxSecondarySampleRate;
DWORD dwPrimaryBuffers;
DWORD dwMaxHwMixingAllBuffers;
DWORD dwMaxHwMixingStaticBuffers;
DWORD dwMaxHwMixingStreamingBuffers;
DWORD dwFreeHwMixingAllBuffers;
DWORD dwFreeHwMixingStaticBuffers;
DWORD dwFreeHwMixingStreamingBuffers;
DWORD dwMaxHw3DAllBuffers;
DWORD dwMaxHw3DStaticBuffers;
DWORD dwMaxHw3DStreamingBuffers;
DWORD dwFreeHw3DAllBuffers;
DWORD dwFreeHw3DStaticBuffers;
DWORD dwFreeHw3DStreamingBuffers;
DWORD dwTotalHwMemBytes;
DWORD dwFreeHwMemBytes;
DWORD dwMaxContigFreeHwMemBytes;
DWORD dwUnlockTransferRateHwBuffers;
DWORD dwPlayCpuOverheadSwBuffers;
DWORD dwReserved1;
DWORD dwReserved2;
} DSCAPS, *LPDSCAPS;
typedef const DSCAPS *LPCDSCAPS;
typedef struct _DSBCAPS
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwBufferBytes;
DWORD dwUnlockTransferRate;
DWORD dwPlayCpuOverhead;
} DSBCAPS, *LPDSBCAPS;
typedef const DSBCAPS *LPCDSBCAPS;
typedef struct _DSBUFFERDESC
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwBufferBytes;
DWORD dwReserved;
LPWAVEFORMATEX lpwfxFormat;
#if DIRECTSOUND_VERSION >= 1792
GUID guid3DAlgorithm;
#endif
} DSBUFFERDESC, *LPDSBUFFERDESC;
typedef const DSBUFFERDESC *LPCDSBUFFERDESC;
typedef struct _DSBUFFERDESC1
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwBufferBytes;
DWORD dwReserved;
LPWAVEFORMATEX lpwfxFormat;
} DSBUFFERDESC1, *LPDSBUFFERDESC1;
typedef const DSBUFFERDESC1 *LPCDSBUFFERDESC1;
typedef struct _DS3DBUFFER
{
DWORD dwSize;
D3DVECTOR vPosition;
D3DVECTOR vVelocity;
DWORD dwInsideConeAngle;
DWORD dwOutsideConeAngle;
D3DVECTOR vConeOrientation;
LONG lConeOutsideVolume;
D3DVALUE flMinDistance;
D3DVALUE flMaxDistance;
DWORD dwMode;
} DS3DBUFFER, *LPDS3DBUFFER;
typedef const DS3DBUFFER *LPCDS3DBUFFER;
typedef struct _DS3DLISTENER
{
DWORD dwSize;
D3DVECTOR vPosition;
D3DVECTOR vVelocity;
D3DVECTOR vOrientFront;
D3DVECTOR vOrientTop;
D3DVALUE flDistanceFactor;
D3DVALUE flRolloffFactor;
D3DVALUE flDopplerFactor;
} DS3DLISTENER, *LPDS3DLISTENER;
typedef const DS3DLISTENER *LPCDS3DLISTENER;
typedef struct _DSCCAPS
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwFormats;
DWORD dwChannels;
} DSCCAPS, *LPDSCCAPS;
typedef const DSCCAPS *LPCDSCCAPS;
typedef struct _DSCBUFFERDESC
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwBufferBytes;
DWORD dwReserved;
LPWAVEFORMATEX lpwfxFormat;
} DSCBUFFERDESC, *LPDSCBUFFERDESC;
typedef const DSCBUFFERDESC *LPCDSCBUFFERDESC;
typedef struct _DSCBCAPS
{
DWORD dwSize;
DWORD dwFlags;
DWORD dwBufferBytes;
DWORD dwReserved;
} DSCBCAPS, *LPDSCBCAPS;
typedef const DSCBCAPS *LPCDSCBCAPS;
typedef struct _DSBPOSITIONNOTIFY
{
DWORD dwOffset;
HANDLE hEventNotify;
} DSBPOSITIONNOTIFY, *LPDSBPOSITIONNOTIFY;
typedef const DSBPOSITIONNOTIFY *LPCDSBPOSITIONNOTIFY;
typedef BOOL (CALLBACK *LPDSENUMCALLBACKA)(LPGUID, LPCSTR, LPCSTR, LPVOID);
typedef BOOL (CALLBACK *LPDSENUMCALLBACKW)(LPGUID, LPCWSTR, LPCWSTR, LPVOID);
extern HRESULT WINAPI DirectSoundCreate(LPCGUID, LPDIRECTSOUND *, LPUNKNOWN);
extern HRESULT WINAPI DirectSoundEnumerateA(LPDSENUMCALLBACKA, LPVOID);
extern HRESULT WINAPI DirectSoundEnumerateW(LPDSENUMCALLBACKW, LPVOID);
extern HRESULT WINAPI DirectSoundCaptureCreate(LPCGUID, LPDIRECTSOUNDCAPTURE *, LPUNKNOWN);
extern HRESULT WINAPI DirectSoundCaptureEnumerateA(LPDSENUMCALLBACKA, LPVOID);
extern HRESULT WINAPI DirectSoundCaptureEnumerateW(LPDSENUMCALLBACKW, LPVOID);
#ifdef UNICODE
#define LPDSENUMCALLBACK LPDSENUMCALLBACKW
#define DirectSoundEnumerate DirectSoundEnumerateW
#define DirectSoundCaptureEnumerate DirectSoundCaptureEnumerateW
#else 
#define LPDSENUMCALLBACK LPDSENUMCALLBACKA
#define DirectSoundEnumerate DirectSoundEnumerateA
#define DirectSoundCaptureEnumerate DirectSoundCaptureEnumerateA
#endif 
#ifndef IUnknown_QueryInterface
#define IUnknown_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#endif 
#ifndef IUnknown_AddRef
#define IUnknown_AddRef(p) (p)->lpVtbl->AddRef(p)
#endif 
#ifndef IUnknown_Release
#define IUnknown_Release(p) (p)->lpVtbl->Release(p)
#endif 
DEFINE_GUID(IID_IDirectSound, 0x279afa83, 0x4981, 4558, 165, 33, 0, 32, 175, 11, 229, 96);
#undef INTERFACE
#define INTERFACE IDirectSound
DECLARE_INTERFACE_(IDirectSound, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(CreateSoundBuffer) (THIS_ LPCDSBUFFERDESC, LPDIRECTSOUNDBUFFER *, LPUNKNOWN) ;
STDMETHOD(GetCaps) (THIS_ LPDSCAPS) ;
STDMETHOD(DuplicateSoundBuffer) (THIS_ LPDIRECTSOUNDBUFFER, LPDIRECTSOUNDBUFFER *) ;
STDMETHOD(SetCooperativeLevel) (THIS_ HWND, DWORD) ;
STDMETHOD(Compact) (THIS) ;
STDMETHOD(GetSpeakerConfig) (THIS_ LPDWORD) ;
STDMETHOD(SetSpeakerConfig) (THIS_ DWORD) ;
STDMETHOD(Initialize) (THIS_ LPCGUID) ;
};
#define IDirectSound_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSound_AddRef(p) IUnknown_AddRef(p)
#define IDirectSound_Release(p) IUnknown_Release(p)
#define IDirectSound_CreateSoundBuffer(p,a,b,c) (p)->lpVtbl->CreateSoundBuffer(p,a,b,c)
#define IDirectSound_GetCaps(p,a) (p)->lpVtbl->GetCaps(p,a)
#define IDirectSound_DuplicateSoundBuffer(p,a,b) (p)->lpVtbl->DuplicateSoundBuffer(p,a,b)
#define IDirectSound_SetCooperativeLevel(p,a,b) (p)->lpVtbl->SetCooperativeLevel(p,a,b)
#define IDirectSound_Compact(p) (p)->lpVtbl->Compact(p)
#define IDirectSound_GetSpeakerConfig(p,a) (p)->lpVtbl->GetSpeakerConfig(p,a)
#define IDirectSound_SetSpeakerConfig(p,b) (p)->lpVtbl->SetSpeakerConfig(p,b)
#define IDirectSound_Initialize(p,a) (p)->lpVtbl->Initialize(p,a)
DEFINE_GUID(IID_IDirectSoundBuffer, 0x279afa85, 0x4981, 4558, 165, 33, 0, 32, 175, 11, 229, 96);
#undef INTERFACE
#define INTERFACE IDirectSoundBuffer
DECLARE_INTERFACE_(IDirectSoundBuffer, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetCaps) (THIS_ LPDSBCAPS) ;
STDMETHOD(GetCurrentPosition) (THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetFormat) (THIS_ LPWAVEFORMATEX, DWORD, LPDWORD) ;
STDMETHOD(GetVolume) (THIS_ LPLONG) ;
STDMETHOD(GetPan) (THIS_ LPLONG) ;
STDMETHOD(GetFrequency) (THIS_ LPDWORD) ;
STDMETHOD(GetStatus) (THIS_ LPDWORD) ;
STDMETHOD(Initialize) (THIS_ LPDIRECTSOUND, LPCDSBUFFERDESC) ;
STDMETHOD(Lock) (THIS_ DWORD, DWORD, LPVOID *, LPDWORD, LPVOID *, LPDWORD, DWORD) ;
STDMETHOD(Play) (THIS_ DWORD, DWORD, DWORD) ;
STDMETHOD(SetCurrentPosition) (THIS_ DWORD) ;
STDMETHOD(SetFormat) (THIS_ LPCWAVEFORMATEX) ;
STDMETHOD(SetVolume) (THIS_ LONG) ;
STDMETHOD(SetPan) (THIS_ LONG) ;
STDMETHOD(SetFrequency) (THIS_ DWORD) ;
STDMETHOD(Stop) (THIS) ;
STDMETHOD(Unlock) (THIS_ LPVOID, DWORD, LPVOID, DWORD) ;
STDMETHOD(Restore) (THIS) ;
};
#define IDirectSoundBuffer_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSoundBuffer_AddRef(p) IUnknown_AddRef(p)
#define IDirectSoundBuffer_Release(p) IUnknown_Release(p)
#define IDirectSoundBuffer_GetCaps(p,a) (p)->lpVtbl->GetCaps(p,a)
#define IDirectSoundBuffer_GetCurrentPosition(p,a,b) (p)->lpVtbl->GetCurrentPosition(p,a,b)
#define IDirectSoundBuffer_GetFormat(p,a,b,c) (p)->lpVtbl->GetFormat(p,a,b,c)
#define IDirectSoundBuffer_GetVolume(p,a) (p)->lpVtbl->GetVolume(p,a)
#define IDirectSoundBuffer_GetPan(p,a) (p)->lpVtbl->GetPan(p,a)
#define IDirectSoundBuffer_GetFrequency(p,a) (p)->lpVtbl->GetFrequency(p,a)
#define IDirectSoundBuffer_GetStatus(p,a) (p)->lpVtbl->GetStatus(p,a)
#define IDirectSoundBuffer_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectSoundBuffer_Lock(p,a,b,c,d,e,f,g) (p)->lpVtbl->Lock(p,a,b,c,d,e,f,g)
#define IDirectSoundBuffer_Play(p,a,b,c) (p)->lpVtbl->Play(p,a,b,c)
#define IDirectSoundBuffer_SetCurrentPosition(p,a) (p)->lpVtbl->SetCurrentPosition(p,a)
#define IDirectSoundBuffer_SetFormat(p,a) (p)->lpVtbl->SetFormat(p,a)
#define IDirectSoundBuffer_SetVolume(p,a) (p)->lpVtbl->SetVolume(p,a)
#define IDirectSoundBuffer_SetPan(p,a) (p)->lpVtbl->SetPan(p,a)
#define IDirectSoundBuffer_SetFrequency(p,a) (p)->lpVtbl->SetFrequency(p,a)
#define IDirectSoundBuffer_Stop(p) (p)->lpVtbl->Stop(p)
#define IDirectSoundBuffer_Unlock(p,a,b,c,d) (p)->lpVtbl->Unlock(p,a,b,c,d)
#define IDirectSoundBuffer_Restore(p) (p)->lpVtbl->Restore(p)
DEFINE_GUID(IID_IDirectSound3DListener, 0x279afa84, 0x4981, 4558, 165, 33, 0, 32, 175, 11, 229, 96);
#undef INTERFACE
#define INTERFACE IDirectSound3DListener
DECLARE_INTERFACE_(IDirectSound3DListener, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetAllParameters) (THIS_ LPDS3DLISTENER) ;
STDMETHOD(GetDistanceFactor) (THIS_ LPD3DVALUE) ;
STDMETHOD(GetDopplerFactor) (THIS_ LPD3DVALUE) ;
STDMETHOD(GetOrientation) (THIS_ LPD3DVECTOR, LPD3DVECTOR) ;
STDMETHOD(GetPosition) (THIS_ LPD3DVECTOR) ;
STDMETHOD(GetRolloffFactor) (THIS_ LPD3DVALUE) ;
STDMETHOD(GetVelocity) (THIS_ LPD3DVECTOR) ;
STDMETHOD(SetAllParameters) (THIS_ LPCDS3DLISTENER, DWORD) ;
STDMETHOD(SetDistanceFactor) (THIS_ D3DVALUE, DWORD) ;
STDMETHOD(SetDopplerFactor) (THIS_ D3DVALUE, DWORD) ;
STDMETHOD(SetOrientation) (THIS_ D3DVALUE, D3DVALUE, D3DVALUE, D3DVALUE, D3DVALUE, D3DVALUE, DWORD) ;
STDMETHOD(SetPosition) (THIS_ D3DVALUE, D3DVALUE, D3DVALUE, DWORD) ;
STDMETHOD(SetRolloffFactor) (THIS_ D3DVALUE, DWORD) ;
STDMETHOD(SetVelocity) (THIS_ D3DVALUE, D3DVALUE, D3DVALUE, DWORD) ;
STDMETHOD(CommitDeferredSettings) (THIS) ;
};
#define IDirectSound3DListener_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSound3DListener_AddRef(p) IUnknown_AddRef(p)
#define IDirectSound3DListener_Release(p) IUnknown_Release(p)
#define IDirectSound3DListener_GetAllParameters(p,a) (p)->lpVtbl->GetAllParameters(p,a)
#define IDirectSound3DListener_GetDistanceFactor(p,a) (p)->lpVtbl->GetDistanceFactor(p,a)
#define IDirectSound3DListener_GetDopplerFactor(p,a) (p)->lpVtbl->GetDopplerFactor(p,a)
#define IDirectSound3DListener_GetOrientation(p,a,b) (p)->lpVtbl->GetOrientation(p,a,b)
#define IDirectSound3DListener_GetPosition(p,a) (p)->lpVtbl->GetPosition(p,a)
#define IDirectSound3DListener_GetRolloffFactor(p,a) (p)->lpVtbl->GetRolloffFactor(p,a)
#define IDirectSound3DListener_GetVelocity(p,a) (p)->lpVtbl->GetVelocity(p,a)
#define IDirectSound3DListener_SetAllParameters(p,a,b) (p)->lpVtbl->SetAllParameters(p,a,b)
#define IDirectSound3DListener_SetDistanceFactor(p,a,b) (p)->lpVtbl->SetDistanceFactor(p,a,b)
#define IDirectSound3DListener_SetDopplerFactor(p,a,b) (p)->lpVtbl->SetDopplerFactor(p,a,b)
#define IDirectSound3DListener_SetOrientation(p,a,b,c,d,e,f,g) (p)->lpVtbl->SetOrientation(p,a,b,c,d,e,f,g)
#define IDirectSound3DListener_SetPosition(p,a,b,c,d) (p)->lpVtbl->SetPosition(p,a,b,c,d)
#define IDirectSound3DListener_SetRolloffFactor(p,a,b) (p)->lpVtbl->SetRolloffFactor(p,a,b)
#define IDirectSound3DListener_SetVelocity(p,a,b,c,d) (p)->lpVtbl->SetVelocity(p,a,b,c,d)
#define IDirectSound3DListener_CommitDeferredSettings(p) (p)->lpVtbl->CommitDeferredSettings(p)
DEFINE_GUID(IID_IDirectSound3DBuffer, 0x279afa86, 0x4981, 4558, 165, 33, 0, 32, 175, 11, 229, 96);
#undef INTERFACE
#define INTERFACE IDirectSound3DBuffer
DECLARE_INTERFACE_(IDirectSound3DBuffer, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetAllParameters) (THIS_ LPDS3DBUFFER) ;
STDMETHOD(GetConeAngles) (THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetConeOrientation) (THIS_ LPD3DVECTOR) ;
STDMETHOD(GetConeOutsideVolume) (THIS_ LPLONG) ;
STDMETHOD(GetMaxDistance) (THIS_ LPD3DVALUE) ;
STDMETHOD(GetMinDistance) (THIS_ LPD3DVALUE) ;
STDMETHOD(GetMode) (THIS_ LPDWORD) ;
STDMETHOD(GetPosition) (THIS_ LPD3DVECTOR) ;
STDMETHOD(GetVelocity) (THIS_ LPD3DVECTOR) ;
STDMETHOD(SetAllParameters) (THIS_ LPCDS3DBUFFER, DWORD) ;
STDMETHOD(SetConeAngles) (THIS_ DWORD, DWORD, DWORD) ;
STDMETHOD(SetConeOrientation) (THIS_ D3DVALUE, D3DVALUE, D3DVALUE, DWORD) ;
STDMETHOD(SetConeOutsideVolume) (THIS_ LONG, DWORD) ;
STDMETHOD(SetMaxDistance) (THIS_ D3DVALUE, DWORD) ;
STDMETHOD(SetMinDistance) (THIS_ D3DVALUE, DWORD) ;
STDMETHOD(SetMode) (THIS_ DWORD, DWORD) ;
STDMETHOD(SetPosition) (THIS_ D3DVALUE, D3DVALUE, D3DVALUE, DWORD) ;
STDMETHOD(SetVelocity) (THIS_ D3DVALUE, D3DVALUE, D3DVALUE, DWORD) ;
};
#define IDirectSound3DBuffer_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSound3DBuffer_AddRef(p) IUnknown_AddRef(p)
#define IDirectSound3DBuffer_Release(p) IUnknown_Release(p)
#define IDirectSound3DBuffer_GetAllParameters(p,a) (p)->lpVtbl->GetAllParameters(p,a)
#define IDirectSound3DBuffer_GetConeAngles(p,a,b) (p)->lpVtbl->GetConeAngles(p,a,b)
#define IDirectSound3DBuffer_GetConeOrientation(p,a) (p)->lpVtbl->GetConeOrientation(p,a)
#define IDirectSound3DBuffer_GetConeOutsideVolume(p,a) (p)->lpVtbl->GetConeOutsideVolume(p,a)
#define IDirectSound3DBuffer_GetPosition(p,a) (p)->lpVtbl->GetPosition(p,a)
#define IDirectSound3DBuffer_GetMinDistance(p,a) (p)->lpVtbl->GetMinDistance(p,a)
#define IDirectSound3DBuffer_GetMaxDistance(p,a) (p)->lpVtbl->GetMaxDistance(p,a)
#define IDirectSound3DBuffer_GetMode(p,a) (p)->lpVtbl->GetMode(p,a)
#define IDirectSound3DBuffer_GetVelocity(p,a) (p)->lpVtbl->GetVelocity(p,a)
#define IDirectSound3DBuffer_SetAllParameters(p,a,b) (p)->lpVtbl->SetAllParameters(p,a,b)
#define IDirectSound3DBuffer_SetConeAngles(p,a,b,c) (p)->lpVtbl->SetConeAngles(p,a,b,c)
#define IDirectSound3DBuffer_SetConeOrientation(p,a,b,c,d) (p)->lpVtbl->SetConeOrientation(p,a,b,c,d)
#define IDirectSound3DBuffer_SetConeOutsideVolume(p,a,b) (p)->lpVtbl->SetConeOutsideVolume(p,a,b)
#define IDirectSound3DBuffer_SetPosition(p,a,b,c,d) (p)->lpVtbl->SetPosition(p,a,b,c,d)
#define IDirectSound3DBuffer_SetMinDistance(p,a,b) (p)->lpVtbl->SetMinDistance(p,a,b)
#define IDirectSound3DBuffer_SetMaxDistance(p,a,b) (p)->lpVtbl->SetMaxDistance(p,a,b)
#define IDirectSound3DBuffer_SetMode(p,a,b) (p)->lpVtbl->SetMode(p,a,b)
#define IDirectSound3DBuffer_SetVelocity(p,a,b,c,d) (p)->lpVtbl->SetVelocity(p,a,b,c,d)
DEFINE_GUID(IID_IDirectSoundCapture, 0xb0210781, 0x89cd, 4560, 175, 8, 0, 160, 201, 37, 205, 22);
#undef INTERFACE
#define INTERFACE IDirectSoundCapture
DECLARE_INTERFACE_(IDirectSoundCapture, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(CreateCaptureBuffer) (THIS_ LPCDSCBUFFERDESC, LPDIRECTSOUNDCAPTUREBUFFER *, LPUNKNOWN) ;
STDMETHOD(GetCaps) (THIS_ LPDSCCAPS) ;
STDMETHOD(Initialize) (THIS_ LPCGUID) ;
};
#define IDirectSoundCapture_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSoundCapture_AddRef(p) IUnknown_AddRef(p)
#define IDirectSoundCapture_Release(p) IUnknown_Release(p)
#define IDirectSoundCapture_CreateCaptureBuffer(p,a,b,c) (p)->lpVtbl->CreateCaptureBuffer(p,a,b,c)
#define IDirectSoundCapture_GetCaps(p,a) (p)->lpVtbl->GetCaps(p,a)
#define IDirectSoundCapture_Initialize(p,a) (p)->lpVtbl->Initialize(p,a)
DEFINE_GUID(IID_IDirectSoundCaptureBuffer, 0xb0210782, 0x89cd, 4560, 175, 8, 0, 160, 201, 37, 205, 22);
#undef INTERFACE
#define INTERFACE IDirectSoundCaptureBuffer
DECLARE_INTERFACE_(IDirectSoundCaptureBuffer, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(GetCaps) (THIS_ LPDSCBCAPS) ;
STDMETHOD(GetCurrentPosition) (THIS_ LPDWORD, LPDWORD) ;
STDMETHOD(GetFormat) (THIS_ LPWAVEFORMATEX, DWORD, LPDWORD) ;
STDMETHOD(GetStatus) (THIS_ LPDWORD) ;
STDMETHOD(Initialize) (THIS_ LPDIRECTSOUNDCAPTURE, LPCDSCBUFFERDESC) ;
STDMETHOD(Lock) (THIS_ DWORD, DWORD, LPVOID *, LPDWORD, LPVOID *, LPDWORD, DWORD) ;
STDMETHOD(Start) (THIS_ DWORD) ;
STDMETHOD(Stop) (THIS) ;
STDMETHOD(Unlock) (THIS_ LPVOID, DWORD, LPVOID, DWORD) ;
};
#define IDirectSoundCaptureBuffer_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSoundCaptureBuffer_AddRef(p) IUnknown_AddRef(p)
#define IDirectSoundCaptureBuffer_Release(p) IUnknown_Release(p)
#define IDirectSoundCaptureBuffer_GetCaps(p,a) (p)->lpVtbl->GetCaps(p,a)
#define IDirectSoundCaptureBuffer_GetCurrentPosition(p,a,b) (p)->lpVtbl->GetCurrentPosition(p,a,b)
#define IDirectSoundCaptureBuffer_GetFormat(p,a,b,c) (p)->lpVtbl->GetFormat(p,a,b,c)
#define IDirectSoundCaptureBuffer_GetStatus(p,a) (p)->lpVtbl->GetStatus(p,a)
#define IDirectSoundCaptureBuffer_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirectSoundCaptureBuffer_Lock(p,a,b,c,d,e,f,g) (p)->lpVtbl->Lock(p,a,b,c,d,e,f,g)
#define IDirectSoundCaptureBuffer_Start(p,a) (p)->lpVtbl->Start(p,a)
#define IDirectSoundCaptureBuffer_Stop(p) (p)->lpVtbl->Stop(p)
#define IDirectSoundCaptureBuffer_Unlock(p,a,b,c,d) (p)->lpVtbl->Unlock(p,a,b,c,d)
DEFINE_GUID(IID_IDirectSoundNotify, 0xb0210783, 0x89cd, 4560, 175, 8, 0, 160, 201, 37, 205, 22);
#undef INTERFACE
#define INTERFACE IDirectSoundNotify
DECLARE_INTERFACE_(IDirectSoundNotify, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(SetNotificationPositions) (THIS_ DWORD, LPCDSBPOSITIONNOTIFY) ;
};
#define IDirectSoundNotify_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IDirectSoundNotify_AddRef(p) IUnknown_AddRef(p)
#define IDirectSoundNotify_Release(p) IUnknown_Release(p)
#define IDirectSoundNotify_SetNotificationPositions(p,a,b) (p)->lpVtbl->SetNotificationPositions(p,a,b)
#ifndef _IKsPropertySet_
#define _IKsPropertySet_
typedef struct IKsPropertySet *LPKSPROPERTYSET;
#define KSPROPERTY_SUPPORT_GET 1
#define KSPROPERTY_SUPPORT_SET 2
DEFINE_GUID(IID_IKsPropertySet, 0x31efac30, 0x515c, 4560, 169, 170, 0, 170, 0, 97, 190, 147);
#undef INTERFACE
#define INTERFACE IKsPropertySet
DECLARE_INTERFACE_(IKsPropertySet, IUnknown)
{
STDMETHOD(QueryInterface) (THIS_ REFIID, LPVOID *) ;
STDMETHOD_(ULONG,AddRef) (THIS) ;
STDMETHOD_(ULONG,Release) (THIS) ;
STDMETHOD(Get) (THIS_ REFGUID, ULONG, LPVOID, ULONG, LPVOID, ULONG, PULONG) ;
STDMETHOD(Set) (THIS_ REFGUID, ULONG, LPVOID, ULONG, LPVOID, ULONG) ;
STDMETHOD(QuerySupport) (THIS_ REFGUID, ULONG, PULONG) ;
};
#define IKsPropertySet_QueryInterface(p,a,b) IUnknown_QueryInterface(p,a,b)
#define IKsPropertySet_AddRef(p) IUnknown_AddRef(p)
#define IKsPropertySet_Release(p) IUnknown_Release(p)
#define IKsPropertySet_Get(p,a,b,c,d,e,f,g) (p)->lpVtbl->Get(p,a,b,c,d,e,f,g)
#define IKsPropertySet_Set(p,a,b,c,d,e,f) (p)->lpVtbl->Set(p,a,b,c,d,e,f)
#define IKsPropertySet_QuerySupport(p,a,b,c) (p)->lpVtbl->QuerySupport(p,a,b,c)
#endif 
#define DS_OK S_OK
#define DS_NO_VIRTUALIZATION MAKE_HRESULT(0, _FACDS, 10)
#define DSERR_ALLOCATED MAKE_DSHRESULT(10)
#define DSERR_CONTROLUNAVAIL MAKE_DSHRESULT(30)
#define DSERR_INVALIDPARAM E_INVALIDARG
#define DSERR_INVALIDCALL MAKE_DSHRESULT(50)
#define DSERR_GENERIC E_FAIL
#define DSERR_PRIOLEVELNEEDED MAKE_DSHRESULT(70)
#define DSERR_OUTOFMEMORY E_OUTOFMEMORY
#define DSERR_BADFORMAT MAKE_DSHRESULT(100)
#define DSERR_UNSUPPORTED E_NOTIMPL
#define DSERR_NODRIVER MAKE_DSHRESULT(120)
#define DSERR_ALREADYINITIALIZED MAKE_DSHRESULT(130)
#define DSERR_NOAGGREGATION CLASS_E_NOAGGREGATION
#define DSERR_BUFFERLOST MAKE_DSHRESULT(150)
#define DSERR_OTHERAPPHASPRIO MAKE_DSHRESULT(160)
#define DSERR_UNINITIALIZED MAKE_DSHRESULT(170)
#define DSERR_NOINTERFACE E_NOINTERFACE
#define DSERR_ACCESSDENIED E_ACCESSDENIED
#define DSCAPS_PRIMARYMONO 1
#define DSCAPS_PRIMARYSTEREO 2
#define DSCAPS_PRIMARY8BIT 4
#define DSCAPS_PRIMARY16BIT 8
#define DSCAPS_CONTINUOUSRATE 16
#define DSCAPS_EMULDRIVER 32
#define DSCAPS_CERTIFIED 64
#define DSCAPS_SECONDARYMONO 256
#define DSCAPS_SECONDARYSTEREO 512
#define DSCAPS_SECONDARY8BIT 1024
#define DSCAPS_SECONDARY16BIT 2048
#define DSSCL_NORMAL 1
#define DSSCL_PRIORITY 2
#define DSSCL_EXCLUSIVE 3
#define DSSCL_WRITEPRIMARY 4
#define DSSPEAKER_HEADPHONE 1
#define DSSPEAKER_MONO 2
#define DSSPEAKER_QUAD 3
#define DSSPEAKER_STEREO 4
#define DSSPEAKER_SURROUND 5
#define DSSPEAKER_5POINT1 6
#define DSSPEAKER_GEOMETRY_MIN 5
#define DSSPEAKER_GEOMETRY_NARROW 10
#define DSSPEAKER_GEOMETRY_WIDE 20
#define DSSPEAKER_GEOMETRY_MAX 180
#define DSSPEAKER_COMBINED(c, g) ((DWORD)(((BYTE)(c)) | ((DWORD)((BYTE)(g))) << 16))
#define DSSPEAKER_CONFIG(a) ((BYTE)(a))
#define DSSPEAKER_GEOMETRY(a) ((BYTE)(((DWORD)(a) >> 16) & 255))
#define DSBCAPS_PRIMARYBUFFER 1
#define DSBCAPS_STATIC 2
#define DSBCAPS_LOCHARDWARE 4
#define DSBCAPS_LOCSOFTWARE 8
#define DSBCAPS_CTRL3D 16
#define DSBCAPS_CTRLFREQUENCY 32
#define DSBCAPS_CTRLPAN 64
#define DSBCAPS_CTRLVOLUME 128
#define DSBCAPS_CTRLPOSITIONNOTIFY 256
#define DSBCAPS_CTRLDEFAULT	0x0E0
#define DSBCAPS_CTRLALL	0x01F0
#define DSBCAPS_STICKYFOCUS 0x4000
#define DSBCAPS_GLOBALFOCUS 0x8000
#define DSBCAPS_GETCURRENTPOSITION2 0x10000
#define DSBCAPS_MUTE3DATMAXDISTANCE 0x20000
#define DSBCAPS_LOCDEFER 0x40000
#define DSBPLAY_LOOPING 1
#define DSBPLAY_LOCHARDWARE 2
#define DSBPLAY_LOCSOFTWARE 4
#define DSBPLAY_TERMINATEBY_TIME 8
#define DSBPLAY_TERMINATEBY_DISTANCE 16
#define DSBPLAY_TERMINATEBY_PRIORITY 32
#define DSBSTATUS_PLAYING 1
#define DSBSTATUS_BUFFERLOST 2
#define DSBSTATUS_LOOPING 4
#define DSBSTATUS_LOCHARDWARE 8
#define DSBSTATUS_LOCSOFTWARE 16
#define DSBSTATUS_TERMINATED 32
#define DSBLOCK_FROMWRITECURSOR 1
#define DSBLOCK_ENTIREBUFFER 2
#define DSBFREQUENCY_MIN 100
#define DSBFREQUENCY_MAX 100000
#define DSBFREQUENCY_ORIGINAL 0
#define DSBPAN_LEFT -10000
#define DSBPAN_CENTER 0
#define DSBPAN_RIGHT 10000
#define DSBVOLUME_MIN -10000
#define DSBVOLUME_MAX 0
#define DSBSIZE_MIN 4
#define DSBSIZE_MAX 0xfffffff
#define DS3DMODE_NORMAL 0
#define DS3DMODE_HEADRELATIVE 1
#define DS3DMODE_DISABLE 2
#define DS3D_IMMEDIATE 0
#define DS3D_DEFERRED 1
#define DS3D_MINDISTANCEFACTOR FLT_MIN
#define DS3D_MAXDISTANCEFACTOR FLT_MAX
#define DS3D_DEFAULTDISTANCEFACTOR 1.0f
#define DS3D_MINROLLOFFFACTOR 0.0f
#define DS3D_MAXROLLOFFFACTOR 10.0f
#define DS3D_DEFAULTROLLOFFFACTOR 1.0f
#define DS3D_MINDOPPLERFACTOR 0.0f
#define DS3D_MAXDOPPLERFACTOR 10.0f
#define DS3D_DEFAULTDOPPLERFACTOR 1.0f
#define DS3D_DEFAULTMINDISTANCE 1.0f
#define DS3D_DEFAULTMAXDISTANCE 1000000000.0f
#define DS3D_MINCONEANGLE 0
#define DS3D_MAXCONEANGLE 360
#define DS3D_DEFAULTCONEANGLE 360
#define DS3D_DEFAULTCONEOUTSIDEVOLUME DSBVOLUME_MAX
#define DSCCAPS_EMULDRIVER DSCAPS_EMULDRIVER
#define DSCCAPS_CERTIFIED DSCAPS_CERTIFIED
#define DSCBCAPS_WAVEMAPPED 0x80000000
#define DSCBLOCK_ENTIREBUFFER 1
#define DSCBSTATUS_CAPTURING 1
#define DSCBSTATUS_LOOPING 2
#define DSCBSTART_LOOPING 1
#define DSBPN_OFFSETSTOP 0xffffffff
#define DS3DALG_DEFAULT GUID_NULL
DEFINE_GUID(DS3DALG_NO_VIRTUALIZATION, 0xc241333f, 7195, 4562, 148, 245, 0, 192, 79, 194, 138, 202);
DEFINE_GUID(DS3DALG_HRTF_FULL, 0xc2413340, 7195, 4562, 148, 245, 0, 192, 79, 194, 138, 202);
DEFINE_GUID(DS3DALG_HRTF_LIGHT, 0xc2413342, 7195, 4562, 148, 245, 0, 192, 79, 194, 138, 202);
#endif 
