/* values used by math functions -- IEEE 754 version */
#include "xmath.h"
_STD_BEGIN

		/* macros */
#define NBITS	(48 + _DOFF)

 #if defined(_32_BIT_DOUBLE) && _D0 == 0
  #define INIT(w0)		{w0, 0}
  #define INIT2(w0, w1)	        {w0, w1}

 #elif defined(_32_BIT_DOUBLE)
  #define INIT(w0)		{0, w0}
  #define INIT2(w0, w1)	        {w1, w0}

 #elif _D0 == 0
  #define INIT(w0)		{w0, 0, 0, 0}
  #define INIT2(w0, w1)	        {w0, 0, 0, w1}

 #else /* _D0 == 0 */
        #define INIT(w0)	{0, 0, 0, w0}
        #define INIT2(w0, w1)	{w1, 0, 0, w0}
 #endif /* _D0 == 0 */

		/* static data */
/* extern const */ _Dconst _Denorm = {INIT2(0, 1)};
/* extern const */ _Dconst _Eps = {
	INIT((_DBIAS - NBITS - 1) << _DOFF)};
/* extern const */ _Dconst _Hugeval = {INIT(_DMAX << _DOFF)};
/* extern const */ _Dconst _Inf = {INIT(_DMAX << _DOFF)};
/* extern const */ _Dconst _Nan = {INIT((_DMAX << _DOFF)
	| (1 << (_DOFF - 1)))};
/* extern const */ _Dconst _Snan = {INIT2(_DMAX << _DOFF, 1)};
/* extern const */ _Dconst _Rteps = {
	INIT((_DBIAS - NBITS / 2) << _DOFF)};

/*** START TI REPLACE ***/
/* extern const */ _DATA_ACCESS double _Xbig = (NBITS + 1) * 347L / 1000;
/* extern const */ _DATA_ACCESS double _Zero = 0.0;
/*** END TI REPLACE ***/
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
