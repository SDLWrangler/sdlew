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

#ifndef __SDL_EW_H__
#define __SDL_EW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "SDL/SDL.h"
#include "SDL/SDL_syswm.h"

extern tSDL_GetAppState *SDL_GetAppState;
extern tSDL_AudioInit *SDL_AudioInit;
extern tSDL_AudioQuit *SDL_AudioQuit;
extern tSDL_OpenAudio *SDL_OpenAudio;
extern tSDL_GetAudioStatus *SDL_GetAudioStatus;
extern tSDL_PauseAudio *SDL_PauseAudio;
extern tSDL_FreeWAV *SDL_FreeWAV;
extern tSDL_BuildAudioCVT *SDL_BuildAudioCVT;
extern tSDL_ConvertAudio *SDL_ConvertAudio;
extern tSDL_MixAudio *SDL_MixAudio;
extern tSDL_LockAudio *SDL_LockAudio;
extern tSDL_UnlockAudio *SDL_UnlockAudio;
extern tSDL_CloseAudio *SDL_CloseAudio;
extern tSDL_CDNumDrives *SDL_CDNumDrives;
extern tSDL_CDStatus *SDL_CDStatus;
extern tSDL_CDPlayTracks *SDL_CDPlayTracks;
extern tSDL_CDPlay *SDL_CDPlay;
extern tSDL_CDPause *SDL_CDPause;
extern tSDL_CDResume *SDL_CDResume;
extern tSDL_CDStop *SDL_CDStop;
extern tSDL_CDEject *SDL_CDEject;
extern tSDL_CDClose *SDL_CDClose;
extern tSDL_HasRDTSC *SDL_HasRDTSC;
extern tSDL_HasMMX *SDL_HasMMX;
extern tSDL_HasMMXExt *SDL_HasMMXExt;
extern tSDL_Has3DNow *SDL_Has3DNow;
extern tSDL_Has3DNowExt *SDL_Has3DNowExt;
extern tSDL_HasSSE *SDL_HasSSE;
extern tSDL_HasSSE2 *SDL_HasSSE2;
extern tSDL_HasAltiVec *SDL_HasAltiVec;
extern tSDL_SetError *SDL_SetError;
extern tSDL_ClearError *SDL_ClearError;
extern tSDL_Error *SDL_Error;
extern tSDL_PumpEvents *SDL_PumpEvents;
extern tSDL_PeepEvents *SDL_PeepEvents;
extern tSDL_PollEvent *SDL_PollEvent;
extern tSDL_WaitEvent *SDL_WaitEvent;
extern tSDL_PushEvent *SDL_PushEvent;
extern tSDL_SetEventFilter *SDL_SetEventFilter;
extern tSDL_GetEventFilter *SDL_GetEventFilter;
extern tSDL_EventState *SDL_EventState;
extern tSDL_Init *SDL_Init;
extern tSDL_InitSubSystem *SDL_InitSubSystem;
extern tSDL_QuitSubSystem *SDL_QuitSubSystem;
extern tSDL_WasInit *SDL_WasInit;
extern tSDL_Quit *SDL_Quit;
extern tSDL_NumJoysticks *SDL_NumJoysticks;
extern tSDL_JoystickOpened *SDL_JoystickOpened;
extern tSDL_JoystickIndex *SDL_JoystickIndex;
extern tSDL_JoystickNumAxes *SDL_JoystickNumAxes;
extern tSDL_JoystickNumBalls *SDL_JoystickNumBalls;
extern tSDL_JoystickNumHats *SDL_JoystickNumHats;
extern tSDL_JoystickNumButtons *SDL_JoystickNumButtons;
extern tSDL_JoystickUpdate *SDL_JoystickUpdate;
extern tSDL_JoystickEventState *SDL_JoystickEventState;
extern tSDL_JoystickGetAxis *SDL_JoystickGetAxis;
extern tSDL_JoystickGetHat *SDL_JoystickGetHat;
extern tSDL_JoystickGetBall *SDL_JoystickGetBall;
extern tSDL_JoystickGetButton *SDL_JoystickGetButton;
extern tSDL_JoystickClose *SDL_JoystickClose;
extern tSDL_EnableUNICODE *SDL_EnableUNICODE;
extern tSDL_EnableKeyRepeat *SDL_EnableKeyRepeat;
extern tSDL_GetKeyRepeat *SDL_GetKeyRepeat;
extern tSDL_GetModState *SDL_GetModState;
extern tSDL_SetModState *SDL_SetModState;
extern tSDL_UnloadObject *SDL_UnloadObject;
/* extern tSDL_SetModuleHandle *SDL_SetModuleHandle; */
/* extern tSDL_RegisterApp *SDL_RegisterApp; */
/* extern tSDL_UnregisterApp *SDL_UnregisterApp; */
/* extern tSDL_InitQuickDraw *SDL_InitQuickDraw; */
extern tSDL_GetMouseState *SDL_GetMouseState;
extern tSDL_GetRelativeMouseState *SDL_GetRelativeMouseState;
extern tSDL_WarpMouse *SDL_WarpMouse;
extern tSDL_SetCursor *SDL_SetCursor;
extern tSDL_FreeCursor *SDL_FreeCursor;
extern tSDL_ShowCursor *SDL_ShowCursor;
extern tSDL_mutexP *SDL_mutexP;
extern tSDL_mutexV *SDL_mutexV;
extern tSDL_DestroyMutex *SDL_DestroyMutex;
extern tSDL_DestroySemaphore *SDL_DestroySemaphore;
extern tSDL_SemWait *SDL_SemWait;
extern tSDL_SemTryWait *SDL_SemTryWait;
extern tSDL_SemWaitTimeout *SDL_SemWaitTimeout;
extern tSDL_SemPost *SDL_SemPost;
extern tSDL_SemValue *SDL_SemValue;
extern tSDL_DestroyCond *SDL_DestroyCond;
extern tSDL_CondSignal *SDL_CondSignal;
extern tSDL_CondBroadcast *SDL_CondBroadcast;
extern tSDL_CondWait *SDL_CondWait;
extern tSDL_CondWaitTimeout *SDL_CondWaitTimeout;
extern tSDL_FreeRW *SDL_FreeRW;
extern tSDL_ReadLE16 *SDL_ReadLE16;
extern tSDL_ReadBE16 *SDL_ReadBE16;
extern tSDL_ReadLE32 *SDL_ReadLE32;
extern tSDL_ReadBE32 *SDL_ReadBE32;
extern tSDL_ReadLE64 *SDL_ReadLE64;
extern tSDL_ReadBE64 *SDL_ReadBE64;
extern tSDL_WriteLE16 *SDL_WriteLE16;
extern tSDL_WriteBE16 *SDL_WriteBE16;
extern tSDL_WriteLE32 *SDL_WriteLE32;
extern tSDL_WriteBE32 *SDL_WriteBE32;
extern tSDL_WriteLE64 *SDL_WriteLE64;
extern tSDL_WriteBE64 *SDL_WriteBE64;
#ifndef HAVE_FREE
extern tSDL_free *SDL_free;
#endif
#ifndef HAVE_PUTENV
extern tSDL_putenv *SDL_putenv;
#endif
#ifndef HAVE_QSORT
extern tSDL_qsort *SDL_qsort;
#endif
#ifndef HAVE_MEMCMP
extern tSDL_memcmp *SDL_memcmp;
#endif
#ifndef HAVE_STRLEN
extern tSDL_strlen *SDL_strlen;
#endif
#ifndef HAVE_STRLCPY
extern tSDL_strlcpy *SDL_strlcpy;
#endif
#ifndef HAVE_STRLCAT
extern tSDL_strlcat *SDL_strlcat;
#endif
#ifndef HAVE_STRTOL
extern tSDL_strtol *SDL_strtol;
#endif
#ifndef HAVE_STRTOLL
extern tSDL_strtoll *SDL_strtoll;
#endif
#ifndef HAVE_STRTOULL
extern tSDL_strtoull *SDL_strtoull;
#endif
#ifndef HAVE_STRTOD
extern tSDL_strtod *SDL_strtod;
#endif
#ifndef HAVE_STRCMP
extern tSDL_strcmp *SDL_strcmp;
#endif
#ifndef HAVE_STRNCMP
extern tSDL_strncmp *SDL_strncmp;
#endif
#ifndef HAVE_STRCASECMP
extern tSDL_strcasecmp *SDL_strcasecmp;
#endif
#ifndef HAVE_STRNCASECMP
extern tSDL_strncasecmp *SDL_strncasecmp;
#endif
#ifndef HAVE_SSCANF
extern tSDL_sscanf *SDL_sscanf;
#endif
#ifndef HAVE_SNPRINTF
extern tSDL_snprintf *SDL_snprintf;
#endif
#ifndef HAVE_VSNPRINTF
extern tSDL_vsnprintf *SDL_vsnprintf;
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
extern tSDL_iconv_open *SDL_iconv_open;
#endif
#if !(defined(HAVE_ICONV) && defined(HAVE_ICONV_H))
extern tSDL_iconv_close *SDL_iconv_close;
#endif
extern tSDL_iconv *SDL_iconv;
extern tSDL_GetWMInfo *SDL_GetWMInfo;
extern tSDL_ThreadID *SDL_ThreadID;
extern tSDL_GetThreadID *SDL_GetThreadID;
extern tSDL_WaitThread *SDL_WaitThread;
extern tSDL_KillThread *SDL_KillThread;
extern tSDL_GetTicks *SDL_GetTicks;
extern tSDL_Delay *SDL_Delay;
extern tSDL_SetTimer *SDL_SetTimer;
extern tSDL_AddTimer *SDL_AddTimer;
extern tSDL_RemoveTimer *SDL_RemoveTimer;
extern tSDL_VideoInit *SDL_VideoInit;
extern tSDL_VideoQuit *SDL_VideoQuit;
extern tSDL_VideoModeOK *SDL_VideoModeOK;
extern tSDL_UpdateRects *SDL_UpdateRects;
extern tSDL_UpdateRect *SDL_UpdateRect;
extern tSDL_Flip *SDL_Flip;
extern tSDL_SetGamma *SDL_SetGamma;
extern tSDL_SetGammaRamp *SDL_SetGammaRamp;
extern tSDL_GetGammaRamp *SDL_GetGammaRamp;
extern tSDL_SetColors *SDL_SetColors;
extern tSDL_SetPalette *SDL_SetPalette;
extern tSDL_MapRGB *SDL_MapRGB;
extern tSDL_MapRGBA *SDL_MapRGBA;
extern tSDL_GetRGB *SDL_GetRGB;
extern tSDL_GetRGBA *SDL_GetRGBA;
extern tSDL_FreeSurface *SDL_FreeSurface;
extern tSDL_LockSurface *SDL_LockSurface;
extern tSDL_UnlockSurface *SDL_UnlockSurface;
extern tSDL_SaveBMP_RW *SDL_SaveBMP_RW;
extern tSDL_SetColorKey *SDL_SetColorKey;
extern tSDL_SetAlpha *SDL_SetAlpha;
extern tSDL_SetClipRect *SDL_SetClipRect;
extern tSDL_GetClipRect *SDL_GetClipRect;
extern tSDL_UpperBlit *SDL_UpperBlit;
extern tSDL_LowerBlit *SDL_LowerBlit;
extern tSDL_FillRect *SDL_FillRect;
extern tSDL_LockYUVOverlay *SDL_LockYUVOverlay;
extern tSDL_UnlockYUVOverlay *SDL_UnlockYUVOverlay;
extern tSDL_DisplayYUVOverlay *SDL_DisplayYUVOverlay;
extern tSDL_FreeYUVOverlay *SDL_FreeYUVOverlay;
extern tSDL_GL_LoadLibrary *SDL_GL_LoadLibrary;
extern tSDL_GL_SetAttribute *SDL_GL_SetAttribute;
extern tSDL_GL_GetAttribute *SDL_GL_GetAttribute;
extern tSDL_GL_SwapBuffers *SDL_GL_SwapBuffers;
extern tSDL_GL_UpdateRects *SDL_GL_UpdateRects;
extern tSDL_GL_Lock *SDL_GL_Lock;
extern tSDL_GL_Unlock *SDL_GL_Unlock;
extern tSDL_WM_SetCaption *SDL_WM_SetCaption;
extern tSDL_WM_GetCaption *SDL_WM_GetCaption;
extern tSDL_WM_SetIcon *SDL_WM_SetIcon;
extern tSDL_WM_IconifyWindow *SDL_WM_IconifyWindow;
extern tSDL_WM_ToggleFullScreen *SDL_WM_ToggleFullScreen;
extern tSDL_WM_GrabInput *SDL_WM_GrabInput;
extern tSDL_SoftStretch *SDL_SoftStretch;

enum {
  SDLEW_SUCCESS = 0,
  SDLEW_ERROR_OPEN_FAILED = -1,
  SDLEW_ERROR_ATEXIT_FAILED = -2,
};

int sdlewInit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __SDL_EW_H__ */
