/*
 *  Copyright 2016 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== _cof.h ========
 *
 *  Private definitions for the TI and Motorola COFF module.
 *
 */


/*
 *  Motorola COFF files have too many sections to keep all the section headers
 *  in memory.  For this reason the COF_HandleObj keeps _COF_NHDRS sections in 
 *  memory at a time and scans through the file to read them all in.  For
 *  consistency, we'll do the same thing for the TI world.
 */

#ifndef _COF_
#  define _COF_

#  include "cof.h"

#  define _COF_NHDRS   16

/*
 *  ======== COF_HandleObj ========
 */
typedef struct COF_HandleObj {
    /*
     *  All three of these file handles will point to the same file.  By
     *  maintaining three file handles, we can avoid having to preserve and
     *  restore file pointers when different parts of the file need to be read.
     */
    Void           *file;           /* File handle for most operations.      */
    Void           *stfile;         /* File handle for reading string table. */
    Void           *scanFile;       /* File handle for scan functions.       */
    COF_Attrs       attrs;
    COF_FileHdr     header;
    COF_OptHdr      optHeader;
    COF_LinkHdr     linkHeader;     /* Only used with Motorola COFF */
    Long            sectHdrOffset;  /* fseek offset to section headers */
    COF_SectHdr    *sectHdrs;
    Int             sectHdrBase;
    Int             coftype;
    UChar           *loadbuf;
    Bool            byteSwapped;
    Long            strTab;         /* file offset to string table */
    Long            curSymIndex;
    Long            curRelocIndex;  /* current relocation index */
    COF_SectHdr    *curSect;        /* current section for scan reloc info */
    Int             numCurSects;    /* number of section headers in memory */
} COF_HandleObj;

/* utility functions */

extern Void _COF_getName(COF_Handle desc, COF_NameDesc *nameDesc, String name);
extern COF_SectHdr *_COF_getSectPtr(COF_Handle desc, Int sectNum);
extern Void _COF_swapMdInt(Short *);
extern Void _COF_swapMdUns(UShort *);
extern Void _COF_swapLgInt(Long *);
extern Void _COF_swapLgUns(ULong *);

/*
 * ======== _COF_swapL ========
 *
 * A good compile will remove half of this at compile-time, since it
 * is a constant expression as an if-condition.  The whole point of this
 * is to allow ULong or Long to be passed in, but nothing else.
 */
#define _COF_swapL(lp) { \
    if (sizeof *(lp) != 4) { \
        assert(0 == 1); \
    } else { \
        _COF_swapLgUns((ULong *)(lp)); \
    } \
}

/*
 * ======== _COF_swapM ========
 *
 * Analogous to _COF_swapL
 */
#define _COF_swapM(mp) { \
    if (sizeof *(mp) != 2) { \
        assert(0 == 1); \
    } else { \
        _COF_swapMdUns((UShort *)(mp)); \
    } \
}

#  if defined(_TI_)
#    define _COF_swapAddr(a)        _COF_swapLgUns(a)
#    define _COF_swapByte(u)
#    define _COF_swapInt(u)         _COF_swapMdInt(u)
#    define _COF_swapUns(u)         _COF_swapMdUns(u)

#    define _COF_SECTHDRSIZE01 ((UInt)&(((COF_SectHdr01*)NULL)->pageNum) \
             + sizeof(((COF_SectHdr01*)NULL)->pageNum))

#    define _COF_SECTHDRSIZE2 ((UInt)&(((COF_SectHdr*)NULL)->pageNum) \
             + sizeof(((COF_SectHdr*)NULL)->pageNum))

#    define _COF_OPTHDRSIZE (&(((COF_OptHdr*)NULL)->dataAddr) \
             + sizeof(((COF_OptHdr*)NULL)->dataAddr))

#    define _COF_MAXVER 2       /* Supports up to Version 2 for TI. */

#  elif defined (_MOT_)
#    define _COF_swapAddr(a)        _COF_swapLgUns(&((*(a)).addr)); \
                                 _COF_swapLgUns(&((*(a)).map))
#    define _COF_swapByte(u)        _COF_swapLgInt(u)
#    define _COF_swapInt(u)         _COF_swapLgInt(u)
#    define _COF_swapUns(u)         _COF_swapLgUns(u)

#    define _COF_SECTHDRSIZE01 ((UInt)&(((COF_SectHdr01*)NULL)->flags) \
             + sizeof(((COF_SectHdr01*)NULL)->flags))

#    define _COF_SECTHDRSIZE2 ((UInt)&(((COF_SectHdr*)NULL)->flags) \
             + sizeof(((COF_SectHdr*)NULL)->flags))

#    define _COF_OPTHDRSIZE (&(((COF_OptHdr*)NULL)->dataEnd) \
             + sizeof(((COF_OptHdr*)NULL)->dataEnd))
#  endif

#  define _COF_swapLong(u)        _COF_swapLgInt(u)
#  define _COF_swapSize(u)        _COF_swapLgInt(u)
#  define _COF_swapPtr(u)         _COF_swapLgInt(u)

#define _COF_OLDHDRSIZE &(((COF_FileHdr*)NULL)->magic)

#define _COF_FILEHDRSIZE ((UInt)&(((COF_FileHdr*)NULL)->magic) \
             + sizeof(((COF_FileHdr*)NULL)->magic))

/* 
 * In functions where the interface includes a parameter that is not needed,
 * this macro can be used to "use" an unused parameter and avoid compiler
 * warnings.
 */

#  define _COF_USEARG(x)       (x = x)

#endif  /* #ifndef COFDEFS_ */
/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 10-21-2016 18:37:04; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

