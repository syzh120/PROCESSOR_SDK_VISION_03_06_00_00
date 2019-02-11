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

C++ operator delete();

*/


#include "basics.h"
#include "runtime.h"

#if ABI_CHANGES_FOR_ARRAY_NEW_AND_DELETE

void operator delete[](void				*ptr,
                       const STD_NAMESPACE::nothrow_t&	nothrow_arg)
THROW_NOTHING()
/*
Nothrow version of array operator delete.  Just call the normal nothrow
operator delete.
*/
{
  operator delete(ptr, nothrow_arg);
}  /* operator delete[] */

#endif /* ABI_CHANGES_FOR_ARRAY_NEW_AND_DELETE */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/

