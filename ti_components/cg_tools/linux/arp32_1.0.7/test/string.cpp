// string -- template string support functions
#include <istream>
_STD_BEGIN

 #if _IS_EMBEDDED
const string::size_type string::npos =
	(string::size_type)(-1);	// define npos as largest positive value
 #endif /* _IS_EMBEDDED */

void _String_base::_Xlen() const
	{	// report a length_error
	_THROW(length_error, "string too long");
	}

void _String_base::_Xran() const
	{	// report an out_of_range error
	_THROW(out_of_range, "invalid string position");
	}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
