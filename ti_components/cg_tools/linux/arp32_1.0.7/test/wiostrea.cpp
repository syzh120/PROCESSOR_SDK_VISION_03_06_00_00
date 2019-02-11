// wiostream -- initialize standard wide streams
#include <fstream>

 #if _IS_EMBEDDED

 #else /* _IS_EMBEDDED */
#include <iostream>
#include <new>
_STD_BEGIN

		// OBJECT DECLARATIONS
int _Winit::_Init_cnt = -1;	// net constructors - destructors
static wfilebuf wfin(_Noinit);	// uninitialized wcin buffer
static wfilebuf wfout(_Noinit);	// uninitialized wcout buffer
static wfilebuf wferr(_Noinit);	// uninitialized wcerr/wclog buffer
wistream wcin(_Noinit);	// uninitialized wcin
wostream wcout(_Noinit);	// uninitialized wcout
wostream wcerr(_Noinit);	// uninitialized wcerr
wostream wclog(_Noinit);	// uninitialized wclog

_Winit::_Winit()
	{	// initialize standard wide streams first time
	bool doinit;
		{	// lock and test whether to initialize
		_Lockit lock(_LOCK_STREAM);
		if (0 <= _Init_cnt)
			++_Init_cnt, doinit = false;	// redundant initialization, skip
		else
			_Init_cnt = 1, doinit = true;	// first initialization, do it
		}

	if (doinit)
		{	// initialize standard wide streams
		new (&wfin) wfilebuf(stdin);
		new (&wfout) wfilebuf(stdout);
		new (&wferr) wfilebuf(stderr);
		new (&wcin) wistream(&wfin, true);
		new (&wcout) wostream(&wfout, true);
		wcin.tie(&wcout);
		new (&wcerr) wostream(&wferr, true);

 #if _HAS_STRICT_CONFORMANCE

 #else /* _HAS_STRICT_CONFORMANCE */
		wcerr.tie(&wcout);
 #endif /* _HAS_STRICT_CONFORMANCE */

		wcerr.setf(ios_base::unitbuf);
		new (&wclog) wostream(&wferr, true);
		wclog.tie(&wcout);
		}
	}

_Winit::~_Winit()
	{	// flush standard wide streams on last destruction
	bool doflush;
		{	// lock and test whether to flush streams
		_Lockit lock(_LOCK_STREAM);
		if (--_Init_cnt == 0)
			doflush = true;	// last destruction, do it
		else
			doflush = false;	// not last destruction, skip
		}

	if (doflush)
		{	// flush standard wide streams, but don't destroy
		wcout.flush();
		wcerr.flush();
		wclog.flush();
		}
	}
_STD_END
 #endif /* _IS_EMBEDDED */

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
