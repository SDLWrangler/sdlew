/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2012 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifndef _SDL_mutex_h
#define _SDL_mutex_h

/** @file SDL_mutex.h
 *  Functions to provide thread synchronization primitives
 *
 *  @note These are independent of the other SDL routines.
 */

#include "SDL_stdinc.h"
#include "SDL_error.h"

#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/** Synchronization functions which can time out return this value
 *  if they time out.
 */
#define SDL_MUTEX_TIMEDOUT	1

/** This is the timeout value which corresponds to never time out */
#define SDL_MUTEX_MAXWAIT	(~(Uint32)0)


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/** @name Mutex functions                                        */ /*@{*/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** The SDL mutex structure, defined in SDL_mutex.c */
struct SDL_mutex;
typedef struct SDL_mutex SDL_mutex;

/** Create a mutex, initialized unlocked */
typedef SDL_mutex * SDLCALL tSDL_CreateMutex(void);

#define SDL_LockMutex(m)	SDL_mutexP(m)
/** Lock the mutex
 *  @return 0, or -1 on error
 */
typedef int SDLCALL tSDL_mutexP(SDL_mutex *mutex);

#define SDL_UnlockMutex(m)	SDL_mutexV(m)
/** Unlock the mutex
 *  @return 0, or -1 on error
 *
 *  It is an error to unlock a mutex that has not been locked by
 *  the current thread, and doing so results in undefined behavior.
 */
typedef int SDLCALL tSDL_mutexV(SDL_mutex *mutex);

/** Destroy a mutex */
typedef void SDLCALL tSDL_DestroyMutex(SDL_mutex *mutex);

/*@}*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/** @name Semaphore functions                                    */ /*@{*/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/** The SDL semaphore structure, defined in SDL_sem.c */
struct SDL_semaphore;
typedef struct SDL_semaphore SDL_sem;

/** Create a semaphore, initialized with value, returns NULL on failure. */
typedef SDL_sem * SDLCALL tSDL_CreateSemaphore(Uint32 initial_value);

/** Destroy a semaphore */
typedef void SDLCALL tSDL_DestroySemaphore(SDL_sem *sem);

/**
 * This function suspends the calling thread until the semaphore pointed 
 * to by sem has a positive count. It then atomically decreases the semaphore
 * count.
 */
typedef int SDLCALL tSDL_SemWait(SDL_sem *sem);

/** Non-blocking variant of SDL_SemWait().
 *  @return 0 if the wait succeeds,
 *  SDL_MUTEX_TIMEDOUT if the wait would block, and -1 on error.
 */
typedef int SDLCALL tSDL_SemTryWait(SDL_sem *sem);

/** Variant of SDL_SemWait() with a timeout in milliseconds, returns 0 if
 *  the wait succeeds, SDL_MUTEX_TIMEDOUT if the wait does not succeed in
 *  the allotted time, and -1 on error.
 *
 *  On some platforms this function is implemented by looping with a delay
 *  of 1 ms, and so should be avoided if possible.
 */
typedef int SDLCALL tSDL_SemWaitTimeout(SDL_sem *sem, Uint32 ms);

/** Atomically increases the semaphore's count (not blocking).
 *  @return 0, or -1 on error.
 */
typedef int SDLCALL tSDL_SemPost(SDL_sem *sem);

/** Returns the current count of the semaphore */
typedef Uint32 SDLCALL tSDL_SemValue(SDL_sem *sem);

/*@}*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/** @name Condition_variable_functions                           */ /*@{*/
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*@{*/
/** The SDL condition variable structure, defined in SDL_cond.c */
struct SDL_cond;
typedef struct SDL_cond SDL_cond;
/*@}*/

/** Create a condition variable */
typedef SDL_cond * SDLCALL tSDL_CreateCond(void);

/** Destroy a condition variable */
typedef void SDLCALL tSDL_DestroyCond(SDL_cond *cond);

/** Restart one of the threads that are waiting on the condition variable,
 *  @return 0 or -1 on error.
 */
typedef int SDLCALL tSDL_CondSignal(SDL_cond *cond);

/** Restart all threads that are waiting on the condition variable,
 *  @return 0 or -1 on error.
 */
typedef int SDLCALL tSDL_CondBroadcast(SDL_cond *cond);

/** Wait on the condition variable, unlocking the provided mutex.
 *  The mutex must be locked before entering this function!
 *  The mutex is re-locked once the condition variable is signaled.
 *  @return 0 when it is signaled, or -1 on error.
 */
typedef int SDLCALL tSDL_CondWait(SDL_cond *cond, SDL_mutex *mut);

/** Waits for at most 'ms' milliseconds, and returns 0 if the condition
 *  variable is signaled, SDL_MUTEX_TIMEDOUT if the condition is not
 *  signaled in the allotted time, and -1 on error.
 *  On some platforms this function is implemented by looping with a delay
 *  of 1 ms, and so should be avoided if possible.
 */
typedef int SDLCALL tSDL_CondWaitTimeout(SDL_cond *cond, SDL_mutex *mutex, Uint32 ms);

/*@}*/

extern tSDL_CreateMutex *SDL_CreateMutex;
extern tSDL_mutexP *SDL_mutexP;
extern tSDL_mutexV *SDL_mutexV;
extern tSDL_DestroyMutex *SDL_DestroyMutex;
extern tSDL_CreateSemaphore *SDL_CreateSemaphore;
extern tSDL_DestroySemaphore *SDL_DestroySemaphore;
extern tSDL_SemWait *SDL_SemWait;
extern tSDL_SemTryWait *SDL_SemTryWait;
extern tSDL_SemWaitTimeout *SDL_SemWaitTimeout;
extern tSDL_SemPost *SDL_SemPost;
extern tSDL_SemValue *SDL_SemValue;
extern tSDL_CreateCond *SDL_CreateCond;
extern tSDL_DestroyCond *SDL_DestroyCond;
extern tSDL_CondSignal *SDL_CondSignal;
extern tSDL_CondBroadcast *SDL_CondBroadcast;
extern tSDL_CondWait *SDL_CondWait;
extern tSDL_CondWaitTimeout *SDL_CondWaitTimeout;

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif /* _SDL_mutex_h */

