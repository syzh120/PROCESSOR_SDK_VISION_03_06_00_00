// throw -- terminate on thrown exception REPLACEABLE
#include <cstdio>
#include <cstdlib>
#include <exception>
_STD_BEGIN

void _Debug_message(const char *s1, const char *s2)
	{	// report error and die
	_CSTD fflush(0);
	_CSTD fputs(s1, stderr);
	_CSTD fputs(s2 != 0 ? s2 : "unknown", stderr);
	_CSTD fputs("\n", stderr);
	_CSTD abort();
	}
_STD_END

_X_STD_BEGIN


void _Throw(const exception& ex)
	{	// report throw exception and die
	_STD _Debug_message("exception: ", ex.what());
	}

_X_STD_END


/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
