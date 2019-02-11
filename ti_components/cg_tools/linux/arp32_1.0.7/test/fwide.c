/* fwide function */
#include <stdio.h>

 #if _HAS_DINKUM_CLIB	/* compiler test */
 #include "xwstdio.h"
_STD_BEGIN

int (fwide)(FILE *str, int mode)
	{	/* set/test wide/narrow file mode */
	int ans;

	_Lockfileatomic(str);
	if (mode < 0 && !(str->_Mode & _MWIDE))
		str->_Mode |= _MBYTE;
	else if (0 < mode && !(str->_Mode & _MBYTE))
		str->_Mode |= _MWIDE;
	ans = str->_Mode & _MBYTE ? -1
		: str->_Mode & _MWIDE ? 1 : 0;
	_Unlockfileatomic(str);
	return (ans);
	}
_STD_END
 #endif /* _HAS_DINKUM_CLIB */

 #if !_HAS_DINKUM_CLIB	/* compiler test */ \
	&& (defined(__GNUC__) && __GNUC__ < 3 \
  	  || defined(__BORLANDC__) \
	  || defined(__TI_COMPILER_VERSION__))
  #include <stdio.h>
  #include <yvals.h>


_STD_BEGIN
int (fwide)(FILE *str, int mode)
	{	/* set/test wide/narrow file mode */
	return (0);
	}
_STD_END
 #endif /* !_HAS_DINKUM_CLIB etc. */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
