/* _Dtest function -- IEEE 754 version */
#include "xmath.h"
_STD_BEGIN

short _Dtest(double *px)
	{	/* categorize *px */
	unsigned short *ps = (unsigned short *)(char *)px;

	if ((ps[_D0] & _DMASK) == _DMAX << _DOFF)
		return ((short)((ps[_D0] & _DFRAC) != 0 || ps[_D1] != 0
#if !defined(_32_BIT_DOUBLE)
                                || ps[_D2] != 0 || ps[_D3] != 0 
#endif
                                ? _NANCODE : _INFCODE));
	else if ((ps[_D0] & ~_DSIGN) != 0 || ps[_D1] != 0
#if !defined(_32_BIT_DOUBLE)
                 || ps[_D2] != 0 || ps[_D3] != 0
#endif /* defined(_32_BIT_DOUBLE) */
            )
		return (_FINITE);
	else
		return (0);
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
