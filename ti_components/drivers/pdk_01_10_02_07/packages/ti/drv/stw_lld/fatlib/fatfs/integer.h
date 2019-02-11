/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef FF_INTEGER_
#define FF_INTEGER_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */

/* This type MUST be 8 bit */
typedef unsigned char	BYTE;

/* These types MUST be 16 bit */
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types MUST be 16 bit or 32 bit */
typedef int				INT;
typedef unsigned int	UINT;

/* These types MUST be 32 bit */
typedef int				LONG;
typedef unsigned int	DWORD;

#undef FALSE
#undef TRUE

/* Boolean type */
#ifndef BOOL_FLAG
  #define BOOL_FLAG
typedef enum {FALSE = 0, TRUE} BOOL;
#endif

#endif

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
