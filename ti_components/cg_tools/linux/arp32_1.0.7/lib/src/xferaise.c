/* _Feraise function */
#include <errno.h>

#if _HAS_C9X || defined(_C99_MATH)
#include <fenv.h>
#include <math.h>

 #else /* _HAS_C9X || _C99_MATH */
#include <ymath.h>
 #endif /* _HAS_C9X || _C99_MATH */

_STD_BEGIN

void (_Feraise)(int except)
	{	/* report floating-point exception */

#if _HAS_C9X || defined(_C99_MATH)
	int errh = math_errhandling;	/* quiet diagnostics */

	if ((errh & MATH_ERREXCEPT) != 0)
		{	/* set hardware bits */
		if ((except & (_FE_OVERFLOW | _FE_UNDERFLOW)) != 0)
			except |= _FE_INEXACT;	/* IEC 60559 */
		feraiseexcept(except);
		}

	if ((errh & MATH_ERRNO) == 0)
		;
	else if ((except & (_FE_DIVBYZERO | _FE_INVALID)) != 0)
		errno = EDOM;
	else if ((except & (_FE_UNDERFLOW | _FE_OVERFLOW)) != 0)
		errno = ERANGE;

#else /* _HAS_C9X || _C99_MATH*/
	if ((except & (_FE_DIVBYZERO | _FE_INVALID)) != 0)
		errno = EDOM;
	else if ((except & (_FE_UNDERFLOW | _FE_OVERFLOW)) != 0)
		errno = ERANGE;
 #endif /* _HAS_C9X || _C99_MATH*/

	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
