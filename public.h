/* SPDX-License-Identifier: MPL-1.1 OR GPL-2.0-or-later */

/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is the Netscape Portable Runtime library.
 * 
 * The Initial Developer of the Original Code is Netscape
 * Communications Corporation.  Portions created by Netscape are 
 * Copyright (C) 1994-2000 Netscape Communications Corporation.  All
 * Rights Reserved.
 * 
 * Contributor(s):  Silicon Graphics, Inc.
 * 
 * Portions created by SGI are Copyright (C) 2000-2001 Silicon
 * Graphics, Inc.  All Rights Reserved.
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 or later (the
 * "GPL"), in which case the provisions of the GPL are applicable 
 * instead of those above.  If you wish to allow use of your 
 * version of this file only under the terms of the GPL and not to
 * allow others to use your version of this file under the MPL,
 * indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by
 * the GPL.  If you do not delete the provisions above, a recipient
 * may use your version of this file under either the MPL or the
 * GPL.
 */

#ifndef __ST_THREAD_H__
#define __ST_THREAD_H__

#include <sys/types.h>
#include <time.h>
#include <errno.h>

#define ST_VERSION	    "1.9"
#define ST_VERSION_MAJOR    1
#define ST_VERSION_MINOR    9

#ifdef _WIN32
    #define __thread
#endif

/* Undefine this to remove the context switch callback feature. */
#define ST_SWITCH_CB

#ifndef ETIME
    #define ETIME ETIMEDOUT
#endif

#ifndef ST_UTIME_NO_TIMEOUT
    #define ST_UTIME_NO_TIMEOUT ((st_utime_t) -1LL)
#endif

#ifndef ST_UTIME_NO_WAIT
    #define ST_UTIME_NO_WAIT 0
#endif

// #define ST_EVENTSYS_DEFAULT 0
// #define ST_EVENTSYS_SELECT  1
// #define ST_EVENTSYS_ALT     3

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long long  st_utime_t;
typedef struct _st_thread * st_thread_t;
typedef struct _st_cond *   st_cond_t;
typedef struct _st_mutex *  st_mutex_t;
typedef struct _st_netfd *  st_netfd_t;
#ifdef ST_SWITCH_CB
typedef void (*st_switch_cb_t)(void);
#endif

extern int st_init(void *h);

#ifdef ST_SWITCH_CB
extern st_switch_cb_t st_set_switch_in_cb(st_switch_cb_t cb);
extern st_switch_cb_t st_set_switch_out_cb(st_switch_cb_t cb);
#endif

extern st_thread_t st_thread_self(void);
extern void st_thread_exit(void *retval);
extern int st_thread_join(st_thread_t thread, void **retvalp);
extern void st_thread_interrupt(st_thread_t thread);
extern void st_thread_yield();
extern st_thread_t st_thread_create(void *(*start)(void *arg), void *arg, int joinable, int stack_size);
extern int st_randomize_stacks(int on);
extern int st_set_utime_function(st_utime_t (*func)(void));

extern st_utime_t st_utime(void);
extern st_utime_t st_utime_last_clock(void);
extern int st_timecache_set(int on);
extern time_t st_time(void);
extern int st_usleep(st_utime_t usecs);
extern int st_sleep(int secs);

extern st_cond_t st_cond_new(void);
extern int st_cond_destroy(st_cond_t cvar);
extern int st_cond_timedwait(st_cond_t cvar, st_utime_t timeout);
extern int st_cond_wait(st_cond_t cvar);
extern int st_cond_signal(st_cond_t cvar);
extern int st_cond_broadcast(st_cond_t cvar);

extern st_mutex_t st_mutex_new(void);
extern int st_mutex_destroy(st_mutex_t lock);
extern int st_mutex_lock(st_mutex_t lock);
extern int st_mutex_unlock(st_mutex_t lock);
extern int st_mutex_trylock(st_mutex_t lock);

extern int st_key_create(int *keyp, void (*destructor)(void *));
extern int st_key_getlimit(void);
extern int st_thread_setspecific(int key, void *value);
extern void *st_thread_getspecific(int key);
extern int st_thread_setspecific2(st_thread_t thread, int key, void *value);

#ifdef DEBUG
extern void _st_show_thread_stack(st_thread_t thread, const char *messg);
extern void _st_iterate_threads(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* !__ST_THREAD_H__ */

