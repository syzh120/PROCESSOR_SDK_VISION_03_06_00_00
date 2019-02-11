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

error.c - runtime error handling.

*/

#include "basics.h"
#include "runtime.h"
#pragma hdrstop

#if DISPLAY_ABORT_DESCRIPTION

static char *error_text(an_error_code	err_code)
/*
Return the string associated with the specified error code.
*/
{
  char	*s = NULL;

  switch (err_code) {
    case ec_abort_header:
      s = "C++ runtime abort";
      break;
    case ec_terminate_called:
      s = "terminate() called by the exception handling mechanism";
      break;
    case ec_terminate_returned:
      s = "returned from a user-defined terminate() routine";
      break;
    case ec_already_marked_for_destruction:
      s =
         "internal error: static object marked for destruction more than once";
      break;
    case ec_main_called_more_than_once:
      s = "main() called more than once";
      break;
    case ec_pure_virtual_called:
      s = "a pure virtual function was called";
      break;
    case ec_bad_cast:
      s = "invalid dynamic cast";
      break;
    case ec_bad_typeid:
      s = "invalid typeid operation";
      break;
    case ec_array_not_from_vec_new:
      s = "freeing array not allocated by an array new operation";
      break;
    default:
      unexpected_condition();
      break;
  }  /* switch */
  return s;
}  /* error_text */


static void display_abort_message(an_error_code	err_code)
/*
Display the reason that the runtime is aborting execution.
*/
{
  fprintf(stderr, "%s: %s\n", error_text(ec_abort_header),
          error_text(err_code));
}  /* display_abort_message */

#endif /* DISPLAY_ABORT_DESCRIPTION */

#if !DISPLAY_ABORT_DESCRIPTION
/*ARGSUSED*/ /* err_code is only used when displaying abort descriptions. */
#endif /* !DISPLAY_ABORT_DESCRIPTION */
EXTERN_C void __abort_execution(an_error_code	err_code)
/*
*/
{
#if DISPLAY_ABORT_DESCRIPTION
  /* Display the reason for the abort. */
  display_abort_message(err_code);
#endif /* DISPLAY_ABORT_DESCRIPTION */
  abort();
}  /* abort_execution */


/******************************************************************************
*                                                             \  ___  /       *
*                                                               /   \         *
* Edison Design Group C++  Runtime                           - | \^/ | -      *
* Copyright 1993-2004 Edison Design Group, Inc.                 \   /         *
* All rights reserved.  Consult your license regarding        /  | |  \       *
* permissions and restrictions.                                  [_]          *
*                                                                             *
******************************************************************************/
