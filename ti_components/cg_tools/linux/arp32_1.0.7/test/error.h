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

Declarations relating to error.c - runtime error handling.

*/

#ifndef ERROR_H
#define ERROR_H 1

typedef enum /* an_error_code */ {
  ec_none,
  ec_abort_header,
  ec_terminate_called,
  ec_terminate_returned,
  ec_already_marked_for_destruction,
  ec_main_called_more_than_once,
  ec_pure_virtual_called,
  ec_bad_cast,
  ec_bad_typeid,
  ec_array_not_from_vec_new,
  ec_last
} an_error_code;

EXTERN_C void __abort_execution(an_error_code err_code);

#endif /* ERROR_H */

/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/
