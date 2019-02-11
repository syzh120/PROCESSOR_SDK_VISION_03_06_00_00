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

C++ default new handler.

*/

#include "basics.h"
#include "runtime.h"

extern void __default_new_handler(void)
/*
The default new handler routine that is called when operator new cannot
allocate memory.  When exceptions are enabled, this routine simply throws
a bad_alloc exception.  When exceptions are not enabled, we simply return
to the caller, which detects that the default new handler is being used
and returns a NULL pointer to the caller.
*/
{
#if EXCEPTION_HANDLING
  throw STD_NAMESPACE::bad_alloc();
#else /* !EXCEPTION_HANDLING */
  return;
#endif /* EXCEPTION_HANDLING */
}  /* __default_new_handler */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/



