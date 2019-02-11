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

C++ operator delete(size_t, void*);

*/

#include "basics.h"
#include "runtime.h"

#if ABI_CHANGES_FOR_PLACEMENT_DELETE

void operator delete(void *, void *) THROW_NOTHING()
/*
Placement operator delete -- does nothing.
*/
{
}  /* operator delete (size_t, void*) */

#endif /* ABI_CHANGES_FOR_PLACEMENT_DELETE */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/
