/* raise function */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
_STD_BEGIN

 #if _USE_EXISTING_SYSTEM_NAMES
  #define _Getpid getpid
  #define _Kill kill
 #endif /* _USE_EXISTING_SYSTEM_NAMES */

#if _POSIX_C_LIB
_EXTERN_C
int _Getpid(void);
int _Kill(int, int);
_END_EXTERN_C

int (raise)(int sig)
	{	/* raise a signal */
	return (_Kill(_Getpid(), sig));
	}

 #else /* _LIB version */
int (raise)(int sig)
	{	/* raise a signal */
	_Sigfun *const s = signal(sig, SIG_IGN);

	if (s == SIG_ERR)
		return (-1);	/* bad signal */
	else if (s == SIG_IGN)
		;
	else if (s != SIG_DFL)
		{	/* revert and call handler */
		signal(sig, SIG_DFL);
		(*s)(sig);
		}
	else
		{	/* default handling */
		}
	return (0);
	}
 #endif /* _LIB version */

_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
