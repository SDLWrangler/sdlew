/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDL_joystick.h
 *
 *  Include file for SDL joystick event handling
 *
 * The term "device_index" identifies currently plugged in joystick devices between 0 and SDL_NumJoysticks, with the exact joystick
 *   behind a device_index changing as joysticks are plugged and unplugged.
 *
 * The term "instance_id" is the current instantiation of a joystick device in the system, if the joystick is removed and then re-inserted
 *   then it will get a new instance_id, instance_id's are monotonically increasing identifiers of a joystick plugged in.
 *
 * The term JoystickGUID is a stable 128-bit identifier for a joystick device that does not change over time, it identifies class of
 *   the device (a X360 wired controller for example). This identifier is platform dependent.
 *
 *
 */

#ifndef _SDL_joystick_h
#define _SDL_joystick_h

#include "SDL_stdinc.h"
#include "SDL_error.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/**
 *  \file SDL_joystick.h
 *
 *  In order to use these functions, SDL_Init() must have been called
 *  with the ::SDL_INIT_JOYSTICK flag.  This causes SDL to scan the system
 *  for joysticks, and load appropriate drivers.
 *
 *  If you would like to receive joystick updates while the application
 *  is in the background, you should set the following hint before calling
 *  SDL_Init(): SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS
 */

/* The joystick structure used to identify an SDL joystick */
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;

/* A structure that encodes the stable unique id for a joystick device */
typedef struct {
    Uint8 data[16];
} SDL_JoystickGUID;

typedef Sint32 SDL_JoystickID;


/* Function prototypes */
/**
 *  Count the number of joysticks attached to the system right now
 */
typedef int SDLCALL tSDL_NumJoysticks(void);

/**
 *  Get the implementation dependent name of a joystick.
 *  This can be called before any joysticks are opened.
 *  If no name can be found, this function returns NULL.
 */
typedef const char * SDLCALL tSDL_JoystickNameForIndex(int device_index);

/**
 *  Open a joystick for use.
 *  The index passed as an argument refers tothe N'th joystick on the system.
 *  This index is the value which will identify this joystick in future joystick
 *  events.
 *
 *  \return A joystick identifier, or NULL if an error occurred.
 */
typedef SDL_Joystick * SDLCALL tSDL_JoystickOpen(int device_index);

/**
 *  Return the name for this currently opened joystick.
 *  If no name can be found, this function returns NULL.
 */
typedef const char * SDLCALL tSDL_JoystickName(SDL_Joystick * joystick);

/**
 *  Return the GUID for the joystick at this index
 */
typedef SDL_JoystickGUID SDLCALL tSDL_JoystickGetDeviceGUID(int device_index);

/**
 *  Return the GUID for this opened joystick
 */
typedef SDL_JoystickGUID SDLCALL tSDL_JoystickGetGUID(SDL_Joystick * joystick);

/**
 *  Return a string representation for this guid. pszGUID must point to at least 33 bytes
 *  (32 for the string plus a NULL terminator).
 */
extern DECLSPEC void SDL_JoystickGetGUIDString(SDL_JoystickGUID guid, char *pszGUID, int cbGUID);

/**
 *  convert a string into a joystick formatted guid
 */
typedef SDL_JoystickGUID SDLCALL tSDL_JoystickGetGUIDFromString(const char *pchGUID);

/**
 *  Returns SDL_TRUE if the joystick has been opened and currently connected, or SDL_FALSE if it has not.
 */
typedef SDL_bool SDLCALL tSDL_JoystickGetAttached(SDL_Joystick * joystick);

/**
 *  Get the instance ID of an opened joystick or -1 if the joystick is invalid.
 */
typedef SDL_JoystickID SDLCALL tSDL_JoystickInstanceID(SDL_Joystick * joystick);

/**
 *  Get the number of general axis controls on a joystick.
 */
typedef int SDLCALL tSDL_JoystickNumAxes(SDL_Joystick * joystick);

/**
 *  Get the number of trackballs on a joystick.
 *
 *  Joystick trackballs have only relative motion events associated
 *  with them and their state cannot be polled.
 */
typedef int SDLCALL tSDL_JoystickNumBalls(SDL_Joystick * joystick);

/**
 *  Get the number of POV hats on a joystick.
 */
typedef int SDLCALL tSDL_JoystickNumHats(SDL_Joystick * joystick);

/**
 *  Get the number of buttons on a joystick.
 */
typedef int SDLCALL tSDL_JoystickNumButtons(SDL_Joystick * joystick);

/**
 *  Update the current state of the open joysticks.
 *
 *  This is called automatically by the event loop if any joystick
 *  events are enabled.
 */
typedef void SDLCALL tSDL_JoystickUpdate(void);

/**
 *  Enable/disable joystick event polling.
 *
 *  If joystick events are disabled, you must call SDL_JoystickUpdate()
 *  yourself and check the state of the joystick when you want joystick
 *  information.
 *
 *  The state can be one of ::SDL_QUERY, ::SDL_ENABLE or ::SDL_IGNORE.
 */
typedef int SDLCALL tSDL_JoystickEventState(int state);

/**
 *  Get the current state of an axis control on a joystick.
 *
 *  The state is a value ranging from -32768 to 32767.
 *
 *  The axis indices start at index 0.
 */
typedef Sint16 SDLCALL tSDL_JoystickGetAxis(SDL_Joystick * joystick,
                                                   int axis);

/**
 *  \name Hat positions
 */
/*@{*/
#define SDL_HAT_CENTERED    0x00
#define SDL_HAT_UP      0x01
#define SDL_HAT_RIGHT       0x02
#define SDL_HAT_DOWN        0x04
#define SDL_HAT_LEFT        0x08
#define SDL_HAT_RIGHTUP     (SDL_HAT_RIGHT|SDL_HAT_UP)
#define SDL_HAT_RIGHTDOWN   (SDL_HAT_RIGHT|SDL_HAT_DOWN)
#define SDL_HAT_LEFTUP      (SDL_HAT_LEFT|SDL_HAT_UP)
#define SDL_HAT_LEFTDOWN    (SDL_HAT_LEFT|SDL_HAT_DOWN)
/*@}*/

/**
 *  Get the current state of a POV hat on a joystick.
 *
 *  The hat indices start at index 0.
 *
 *  \return The return value is one of the following positions:
 *           - ::SDL_HAT_CENTERED
 *           - ::SDL_HAT_UP
 *           - ::SDL_HAT_RIGHT
 *           - ::SDL_HAT_DOWN
 *           - ::SDL_HAT_LEFT
 *           - ::SDL_HAT_RIGHTUP
 *           - ::SDL_HAT_RIGHTDOWN
 *           - ::SDL_HAT_LEFTUP
 *           - ::SDL_HAT_LEFTDOWN
 */
typedef Uint8 SDLCALL tSDL_JoystickGetHat(SDL_Joystick * joystick,
                                                 int hat);

/**
 *  Get the ball axis change since the last poll.
 *
 *  \return 0, or -1 if you passed it invalid parameters.
 *
 *  The ball indices start at index 0.
 */
typedef int SDLCALL tSDL_JoystickGetBall(SDL_Joystick * joystick,
                                                int ball, int *dx, int *dy);

/**
 *  Get the current state of a button on a joystick.
 *
 *  The button indices start at index 0.
 */
typedef Uint8 SDLCALL tSDL_JoystickGetButton(SDL_Joystick * joystick,
                                                    int button);

/**
 *  Close a joystick previously opened with SDL_JoystickOpen().
 */
typedef void SDLCALL tSDL_JoystickClose(SDL_Joystick * joystick);


extern tSDL_NumJoysticks *SDL_NumJoysticks;
extern tSDL_JoystickNameForIndex *SDL_JoystickNameForIndex;
extern tSDL_JoystickOpen *SDL_JoystickOpen;
extern tSDL_JoystickName *SDL_JoystickName;
extern tSDL_JoystickGetDeviceGUID *SDL_JoystickGetDeviceGUID;
extern tSDL_JoystickGetGUID *SDL_JoystickGetGUID;
extern tSDL_JoystickGetGUIDFromString *SDL_JoystickGetGUIDFromString;
extern tSDL_JoystickGetAttached *SDL_JoystickGetAttached;
extern tSDL_JoystickInstanceID *SDL_JoystickInstanceID;
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

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _SDL_joystick_h */

/* vi: set ts=4 sw=4 expandtab: */
