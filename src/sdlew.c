/*
 * Copyright 2014 Blender Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 */

#ifdef _MSC_VER
#  define snprintf _snprintf
#  define popen _popen
#  define pclose _pclose
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include "sdlew.h"

#include "SDL/SDL.h"
#include "SDL/SDL_syswm.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  define VC_EXTRALEAN
#  include <windows.h>

/* Utility macros. */

typedef HMODULE DynamicLibrary;

#  define dynamic_library_open(path)         LoadLibrary(path)
#  define dynamic_library_close(lib)         FreeLibrary(lib)
#  define dynamic_library_find(lib, symbol)  GetProcAddress(lib, symbol)
#else
#  include <dlfcn.h>

typedef void* DynamicLibrary;

#  define dynamic_library_open(path)         dlopen(path, RTLD_NOW)
#  define dynamic_library_close(lib)         dlclose(lib)
#  define dynamic_library_find(lib, symbol)  dlsym(lib, symbol)
#endif

#define SDL_LIBRARY_FIND_CHECKED(name)         name = (t##name *)dynamic_library_find(lib, #name);         assert(name);

#define SDL_LIBRARY_FIND(name)         name = (t##name *)dynamic_library_find(lib, #name);

static DynamicLibrary lib;

#ifndef HAVE_FREE
tSDL_free *SDL_free;
#endif
#ifndef HAVE_PUTENV
tSDL_putenv *SDL_putenv;
#endif
#ifndef HAVE_QSORT
tSDL_qsort *SDL_qsort;
#endif
#ifndef HAVE_MEMCMP
tSDL_memcmp *SDL_memcmp;
#endif
#ifndef HAVE_STRLEN
tSDL_strlen *SDL_strlen;
#endif
#ifndef HAVE_STRLCPY
tSDL_strlcpy *SDL_strlcpy;
#endif
#ifndef HAVE_STRLCAT
tSDL_strlcat *SDL_strlcat;
#endif
#ifndef HAVE_STRTOL
tSDL_strtol *SDL_strtol;
#endif
#ifndef HAVE_STRTOLL
tSDL_strtoll *SDL_strtoll;
#endif
#ifndef HAVE_STRTOULL
tSDL_strtoull *SDL_strtoull;
#endif
#ifndef HAVE_STRTOD
tSDL_strtod *SDL_strtod;
#endif
#ifndef HAVE_STRCMP
tSDL_strcmp *SDL_strcmp;
#endif
#ifndef HAVE_STRNCMP
tSDL_strncmp *SDL_strncmp;
#endif
#ifndef HAVE_STRCASECMP
tSDL_strcasecmp *SDL_strcasecmp;
#endif
#ifndef HAVE_STRNCASECMP
tSDL_strncasecmp *SDL_strncasecmp;
#endif
#ifndef HAVE_SSCANF
tSDL_sscanf *SDL_sscanf;
#endif
#ifndef HAVE_SNPRINTF
tSDL_snprintf *SDL_snprintf;
#endif
#ifndef HAVE_VSNPRINTF
tSDL_vsnprintf *SDL_vsnprintf;
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
tSDL_iconv_open *SDL_iconv_open;
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
tSDL_iconv_close *SDL_iconv_close;
#endif
tSDL_iconv *SDL_iconv;
tSDL_UnloadObject *SDL_UnloadObject;
tSDL_mutexP *SDL_mutexP;
tSDL_mutexV *SDL_mutexV;
tSDL_DestroyMutex *SDL_DestroyMutex;
tSDL_DestroySemaphore *SDL_DestroySemaphore;
tSDL_SemWait *SDL_SemWait;
tSDL_SemTryWait *SDL_SemTryWait;
tSDL_SemWaitTimeout *SDL_SemWaitTimeout;
tSDL_SemPost *SDL_SemPost;
tSDL_SemValue *SDL_SemValue;
tSDL_DestroyCond *SDL_DestroyCond;
tSDL_CondSignal *SDL_CondSignal;
tSDL_CondBroadcast *SDL_CondBroadcast;
tSDL_CondWait *SDL_CondWait;
tSDL_CondWaitTimeout *SDL_CondWaitTimeout;
tSDL_PumpEvents *SDL_PumpEvents;
tSDL_PeepEvents *SDL_PeepEvents;
tSDL_PollEvent *SDL_PollEvent;
tSDL_WaitEvent *SDL_WaitEvent;
tSDL_PushEvent *SDL_PushEvent;
tSDL_SetEventFilter *SDL_SetEventFilter;
tSDL_GetEventFilter *SDL_GetEventFilter;
tSDL_EventState *SDL_EventState;
tSDL_GetAppState *SDL_GetAppState;
tSDL_GetMouseState *SDL_GetMouseState;
tSDL_GetRelativeMouseState *SDL_GetRelativeMouseState;
tSDL_WarpMouse *SDL_WarpMouse;
tSDL_SetCursor *SDL_SetCursor;
tSDL_FreeCursor *SDL_FreeCursor;
tSDL_ShowCursor *SDL_ShowCursor;
tSDL_ThreadID *SDL_ThreadID;
tSDL_GetThreadID *SDL_GetThreadID;
tSDL_WaitThread *SDL_WaitThread;
tSDL_KillThread *SDL_KillThread;
tSDL_EnableUNICODE *SDL_EnableUNICODE;
tSDL_EnableKeyRepeat *SDL_EnableKeyRepeat;
tSDL_GetKeyRepeat *SDL_GetKeyRepeat;
tSDL_GetModState *SDL_GetModState;
tSDL_SetModState *SDL_SetModState;
tSDL_AudioInit *SDL_AudioInit;
tSDL_AudioQuit *SDL_AudioQuit;
tSDL_OpenAudio *SDL_OpenAudio;
tSDL_GetAudioStatus *SDL_GetAudioStatus;
tSDL_PauseAudio *SDL_PauseAudio;
tSDL_FreeWAV *SDL_FreeWAV;
tSDL_BuildAudioCVT *SDL_BuildAudioCVT;
tSDL_ConvertAudio *SDL_ConvertAudio;
tSDL_MixAudio *SDL_MixAudio;
tSDL_LockAudio *SDL_LockAudio;
tSDL_UnlockAudio *SDL_UnlockAudio;
tSDL_CloseAudio *SDL_CloseAudio;
tSDL_VideoInit *SDL_VideoInit;
tSDL_VideoQuit *SDL_VideoQuit;
tSDL_VideoModeOK *SDL_VideoModeOK;
tSDL_UpdateRects *SDL_UpdateRects;
tSDL_UpdateRect *SDL_UpdateRect;
tSDL_Flip *SDL_Flip;
tSDL_SetGamma *SDL_SetGamma;
tSDL_SetGammaRamp *SDL_SetGammaRamp;
tSDL_GetGammaRamp *SDL_GetGammaRamp;
tSDL_SetColors *SDL_SetColors;
tSDL_SetPalette *SDL_SetPalette;
tSDL_MapRGB *SDL_MapRGB;
tSDL_MapRGBA *SDL_MapRGBA;
tSDL_GetRGB *SDL_GetRGB;
tSDL_GetRGBA *SDL_GetRGBA;
tSDL_FreeSurface *SDL_FreeSurface;
tSDL_LockSurface *SDL_LockSurface;
tSDL_UnlockSurface *SDL_UnlockSurface;
tSDL_SaveBMP_RW *SDL_SaveBMP_RW;
tSDL_SetColorKey *SDL_SetColorKey;
tSDL_SetAlpha *SDL_SetAlpha;
tSDL_SetClipRect *SDL_SetClipRect;
tSDL_GetClipRect *SDL_GetClipRect;
tSDL_UpperBlit *SDL_UpperBlit;
tSDL_LowerBlit *SDL_LowerBlit;
tSDL_FillRect *SDL_FillRect;
tSDL_LockYUVOverlay *SDL_LockYUVOverlay;
tSDL_UnlockYUVOverlay *SDL_UnlockYUVOverlay;
tSDL_DisplayYUVOverlay *SDL_DisplayYUVOverlay;
tSDL_FreeYUVOverlay *SDL_FreeYUVOverlay;
tSDL_GL_LoadLibrary *SDL_GL_LoadLibrary;
tSDL_GL_SetAttribute *SDL_GL_SetAttribute;
tSDL_GL_GetAttribute *SDL_GL_GetAttribute;
tSDL_GL_SwapBuffers *SDL_GL_SwapBuffers;
tSDL_GL_UpdateRects *SDL_GL_UpdateRects;
tSDL_GL_Lock *SDL_GL_Lock;
tSDL_GL_Unlock *SDL_GL_Unlock;
tSDL_WM_SetCaption *SDL_WM_SetCaption;
tSDL_WM_GetCaption *SDL_WM_GetCaption;
tSDL_WM_SetIcon *SDL_WM_SetIcon;
tSDL_WM_IconifyWindow *SDL_WM_IconifyWindow;
tSDL_WM_ToggleFullScreen *SDL_WM_ToggleFullScreen;
tSDL_WM_GrabInput *SDL_WM_GrabInput;
tSDL_SoftStretch *SDL_SoftStretch;
tSDL_FreeRW *SDL_FreeRW;
tSDL_ReadLE16 *SDL_ReadLE16;
tSDL_ReadBE16 *SDL_ReadBE16;
tSDL_ReadLE32 *SDL_ReadLE32;
tSDL_ReadBE32 *SDL_ReadBE32;
tSDL_ReadLE64 *SDL_ReadLE64;
tSDL_ReadBE64 *SDL_ReadBE64;
tSDL_WriteLE16 *SDL_WriteLE16;
tSDL_WriteBE16 *SDL_WriteBE16;
tSDL_WriteLE32 *SDL_WriteLE32;
tSDL_WriteBE32 *SDL_WriteBE32;
tSDL_WriteLE64 *SDL_WriteLE64;
tSDL_WriteBE64 *SDL_WriteBE64;
tSDL_Init *SDL_Init;
tSDL_InitSubSystem *SDL_InitSubSystem;
tSDL_QuitSubSystem *SDL_QuitSubSystem;
tSDL_WasInit *SDL_WasInit;
tSDL_Quit *SDL_Quit;
tSDL_GetTicks *SDL_GetTicks;
tSDL_Delay *SDL_Delay;
tSDL_SetTimer *SDL_SetTimer;
tSDL_AddTimer *SDL_AddTimer;
tSDL_RemoveTimer *SDL_RemoveTimer;
tSDL_NumJoysticks *SDL_NumJoysticks;
tSDL_JoystickOpened *SDL_JoystickOpened;
tSDL_JoystickIndex *SDL_JoystickIndex;
tSDL_JoystickNumAxes *SDL_JoystickNumAxes;
tSDL_JoystickNumBalls *SDL_JoystickNumBalls;
tSDL_JoystickNumHats *SDL_JoystickNumHats;
tSDL_JoystickNumButtons *SDL_JoystickNumButtons;
tSDL_JoystickUpdate *SDL_JoystickUpdate;
tSDL_JoystickEventState *SDL_JoystickEventState;
tSDL_JoystickGetAxis *SDL_JoystickGetAxis;
tSDL_JoystickGetHat *SDL_JoystickGetHat;
tSDL_JoystickGetBall *SDL_JoystickGetBall;
tSDL_JoystickGetButton *SDL_JoystickGetButton;
tSDL_JoystickClose *SDL_JoystickClose;
tSDL_CDNumDrives *SDL_CDNumDrives;
tSDL_CDStatus *SDL_CDStatus;
tSDL_CDPlayTracks *SDL_CDPlayTracks;
tSDL_CDPlay *SDL_CDPlay;
tSDL_CDPause *SDL_CDPause;
tSDL_CDResume *SDL_CDResume;
tSDL_CDStop *SDL_CDStop;
tSDL_CDEject *SDL_CDEject;
tSDL_CDClose *SDL_CDClose;
tSDL_HasRDTSC *SDL_HasRDTSC;
tSDL_HasMMX *SDL_HasMMX;
tSDL_HasMMXExt *SDL_HasMMXExt;
tSDL_Has3DNow *SDL_Has3DNow;
tSDL_Has3DNowExt *SDL_Has3DNowExt;
tSDL_HasSSE *SDL_HasSSE;
tSDL_HasSSE2 *SDL_HasSSE2;
tSDL_HasAltiVec *SDL_HasAltiVec;
tSDL_SetError *SDL_SetError;
tSDL_ClearError *SDL_ClearError;
tSDL_Error *SDL_Error;
tSDL_GetWMInfo *SDL_GetWMInfo;

static void sdlewExit(void) {
  if(lib != NULL) {
    /*  Ignore errors. */
    dynamic_library_close(lib);
    lib = NULL;
  }
}

/* Implementation function. */
int sdlewInit(void) {
  /* Library paths. */
#ifdef _WIN32
  /* Expected in c:/windows/system or similar, no path needed. */
  const char *path = "SDL.dll";
#elif defined(__APPLE__)
  /* Default installation path. */
  const char *path = "/usr/local/cuda/lib/libSDL.dylib";
#else
  const char *path = "libSDL.so";
#endif
  static int initialized = 0;
  static int result = 0;
  int error;

  if (initialized) {
    return result;
  }

  initialized = 1;

  error = atexit(sdlewExit);
  if (error) {
    result = SDLEW_ERROR_ATEXIT_FAILED;
    return result;
  }

  /* Load library. */
  lib = dynamic_library_open(path);

  if (lib == NULL) {
    result = SDLEW_ERROR_OPEN_FAILED;
    return result;
  }

#ifndef HAVE_FREE
  SDL_LIBRARY_FIND(SDL_free);
#endif
#ifndef HAVE_PUTENV
  SDL_LIBRARY_FIND(SDL_putenv);
#endif
#ifndef HAVE_QSORT
  SDL_LIBRARY_FIND(SDL_qsort);
#endif
#ifndef HAVE_MEMCMP
  SDL_LIBRARY_FIND(SDL_memcmp);
#endif
#ifndef HAVE_STRLEN
  SDL_LIBRARY_FIND(SDL_strlen);
#endif
#ifndef HAVE_STRLCPY
  SDL_LIBRARY_FIND(SDL_strlcpy);
#endif
#ifndef HAVE_STRLCAT
  SDL_LIBRARY_FIND(SDL_strlcat);
#endif
#ifndef HAVE_STRTOL
  SDL_LIBRARY_FIND(SDL_strtol);
#endif
#ifndef HAVE_STRTOLL
  SDL_LIBRARY_FIND(SDL_strtoll);
#endif
#ifndef HAVE_STRTOULL
  SDL_LIBRARY_FIND(SDL_strtoull);
#endif
#ifndef HAVE_STRTOD
  SDL_LIBRARY_FIND(SDL_strtod);
#endif
#ifndef HAVE_STRCMP
  SDL_LIBRARY_FIND(SDL_strcmp);
#endif
#ifndef HAVE_STRNCMP
  SDL_LIBRARY_FIND(SDL_strncmp);
#endif
#ifndef HAVE_STRCASECMP
  SDL_LIBRARY_FIND(SDL_strcasecmp);
#endif
#ifndef HAVE_STRNCASECMP
  SDL_LIBRARY_FIND(SDL_strncasecmp);
#endif
#ifndef HAVE_SSCANF
  SDL_LIBRARY_FIND(SDL_sscanf);
#endif
#ifndef HAVE_SNPRINTF
  SDL_LIBRARY_FIND(SDL_snprintf);
#endif
#ifndef HAVE_VSNPRINTF
  SDL_LIBRARY_FIND(SDL_vsnprintf);
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
  SDL_LIBRARY_FIND(SDL_iconv_open);
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
  SDL_LIBRARY_FIND(SDL_iconv_close);
#endif
  SDL_LIBRARY_FIND(SDL_iconv);
  SDL_LIBRARY_FIND(SDL_UnloadObject);
  SDL_LIBRARY_FIND(SDL_mutexP);
  SDL_LIBRARY_FIND(SDL_mutexV);
  SDL_LIBRARY_FIND(SDL_DestroyMutex);
  SDL_LIBRARY_FIND(SDL_DestroySemaphore);
  SDL_LIBRARY_FIND(SDL_SemWait);
  SDL_LIBRARY_FIND(SDL_SemTryWait);
  SDL_LIBRARY_FIND(SDL_SemWaitTimeout);
  SDL_LIBRARY_FIND(SDL_SemPost);
  SDL_LIBRARY_FIND(SDL_SemValue);
  SDL_LIBRARY_FIND(SDL_DestroyCond);
  SDL_LIBRARY_FIND(SDL_CondSignal);
  SDL_LIBRARY_FIND(SDL_CondBroadcast);
  SDL_LIBRARY_FIND(SDL_CondWait);
  SDL_LIBRARY_FIND(SDL_CondWaitTimeout);
  SDL_LIBRARY_FIND(SDL_PumpEvents);
  SDL_LIBRARY_FIND(SDL_PeepEvents);
  SDL_LIBRARY_FIND(SDL_PollEvent);
  SDL_LIBRARY_FIND(SDL_WaitEvent);
  SDL_LIBRARY_FIND(SDL_PushEvent);
  SDL_LIBRARY_FIND(SDL_SetEventFilter);
  SDL_LIBRARY_FIND(SDL_GetEventFilter);
  SDL_LIBRARY_FIND(SDL_EventState);
  SDL_LIBRARY_FIND(SDL_GetAppState);
  SDL_LIBRARY_FIND(SDL_GetMouseState);
  SDL_LIBRARY_FIND(SDL_GetRelativeMouseState);
  SDL_LIBRARY_FIND(SDL_WarpMouse);
  SDL_LIBRARY_FIND(SDL_SetCursor);
  SDL_LIBRARY_FIND(SDL_FreeCursor);
  SDL_LIBRARY_FIND(SDL_ShowCursor);
  SDL_LIBRARY_FIND(SDL_ThreadID);
  SDL_LIBRARY_FIND(SDL_GetThreadID);
  SDL_LIBRARY_FIND(SDL_WaitThread);
  SDL_LIBRARY_FIND(SDL_KillThread);
  SDL_LIBRARY_FIND(SDL_EnableUNICODE);
  SDL_LIBRARY_FIND(SDL_EnableKeyRepeat);
  SDL_LIBRARY_FIND(SDL_GetKeyRepeat);
  SDL_LIBRARY_FIND(SDL_GetModState);
  SDL_LIBRARY_FIND(SDL_SetModState);
  SDL_LIBRARY_FIND(SDL_AudioInit);
  SDL_LIBRARY_FIND(SDL_AudioQuit);
  SDL_LIBRARY_FIND(SDL_OpenAudio);
  SDL_LIBRARY_FIND(SDL_GetAudioStatus);
  SDL_LIBRARY_FIND(SDL_PauseAudio);
  SDL_LIBRARY_FIND(SDL_FreeWAV);
  SDL_LIBRARY_FIND(SDL_BuildAudioCVT);
  SDL_LIBRARY_FIND(SDL_ConvertAudio);
  SDL_LIBRARY_FIND(SDL_MixAudio);
  SDL_LIBRARY_FIND(SDL_LockAudio);
  SDL_LIBRARY_FIND(SDL_UnlockAudio);
  SDL_LIBRARY_FIND(SDL_CloseAudio);
  SDL_LIBRARY_FIND(SDL_VideoInit);
  SDL_LIBRARY_FIND(SDL_VideoQuit);
  SDL_LIBRARY_FIND(SDL_VideoModeOK);
  SDL_LIBRARY_FIND(SDL_UpdateRects);
  SDL_LIBRARY_FIND(SDL_UpdateRect);
  SDL_LIBRARY_FIND(SDL_Flip);
  SDL_LIBRARY_FIND(SDL_SetGamma);
  SDL_LIBRARY_FIND(SDL_SetGammaRamp);
  SDL_LIBRARY_FIND(SDL_GetGammaRamp);
  SDL_LIBRARY_FIND(SDL_SetColors);
  SDL_LIBRARY_FIND(SDL_SetPalette);
  SDL_LIBRARY_FIND(SDL_MapRGB);
  SDL_LIBRARY_FIND(SDL_MapRGBA);
  SDL_LIBRARY_FIND(SDL_GetRGB);
  SDL_LIBRARY_FIND(SDL_GetRGBA);
  SDL_LIBRARY_FIND(SDL_FreeSurface);
  SDL_LIBRARY_FIND(SDL_LockSurface);
  SDL_LIBRARY_FIND(SDL_UnlockSurface);
  SDL_LIBRARY_FIND(SDL_SaveBMP_RW);
  SDL_LIBRARY_FIND(SDL_SetColorKey);
  SDL_LIBRARY_FIND(SDL_SetAlpha);
  SDL_LIBRARY_FIND(SDL_SetClipRect);
  SDL_LIBRARY_FIND(SDL_GetClipRect);
  SDL_LIBRARY_FIND(SDL_UpperBlit);
  SDL_LIBRARY_FIND(SDL_LowerBlit);
  SDL_LIBRARY_FIND(SDL_FillRect);
  SDL_LIBRARY_FIND(SDL_LockYUVOverlay);
  SDL_LIBRARY_FIND(SDL_UnlockYUVOverlay);
  SDL_LIBRARY_FIND(SDL_DisplayYUVOverlay);
  SDL_LIBRARY_FIND(SDL_FreeYUVOverlay);
  SDL_LIBRARY_FIND(SDL_GL_LoadLibrary);
  SDL_LIBRARY_FIND(SDL_GL_SetAttribute);
  SDL_LIBRARY_FIND(SDL_GL_GetAttribute);
  SDL_LIBRARY_FIND(SDL_GL_SwapBuffers);
  SDL_LIBRARY_FIND(SDL_GL_UpdateRects);
  SDL_LIBRARY_FIND(SDL_GL_Lock);
  SDL_LIBRARY_FIND(SDL_GL_Unlock);
  SDL_LIBRARY_FIND(SDL_WM_SetCaption);
  SDL_LIBRARY_FIND(SDL_WM_GetCaption);
  SDL_LIBRARY_FIND(SDL_WM_SetIcon);
  SDL_LIBRARY_FIND(SDL_WM_IconifyWindow);
  SDL_LIBRARY_FIND(SDL_WM_ToggleFullScreen);
  SDL_LIBRARY_FIND(SDL_WM_GrabInput);
  SDL_LIBRARY_FIND(SDL_SoftStretch);
  SDL_LIBRARY_FIND(SDL_FreeRW);
  SDL_LIBRARY_FIND(SDL_ReadLE16);
  SDL_LIBRARY_FIND(SDL_ReadBE16);
  SDL_LIBRARY_FIND(SDL_ReadLE32);
  SDL_LIBRARY_FIND(SDL_ReadBE32);
  SDL_LIBRARY_FIND(SDL_ReadLE64);
  SDL_LIBRARY_FIND(SDL_ReadBE64);
  SDL_LIBRARY_FIND(SDL_WriteLE16);
  SDL_LIBRARY_FIND(SDL_WriteBE16);
  SDL_LIBRARY_FIND(SDL_WriteLE32);
  SDL_LIBRARY_FIND(SDL_WriteBE32);
  SDL_LIBRARY_FIND(SDL_WriteLE64);
  SDL_LIBRARY_FIND(SDL_WriteBE64);
  SDL_LIBRARY_FIND(SDL_Init);
  SDL_LIBRARY_FIND(SDL_InitSubSystem);
  SDL_LIBRARY_FIND(SDL_QuitSubSystem);
  SDL_LIBRARY_FIND(SDL_WasInit);
  SDL_LIBRARY_FIND(SDL_Quit);
  SDL_LIBRARY_FIND(SDL_GetTicks);
  SDL_LIBRARY_FIND(SDL_Delay);
  SDL_LIBRARY_FIND(SDL_SetTimer);
  SDL_LIBRARY_FIND(SDL_AddTimer);
  SDL_LIBRARY_FIND(SDL_RemoveTimer);
  SDL_LIBRARY_FIND(SDL_NumJoysticks);
  SDL_LIBRARY_FIND(SDL_JoystickOpened);
  SDL_LIBRARY_FIND(SDL_JoystickIndex);
  SDL_LIBRARY_FIND(SDL_JoystickNumAxes);
  SDL_LIBRARY_FIND(SDL_JoystickNumBalls);
  SDL_LIBRARY_FIND(SDL_JoystickNumHats);
  SDL_LIBRARY_FIND(SDL_JoystickNumButtons);
  SDL_LIBRARY_FIND(SDL_JoystickUpdate);
  SDL_LIBRARY_FIND(SDL_JoystickEventState);
  SDL_LIBRARY_FIND(SDL_JoystickGetAxis);
  SDL_LIBRARY_FIND(SDL_JoystickGetHat);
  SDL_LIBRARY_FIND(SDL_JoystickGetBall);
  SDL_LIBRARY_FIND(SDL_JoystickGetButton);
  SDL_LIBRARY_FIND(SDL_JoystickClose);
  SDL_LIBRARY_FIND(SDL_CDNumDrives);
  SDL_LIBRARY_FIND(SDL_CDStatus);
  SDL_LIBRARY_FIND(SDL_CDPlayTracks);
  SDL_LIBRARY_FIND(SDL_CDPlay);
  SDL_LIBRARY_FIND(SDL_CDPause);
  SDL_LIBRARY_FIND(SDL_CDResume);
  SDL_LIBRARY_FIND(SDL_CDStop);
  SDL_LIBRARY_FIND(SDL_CDEject);
  SDL_LIBRARY_FIND(SDL_CDClose);
  SDL_LIBRARY_FIND(SDL_HasRDTSC);
  SDL_LIBRARY_FIND(SDL_HasMMX);
  SDL_LIBRARY_FIND(SDL_HasMMXExt);
  SDL_LIBRARY_FIND(SDL_Has3DNow);
  SDL_LIBRARY_FIND(SDL_Has3DNowExt);
  SDL_LIBRARY_FIND(SDL_HasSSE);
  SDL_LIBRARY_FIND(SDL_HasSSE2);
  SDL_LIBRARY_FIND(SDL_HasAltiVec);
  SDL_LIBRARY_FIND(SDL_SetError);
  SDL_LIBRARY_FIND(SDL_ClearError);
  SDL_LIBRARY_FIND(SDL_Error);
  SDL_LIBRARY_FIND(SDL_GetWMInfo);

  result = SDLEW_SUCCESS;
  return result;
}
