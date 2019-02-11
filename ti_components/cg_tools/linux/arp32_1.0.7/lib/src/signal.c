/* signal function */
#include <signal.h>
#include <yvals.h>
_STD_BEGIN

 #if !_POSIX_C_LIB && !_WIN32_C_LIB || defined(_WIN32_WCE) || defined(__TI_COMPILER_VERSION__)
static _Sigfun *sigtable[_NSIG] = {0};

_Sigfun *(signal)(int sig, _Sigfun *fun)
	{	/* specify handling for a signal */
	_Sigfun *s;

	if (sig <= 0 || _NSIG <= sig || fun == SIG_ERR)
		return (SIG_ERR);	/* bad signal */
	/* add machine-dependent handling here */
	_Locksyslock(_LOCK_MALLOC);
	s = sigtable[sig], sigtable[sig] = fun;
	_Unlocksyslock(_LOCK_MALLOC);
	return (s);
	}
 #endif /* !_POSIX_C_LIB && !_WIN32_C_LIB || _WIN32_WCE */

_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
