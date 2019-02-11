// fiopen -- _Fiopen(const char */const wchar_t *, ios_base::openmode)
#include <fstream>

 #if _FN_WIDE
  #define _Xfopen	_wfopen
_STD_BEGIN

FILE *_Fiopen(const char *filename,
	ios_base::openmode mode, int prot)	// protection currently unused
	{	// open wide-named file with byte name
	wchar_t wc_name[FILENAME_MAX];

	if (mbstowcs(wc_name, filename, FILENAME_MAX) == (size_t)(-1))
		return (0);
	return _Fiopen(wc_name, mode, prot);
	}

 #else /* _FN_WIDE */
  #define _Xfopen	fopen

_STD_BEGIN

FILE *_Fiopen(const wchar_t *filename,
	ios_base::openmode mode, int prot)	// protection currently unused
	{	// open byte-named file with wide name
	char c_name[FILENAME_MAX];

	if (wcstombs(c_name, filename, FILENAME_MAX) == (size_t)(-1))
		return (0);
	return _Fiopen(c_name, mode, prot);
	}
 #endif /* _FN_WIDE */

FILE *_Fiopen(const _Sysch_t *filename,
	ios_base::openmode mode, int)	// protection currently unused
	{	// open a file with native name
#if defined(__TI_COMPILER_VERSION__)
	static const _DATA_ACCESS _Sysch_t *mods[] =
#else
	static const _Sysch_t *mods[] =
#endif /* defined(__TI_COMPILER_VERSION__) */
		{	// fopen mode strings corresponding to valid[i]
		_SYSCH("r"), _SYSCH("w"), _SYSCH("w"), _SYSCH("a"),
		_SYSCH("rb"), _SYSCH("wb"), _SYSCH("wb"), _SYSCH("ab"),
		_SYSCH("r+"), _SYSCH("w+"), _SYSCH("a+"),
		_SYSCH("r+b"), _SYSCH("w+b"), _SYSCH("a+b"),
		0};
#if defined(__TI_COMPILER_VERSION__)
	static const _DATA_ACCESS int valid[] =
#else
        static const int valid[] =
#endif /* defined(__TI_COMPILER_VERSION__) */
		{	// valid combinations of open flags
		ios_base::in,
		ios_base::out,
		ios_base::out | ios_base::trunc,
		ios_base::out | ios_base::app,
		ios_base::in | ios_base::binary,
		ios_base::out | ios_base::binary,
		ios_base::out | ios_base::trunc | ios_base::binary,
		ios_base::out | ios_base::app | ios_base::binary,
		ios_base::in | ios_base::out,
		ios_base::in | ios_base::out | ios_base::trunc,
		ios_base::in | ios_base::out | ios_base::app,
		ios_base::in | ios_base::out | ios_base::binary,
		ios_base::in | ios_base::out | ios_base::trunc
			| ios_base::binary,
		ios_base::in | ios_base::out | ios_base::app
			| ios_base::binary,
		0};

	FILE *fp = 0;
	int n;
	ios_base::openmode atendflag = mode & ios_base::ate;
	ios_base::openmode norepflag = mode & ios_base::_Noreplace;

	if (mode & ios_base::_Nocreate)
		mode |= ios_base::in;	// file must exist
	if (mode & ios_base::app)
		mode |= ios_base::out;	// extension -- app implies out

	mode &= ~(ios_base::ate | ios_base::_Nocreate | ios_base::_Noreplace);
	for (n = 0; valid[n] != 0 && valid[n] != mode; ++n)
		;	// look for a valid mode

	if (valid[n] == 0)
		return (0);	// no valid mode
	else if (norepflag && mode & (ios_base::out || ios_base::app)
		&& (fp = _Xfopen(filename, _SYSCH("r"))) != 0)
		{	// file must not exist, close and fail
		fclose(fp);
		return (0);
		}
	else if (fp != 0 && fclose(fp) != 0)
		return (0);	// can't close after test open
// should open with protection here, if other than default
	else if ((fp = _Xfopen(filename, mods[n])) == 0)
		return (0);	// open failed

	if (!atendflag || fseek(fp, 0, SEEK_END) == 0)
		return (fp);	// no need to seek to end, or seek succeeded

	fclose(fp);	// can't position at end
	return (0);
		}
_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
