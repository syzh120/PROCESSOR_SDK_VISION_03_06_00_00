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

C++ operator new[](size_t, void*) (placement array new).

*/


#include "basics.h"
#include "runtime.h"

#if ABI_CHANGES_FOR_ARRAY_NEW_AND_DELETE && DEFINE_PLACEMENT_NEW_ROUTINES

void *operator new[](size_t, void* ptr) THROW_NOTHING()
/*
Placement array operator new.
*/
{
  return ptr;
}  /* operator new[](size_t, void*) */

#endif /* ABI_CHANGES_FOR_ARRAY_NEW_AND_DELETE &&
          DEFINE_PLACEMENT_NEW_ROUTINES*/

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/


