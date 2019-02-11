/*****************************************************************************/
/* guard.cpp v1.0.7                                                          */
/* Copyright (c) 1996-2015 Texas Instruments Inc., all rights reserved       */
/*****************************************************************************/
/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/
/*

C++ functions to for one-time initialization guard variables.

*/

#include "basics.h"
#include "runtime.h"

#ifdef __EDG_IA64_ABI

/*
These functions are used by the front end only if
IA64_ABI_USE_GUARD_ACQUIRE_RELEASE is TRUE.
*/

EXTERN_C int ABI_NAMESPACE::__cxa_guard_acquire(an_ia64_guard_ptr guard)
/*
If the guard variable indicates that the guarded variable has already
been initialized, return 0.  Otherwise, return 1.
*/
{
  int  initialize = FALSE;
#ifdef __EDG_IA64_ABI_USE_INT_STATIC_INIT_GUARD
  /* EABI, check least significant bit of guard object == 0 */
  if ( ((*guard) & 0x1) == 0 ) {
#else
  char *first_byte = (char *)guard;
  if (*first_byte == 0) {
#endif
    initialize = TRUE;
  }  /* if */
  return initialize;
}  /* __cxa_guard_acquire */


EXTERN_C void ABI_NAMESPACE::__cxa_guard_release(an_ia64_guard_ptr guard)
/*
Called when the initialization of the guarded object is complete.
*/
{
#ifdef __EDG_IA64_ABI_USE_INT_STATIC_INIT_GUARD
   /* EABI, Set least significant bit of the guard object */
   (*guard) |= 0x1;
#else
  /* Set the guard variable to indicate that the initialization is complete.
     A multi-threaded implementation would then release the lock. */
  char *first_byte = (char *)guard;
  *first_byte = 1;
#endif
}  /* __cxa_guard_release */


EXTERN_C void ABI_NAMESPACE::__cxa_guard_abort(an_ia64_guard_ptr guard)
/*
The initialization of the guarded object has been aborted due to an
exception being thrown.  Reset the guard so that the initialization 
will be tried again.
*/
{
   /* EABI, reset least significant bit */
#ifdef __EDG_IA64_ABI_USE_INT_STATIC_INIT_GUARD
  *guard = ((*guard) >> 1) << 1;
#else
  *(char *)guard = 0;
#endif
}  /* __cxa_guard_abort */

#endif /* ifdef __EDG_IA64_ABI */


/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/
