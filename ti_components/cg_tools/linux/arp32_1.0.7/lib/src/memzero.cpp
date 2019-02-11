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

Routine to clear a block of memory.  Used to initialize arrays that
do not have constructors.

*/

#include "basics.h"
#include "runtime.h"
#pragma hdrstop
#include <string.h>

#if __EDG_BSD
/*
Declare the bzero routine because some header files on BSD systems don't
provide a declaration.  Also, the minimal headers provided in the
release include directory don't declare bzero.
*/
EXTERN_C void bzero(void*, int);
#endif /* __EDG_BSD */

EXTERN_C void __memzero(void    *buffer,
                        size_t	size)
/*
Initialize a block of memory.
*/
{
#if __EDG_BSD
  bzero(buffer, size);
#else /* !__EDG_BSD */
  memset(buffer, 0, size);
#endif /* __EDG_BSD */
}  /* __memzero */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/

