/*****************************************************************************/
/* vars.cpp v1.0.7                                                           */
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

Performs initialization of global variables used by the runtime.

*/

#define EXTERN /* empty */
#define VAR_INITIALIZERS 1

#include "basics.h"
#include "runtime.h"
#include "vec_newdel.h"
/*** START TI ADD ***/
/* We do not need main.h to build TI RTS */
/*** END TI ADD ***/
#include "vec_newdel.h"
#include "eh.h"

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/



