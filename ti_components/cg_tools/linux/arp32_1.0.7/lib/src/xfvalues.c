/* values used by math functions -- IEEE 754 float version */
#include "xmath.h"
_STD_BEGIN

		/* macros */
#define NBITS	(16 + _FOFF)

 #if _D0 == 0
  #define INIT(w0)		{w0, 0}
  #define INIT2(w0, w1)	{w0, w1}

 #else /* _D0 == 0 */
  #define INIT(w0)		{0, w0}
  #define INIT2(w0, w1)	{w1, w0}
 #endif /* _D0 == 0 */

		/* static data */
/* extern const */ _Dconst _FDenorm = {INIT2(0, 1)};
/* extern const */ _Dconst _FEps = {
	INIT((_FBIAS - NBITS - 1) << _FOFF)};
/* extern const */ _Dconst _FInf = {INIT(_FMAX << _FOFF)};
/* extern const */ _Dconst _FNan = {INIT((_FMAX << _FOFF)
	| (1 << (_FOFF - 1)))};
/* extern const */ _Dconst _FSnan = {INIT2(_FMAX << _FOFF, 1)};
/* extern const */ _Dconst _FRteps = {
	INIT((_FBIAS - NBITS / 2) << _FOFF)};

/*** START TI REPLACE ***/
/* extern const */ _DATA_ACCESS float _FXbig = (NBITS + 1) * 347L / 1000;
/* extern const */ _DATA_ACCESS float _FZero = 0.0F;
/*** END TI REPLACE ***/
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
