/*
 *  Copyright 2016 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== cof.c ========
 *
 *  Motorola and TI DSP COFF support
 *
 *  Either _TI_ or _MOT_ must be defined (preferably by using a
 *  -D switch with the compiler) in order to compile correctly.
 *
 *  Note this module is INCOMPLETE.  Full support for the C30 and C40
 *  will require more work in at least the area of doReloc to support
 *  32-bit address relocation.
 *
 *  To Do:
 *  1) Clean up {big, little}-endian support. This is needed in the
 *     the COF_loadArgs for the byte-addr proc's like the C80 and C62
 *
 */

#if defined(_VXWORKS_)
#  include <stdioLib.h>
#else
#  include <stdio.h>
#endif

#ifdef UNDER_CE
#include <windows.h>
#endif

#include <xdc/std.h>

#include <string.h>
#include <stdlib.h>

#include <cof.h>
#include <_cof.h>

#define MIN(a,b)            ((a)<(b)?(a):(b))

/* magic values stored in COF_FileHdr in the COFF file */
#define COF_C430MAGIC     0xA0  /* Magic number for TI MSP430 COF  */
#define COF_C28MAGIC      0x9D  /* Magic number for TI C28 COF  */
#define COF_C30MAGIC      0x93  /* Magic number for TI C30 COF  */
#define COF_C40MAGIC      0x93  /* Magic number for TI C40 COF  */
#define COF_C50MAGIC      0x92  /* Magic number for TI C50 COF  */
#define COF_C54MAGIC      0x98  /* Magic number for TI C54 COF  */
#define COF_C55MAGIC      0x9c  /* Magic number for LEAD3 (C55) COF  */
#define COF_C56MAGIC      0xA1  /* Magic number for Ryujin (C56) COF  */
#define COF_C62MAGIC      0x99  /* Magic number for TI C62x COF */
#define COF_C80MAGIC      0x95  /* Magic number for TI C80 COF  */
#define COF_ARMMAGIC      0x97  /* Magic number for TI ARM COF */
#define COF_VER0MAGIC     0xc0  /* Magic number for TI version 0 COFF format */
#define COF_VER1MAGIC     0xc1  /* Magic number for TI version 1 COFF format */
#define COF_VER2MAGIC     0xc2  /* Magic number for TI version 2 COFF format */
#define COF_OPTMAGIC      0x108
#define COF_56KHDRMAGIC   0x2c5
#define COF_561CHDRMAGIC  0x2c7
#define COF_563CHDRMAGIC  0x2c8
#define COF_96KHDRMAGIC   0xffff      /* WRONG: Don't know 96K magic! */
#define COF_BADMAGIC      0x0   /* Invalid magic number */

/*
 *  ======== frees ========
 *  In case we want to track sizes in the future
 */
#define frees(p,s) (free(p))

/*
 *  ======== assert ========
 */
#define assert(t)

/*
 *  ======== readDatumAt ========
 *
 *  Read a single item of the item's size (1, 2, or 4); swapping as needed.
 *  (Could return (FALSE) on read error; overhead not worth it.)
 */
#define readDatumAt(datump, file, swap, readfxn) { \
    readfxn((Char *)(datump), sizeof *(datump), 1, (file)); \
    if (sizeof *(datump) == 4 && (swap) == TRUE ) { \
        _COF_swapL(datump); \
    } else if (sizeof *(datump) == 2 && (swap) == TRUE ) { \
        _COF_swapM(datump); \
    } \
}

/*
 *  ======== readAddrAt ========
 *
 *  This macro accomodates the different address structures used in the
 *  TI and Motorola worlds.
 */
#if defined(_TI_)

#  define readAddrAt(datump, file, swap, readfxn) \
       readDatumAt(datump, file, swap, readfxn)

#elif defined(_MOT_)

#  define readAddrAt(datump, file, swap, readfxn) {   \
       readDatumAt(datump.addr, file, swap, readfxn); \
       readDatumAt(datump.map,  file, swap, readfxn); \
       }

#endif

#if defined(_MOT_)
#  define sectHdrSize(a) _COF_SECTHDRSIZE01
#elif defined(_TI_)
UInt _sectHdrSize[_COF_MAXVER + 1] = {
    _COF_SECTHDRSIZE01,
    _COF_SECTHDRSIZE01,
    _COF_SECTHDRSIZE2
};
#  define sectHdrSize(a) _sectHdrSize[(a)]
#endif

/*
 *  ======== Target ========
 *  Field mausize:
 *      Number of bytes in minimum addressable unit. 
 *  Field charsize:
 *      Number of bytes in a character. For the C6x, charsize = 1, since
 *      4 characters are packed into a word. For C55x, charsize = 2,
 *      since data memory is word addressable, although mausize = 1 (program
 *      memory is byte addressable).
 */
typedef struct Target {
    Int     type;           /* COF_??? identifier */
    COF_Uns magic;          /* different chips have different magic */
    Int     wordsize;       /* Size of a word */
    Int     mausize;        /* Size of minimum addressable unit */
    Int     charsize;       /* For C55x, mausize = 1, but charsize = 2 */
    Int     ptrsize;        /* pointer size; C55L == 4, C55 == 2 */
} Target;

/*
 * Default COF attributes:  All NULL or zero.  fopen, fclose, ftell, fread,
 * and fseek must all be set to non-NULL in order to sucessfully call
 * COF_create().
 */

const COF_Attrs COF_ATTRS = {
    NULL,                   /* write function callback */
    (Ptr)NULL,              /* write function argument */
    NULL,                   /* lookup function callback */
    (Ptr)NULL,              /* lookup function argument */
    NULL,                   /* fread */
    NULL,                   /* fseek */
    NULL,                   /* ftell */
    NULL,                   /* fclose */
    NULL,                   /* fopen */
    NULL,                   /* fwrite */
    0L,                     /* default arguments addr */
    0L,                     /* default arguments size */
    0x800                   /* default load buffer size */
};

/*
 * Target specific definitions indexed by target type (COF_C30, .., COF_96K).
 * The indexing into this table MUST match the definitions for COF_C30,
 * COF_C40, ... , COF_96K.  We have separate targetTab's for _TI_ and _MOT_
 * so that magic2type() will fail when, for example, it's called in the TI
 * world with a MOT COFF file.
 */

#if defined _TI_

static  Target  targetTab[] = {
    /* targ     magic           word    mau     char    ptr */
    {COF_C30,   COF_C30MAGIC,   4,      4,      4,      4},     /* C30  */
    {COF_C40,   COF_C40MAGIC,   4,      4,      4,      4},     /* C40  */
    {COF_C50,   COF_C50MAGIC,   2,      2,      2,      2},     /* C50  */
    {COF_C54,   COF_C54MAGIC,   2,      2,      2,      2},     /* C54  */
    {COF_C62,   COF_C62MAGIC,   4,      1,      1,      4},     /* C62x */
    {COF_C80,   COF_C80MAGIC,   4,      1,      1,      4},     /* C80  */
    {COF_C55,   COF_C55MAGIC,   2,      1,      2,      2},     /* C55  */
    {COF_C28,   COF_C28MAGIC,   2,      2,      2,      2},     /* C28  */
    {COF_C56B,  COF_C56MAGIC,   2,      1,      1,      4},     /* C56 byte */
    {COF_C56W,  COF_C56MAGIC,   2,      2,      2,      4},     /* C56 word */
    {COF_ARM,   COF_ARMMAGIC,   4,      1,      1,      4},     /* ARM */
    {COF_C55L,  COF_C55MAGIC,   2,      1,      2,      4},     /* C55L  */
    {COF_C430,  COF_C430MAGIC,  2,      1,      1,      2},     /* MSP430  */
};

#elif defined _MOT_
/* 56K wdsize == 3 but host promote to 4 */    
static  Target  targetTab[] = {
    /* targ     magic           word    mau     char    ptr */
    {COF_56K,   COF_56KHDRMAGIC,  4,    4,      4,      4},         /* 56K */
    {COF_561C,  COF_561CHDRMAGIC, 4,    4,      4,      4},         /* 56100 */
    {COF_563C,  COF_563CHDRMAGIC, 4,    4,      4,      4},         /* 56300 */
    {COF_96K,   COF_96KHDRMAGIC,  4,    4,      4,      4},         /* 96K */
};

#else
    
static  Target  targetTab[] = {
};
    
#endif

#define TARGETTABLEN (sizeof(targetTab) / sizeof(Target))

#if defined(_TI_)

static Bool  doCinit(COF_Handle desc, UChar *data, Int nbytes, Int *extra);
static Bool  doCinit32(COF_Handle desc, UChar *data, Int nbytes, Int *extra);
static Bool  doCinit6x(COF_Handle desc, UChar *data, Int nbytes, Int *extra);
#define COF_C6XALIGN      0x8   /* cinit record alignment used for C6x */

#elif defined(_MOT_)

static Bool doBlockSection(COF_Handle desc, COF_SectHdr *sectPtr, ULong addr);

#endif

static Bool     doReloc(COF_Handle d, COF_SectHdr *s, Int sectNum, UChar *b, 
                     ULong a, Int n, ULong sb[]);
static COF_Uns  getFileMagic(COF_Handle desc);
static Int      getHeaders(COF_Handle desc);
static Int      getSectHdrs(COF_Handle desc, Int base);
static Int      getSpace(COF_SectHdr *sect);
static Int      loadArgs(COF_Handle desc, Bool cgFormat,
                            ULong argsAddr, ULong argsSize,
                            Int argc, Char *argv[], Char *envp[]);
static UInt     fillArgs(COF_Handle desc, Bool cgFormat,
                            ULong argsAddr, Int argc, String argv[],
                            Int envc, String envp[],
                            Char *argbuf);
static Int      magic2type(COF_Handle desc, COF_Uns magic);
static ULong    nop(void *p, ULong addr, void *data, ULong nbytes, Int mtype);
static Char     *copyString(Char *dst, Char *src, Int charsize);
static ULong    *copyLongPtr(ULong targPtr, Int cofType, ULong *hostBuf);

/*
 *  ======== COF_byteSize ========
 *
 *  Return the byte size of the target processor for which the COFF file is
 *  intended.  Note that the byte size that is returned is the least power
 *  of two greater than or equal to the number of 8-bit bytes in a target
 *  byte. For example, the byte size returned for the Motorola 24-bit
 *  processors is 4.
 */
unsigned int COF_byteSize(COF_Handle desc)
{
    if (desc->coftype < TARGETTABLEN) {
        return (targetTab[desc->coftype].mausize);
    }
    else {
        return (0);
    }
}

/*
 *  ======== COF_byteSwapped ========
 */
Bool COF_byteSwapped(COF_Handle hnd)
{
    return (hnd->byteSwapped);
}

/*
 *  ======== COF_charSize ========
 *
 *  Return the size of a character. This is needed to support C55x, where
 *  characters are 2 bytes, but MAU size is 1 byte.
 */
unsigned int COF_charSize(COF_Handle desc)
{
    if (desc->coftype < TARGETTABLEN) {
        return (targetTab[desc->coftype].charsize);
    }
    else {
        return (0);
    }
}

/*
 *  ======== COF_create ========
 *
 *  Allocate the COF handle object, assign values to handle object fields,
 *  open COFF file, and read file and section headers.
 */
COF_Handle COF_create(Int type, String fname, Int *status, COF_Attrs *attrs)
{
    COF_Handle  desc;
    Int         dummy;
    String      mode;

    /* so we can pass NULL status pointer */
    if (status == NULL) {
        status = &dummy;
    }

    if (attrs == NULL
        || attrs->fopen == NULL || attrs->fclose == NULL
        || attrs->ftell == NULL || attrs->fread == NULL
        || attrs->fseek == NULL) {
        *status = COF_EOPEN;    /* attrs MUST define file functions */
        return (NULL);
    }

    if (type != COF_UNKNOWN
            && (type < 0 || type >= TARGETTABLEN)) {
        *status = COF_EBADARG;
        return (NULL);
    }
    
    if ((desc = (COF_Handle)calloc(sizeof(COF_HandleObj), 1)) == NULL) {
        *status = COF_EMEM;
        return (NULL);
    }

    /* make a local copy of the attributes */
    desc->attrs = *attrs;
    if (desc->attrs.write == NULL) {
        desc->attrs.write = nop;
    }
    desc->coftype = type;
    desc->byteSwapped = FALSE;
    desc->sectHdrs = NULL;

    /* allocate a load buffer for passing blocks to the write callback */
    if ((desc->loadbuf = (UChar *)malloc(desc->attrs.loadBufSize)) == NULL) {
        COF_delete(desc);
        *status = COF_EMEM;
        return (NULL);
    }

    /* open the general-use file handle in binary mode */

    if ((desc->file = (*desc->attrs.fopen)(fname, "rb")) == NULL) {
        COF_delete(desc);
        *status = COF_EOPEN;
        return (NULL);
    }
    
    /* open the string table file handle */
    if ((desc->stfile = (*desc->attrs.fopen)(fname, "rb")) == NULL) {
        COF_delete(desc);
        *status = COF_EOPEN;
        return (NULL);
    }

    /*
     *  open the scan file handle, for use by COF_scan/nextReloc and
     *  COF_scan/nextSymbol.
     */
    mode = attrs->fwrite == NULL ? "rb" : "r+b";
    if ((desc->scanFile = (*desc->attrs.fopen)(fname, mode)) == NULL) {
        COF_delete(desc);
        *status = COF_EOPEN;
        return (NULL);
    }

    if ((*status = getHeaders(desc)) != COF_EOK) {
        COF_delete(desc);
        return (NULL);
    }

    /* offset in the file of string table (first 4 bytes are length) */
    desc->strTab = desc->header.symTabPtr
                    + (desc->header.nSyms * COF_SYMBOLSIZE);

    return (desc);
}                                       /* COF_create() */


/*
 *  ======== COF_delete ========
 *
 *  Close files and free objects allocated during COF_create.
 */
Void COF_delete(COF_Handle desc)
{
    if (desc != NULL) {

        if (desc->sectHdrs != NULL) {
            frees(desc->sectHdrs,
                     (size_t)desc->numCurSects * sizeof(COF_SectHdr));
        }

        if (desc->file != NULL) {
            (*desc->attrs.fclose)(desc->file);
        }
        if (desc->stfile != NULL) {
            (*desc->attrs.fclose)(desc->stfile);
        }
        
        if (desc->scanFile != NULL) {
            (*desc->attrs.fclose)(desc->scanFile);
        }
        
        if (desc->loadbuf != NULL) {
            frees(desc->loadbuf, desc->attrs.loadBufSize);
        }
    
        frees(desc, sizeof(COF_HandleObj));
    }
}


/*
 *  ======== COF_exit ========
 */
Void COF_exit(Void)
{
}

/*
 *  ======== COF_getEntry ========
 *
 *  Get the target processor entry point address, which is stored in
 *  the optional header.
 */
int COF_getEntry(COF_Handle desc, ULong *entry)
{
    if (desc == NULL || entry == NULL) {
        return (COF_EBADARG);
    }

    /*
     * If we've successfully gotten through COF_create() and "desc" is 
     * valid, then header data has been read and we can safely look at 
     * desc->header.optHdrSize.
     */
    else if (desc->header.optHdrSize != sizeof(COF_OptHdr)) {
        return (COF_EOHEADER);
    }
 
    *entry = COF_offset(desc->optHeader.entryPoint);
    return (COF_EOK);
}

/*
 *  ======== COF_getHeader ========
 *
 *  Get the file header from the COF handle object.  This function is provided
 *  because the COF handle object is hidden from the user.
 */
void COF_getHeader(COF_Handle desc, COF_FileHdr *header)
{
    *header = desc->header;
}


/*
 *  ======== COF_getSect ========
 *
 *  Given a section name, find the first section with that name and
 *  copy the section header data into the structure pointed to by the
 *  parameter "sect".  
 */
Int COF_getSect(COF_Handle desc, String name, COF_SectHdr *sect)
{
    COF_SectHdr *sectPtr;
    Int i;
    Int nameLen;
    
    if (desc->sectHdrs) {
        nameLen = strlen(name);
        
        for (i = 1; i <= (Int)desc->header.nSects; i++) {
            if ((sectPtr = _COF_getSectPtr(desc, i)) == NULL) {
                break;
            }

            if (nameLen <= COF_NAMELEN
                && sectPtr->nameDesc.stringPtr.immedFlag) {
                if (strncmp(sectPtr->nameDesc.name, name, COF_NAMELEN) == 0) {
                    *sect = *sectPtr;
                    return (COF_EOK);
                }
            }
            else {
                Char sectName[COF_MAXEXPR + 1];
                _COF_getName(desc, &sectPtr->nameDesc, sectName);
                if (strcmp(sectName, name) == 0) {
                    *sect = *sectPtr;
                    return (COF_EOK);
                }
            }
        }
    }
    return (COF_ESECT);
}

/*
 *  ======== COF_getSectHdrSize ========
 *
 *  Given a COFF file handle, return the section header size being used.
 */
unsigned COF_getSectHdrSize(COF_Handle hnd)
{
    UInt version;

    switch (hnd->header.version) {
        case COF_VER0MAGIC:
            version = 0;
            break;
        case COF_VER1MAGIC:
            version = 1;
            break;
        case COF_VER2MAGIC:
            version = 2;
            break;
        default:
            version = 2;
    }
    return(sectHdrSize(version));
}

/*
 *  ======== _COF_getSectPtr ========
 *
 *  Get a pointer to a section header, indexed by parameter "sectNum".
 *  COFF conventions number sections beginning with "1" rather than
 *  "0".  This is a hidden function
 */
COF_SectHdr *_COF_getSectPtr(COF_Handle desc, Int sectNum)
{
    COF_SectHdr *sectPtr;

    if (sectNum < 1 || sectNum > (Int)desc->header.nSects) {
        return (NULL);
    }
        
    if (sectNum < desc->sectHdrBase
            || desc->sectHdrBase + desc->numCurSects <= sectNum) {
        if (getSectHdrs(desc, sectNum) != COF_EOK) {
            return (NULL);
        }
    }

    sectPtr = desc->sectHdrs + sectNum - desc->sectHdrBase;
    return (sectPtr);
}

/*
 *  ======== COF_getTargetType ========
 *
 *  Return the "coftype" field of the COF handle object, which indicates the
 *  target processor for which the COFF file opened with COF_create is
 *  intended.  This function is provided because the COF handle object is
 *  hidden from the user.
 */
Int COF_getTargetType(COF_Handle desc)
{
    return (desc->coftype);
}

/*
 *  ======== COF_init ========
 *
 *  Do any and all initialization required by the Spectron COF module.
 *  COF_init must be called before any of the Spectron COF functions are used.
 */
Void COF_init(Void)
{
    Target *tp;

    /* we use COF_???? to index into targetTab[] */
    for (tp = targetTab + TARGETTABLEN - 1; tp >= targetTab; tp--) {
        assert(tp->type == (tp - targetTab));
    }
}


/*
 *  ======== COF_load ========
 *
 *  Load the program in the COFF file onto a processor, along with the
 *  arguments and environment passed to COF_load() in the argc, argv, and
 *  envp arguments.  If the COFF file doesn't have a ".args" section, the
 *  target destination for the arguments and environment must be specified
 *  with the "argsAddr" and "argsSize" fields in the "attrs" parameter to
 *  COF_create().  The "entry" parameter to COF_load is a return parameter,
 *  used for returning the target program's entry point.
 */
Int COF_load(COF_Handle desc, Int argc, String argv[], String envp[], 
             ULong *entry)
{
    Int         error;
    ULong       argsAddr;
    ULong       argsSize;
    COF_SectHdr *argsSect;

    if ((error = COF_loadCode(desc, entry)) != COF_EOK) {
        return (error);
    }
    
    /* allocate the section header so we can pass the address in a DLL */
    if ((argsSect = (COF_SectHdr *)malloc(sizeof(COF_SectHdr))) == NULL) {
        return (COF_EMEM);
    }
    
    error = COF_getSect(desc, ".args", argsSect);
    if (error == COF_EOK) {
        argsAddr = COF_offset(argsSect->physAddr);
        argsSize = argsSect->size;   /* in DSP words */
    }
    else {
        argsAddr = desc->attrs.argsAddr;
        argsSize = desc->attrs.argsSize;
    }
    frees(argsSect, sizeof(COF_SectHdr));

    if (argc > 0 && argv != NULL) {

        COF_Symbol sym;
        /* although we are supposed to only look for "__c_args__", codegen
         * seems to always define this symbol.  So we look for codegen's
         * _args_main function instead.
         */
        if (COF_getCSymbol(desc, "_args_main", &sym) == COF_EOK) {
            /* load CG format arguments */
            error = COF_loadCGArgs(desc, argsAddr, argsSize, argc, argv, envp);
        }
        else {
            /* load SPOX/BIOS format arguments */
            error = COF_loadArgs(desc, argsAddr, argsSize, argc, argv, envp);
        }
        return (error);
    }
    
    return (COF_EOK);
}


/*
 *  ======== COF_loadArgs ========
 *
 *  Load argc, argv[], and envp[] onto the target processor, using the "write"
 *  function specified in the "attrs" structure passed to COF_create.  The
 *  "argsAddr" and "argsSize" parameters to COF_loadArgs indicate the
 *  destination address and the amount of space on the target processor
 *  available for arguments and environment.
 *
 *  The .args buffer has the form:
 *
 *      argc,
 *  +-- *argv,
 *  |   *envp, -----+   
 *  +-->argv[0], -------+
 *      argv[1],    |   |
 *      ...,        |   |
 *      argv[n],    |   |
 *  +-- envp[0],<---+   |
 *  |   envp[1],        |
 *  |   ... ,           |
 *  |   envp[n],        |
 *  |   argv 0 string,<-+
 *  |   argv 1 string,
 *  |   ...
 *  |   argv n string,
 *  +-->envp 0 string,
 *      envp 1 string,
 *      ...
 *      envp n string,
 */

Int COF_loadArgs(COF_Handle desc, ULong argsAddr, ULong argsSize,
                 Int argc, Char *argv[], Char *envp[])
{
    return (loadArgs(desc, FALSE, argsAddr, argsSize, argc, argv, envp));
}


/*
 *  ======== COF_loadCGArgs ========
 *
 *  Load argc, argv[] according to TI CodeGen's format onto the target
 *  processor, using the "write" function specified in the "attrs" structure
 *  passed to COF_create.  The "argsAddr" and "argsSize" parameters to
 *  COF_loadArgs indicate the destination address and the amount of space on
 *  the target processor available for arguments and environment.
 *
 *  The .args buffer has the form:
 *
 *     argc,
 *     argv[0], -------+
 *     argv[1],        |
 *     ...,            |
 *     argv[n] = NULL, |
 *     envc,           |
 *     envp[0], ------ | -+
 *      :              |  |
 *     envp[m] = NULL  |  |
 *     argv 0 string,<-+  |
 *     argv 1 string,     |
 *     ...                |
 *     argv n string,     |
 *     envp 0 string,<----+
 */

Int COF_loadCGArgs(COF_Handle desc, ULong argsAddr, ULong argsSize,
                 Int argc, Char *argv[], Char *envp[])
{
    return (loadArgs(desc, TRUE, argsAddr, argsSize, argc, argv, envp));
}

/*
 *  ======== COF_loadCode ========
 *
 *  This function loads the program in the COFF file into the target processor
 *  and returns the entry point address in the "entry" parameter.  A board-
 *  specific write function must be assigned to the "write" field of the
 *  "attrs" parameter to COF_create().
 */
Int COF_loadCode(COF_Handle desc, ULong *entry)
{
    Int         sectNum;
    COF_SectHdr *sectPtr;
    Bool        bss;

    for (sectNum = 1; sectNum <= (Int)desc->header.nSects; sectNum++) {
        if ((sectPtr = _COF_getSectPtr(desc, sectNum)) == NULL) {
            return (COF_ESECT);
        }

        bss = (Bool) ((sectPtr->flags & COF_S_BSS) != 0 &&
                      strcmp(sectPtr->nameDesc.name, ".bss") == 0);

        /*
         * Ignore empty sections or sections whose flags indicate the
         * section is not to be loaded.  Note that the cinit section,
         * although it has the COF_S_COPY flag set, must be loaded.   
         */
        if (sectPtr->dataPtr == 0L && !bss ||
                sectPtr->size == 0L ||
                (sectPtr->flags & (COF_S_DSECT | COF_S_NOLOAD)) ||
                (sectPtr->flags & COF_S_COPY)
                && strcmp(sectPtr->nameDesc.name, ".cinit")) {
            continue;
        }

        if (!COF_loadSect(desc, sectPtr, sectNum, NULL, bss)) {
            return (COF_ESECT);
        }
    }

    if (entry != NULL) {
        return (COF_getEntry(desc, entry));
    }
    
    return (COF_EOK);
}

/*
 *  ======== COF_loadSect ========
 *
 *  Write the data for one section to the target processor, using the function
 *  specified with the "write" field in the "attrs" parameter to COF_create().
 */
Bool COF_loadSect(COF_Handle desc, COF_SectHdr *sectPtr, 
                  Int sectNum, ULong sectBase[], Bool bss)
{
    Int     nbytes, nwords, bufsize, wordsize;
    Int     extra = 0;
    Long   total;              
    ULong   addr;
    Long   save;
    Bool    applyCinit = FALSE;
    UChar    *buf;
    Int     space;
    
    if (bss) {
        /* clear load buffer */
        memset((Char *)desc->loadbuf, '\0', 
               desc->attrs.loadBufSize * sizeof(desc->loadbuf[0]));
        space = COF_MEM_D;
    }
    else {
        if ((*desc->attrs.fseek)(desc->file, sectPtr->dataPtr, SEEK_SET)) {
            return (FALSE);
        }
        if ((sectPtr->flags & COF_S_COPY) != 0 
                && strcmp(".cinit", sectPtr->nameDesc.name) == 0) {
            applyCinit = TRUE;
        }
        space = getSpace(sectPtr);
    }

    addr = sectBase == NULL ? COF_offset(sectPtr->physAddr) : sectBase[sectNum];
    
#if defined(_MOT_)
    /* Handle the block special case */
    if (sectPtr->flags & COF_S_BLOCK) {
        return (doBlockSection(desc, sectPtr, addr));
    }
#endif

    wordsize = targetTab[desc->coftype].mausize;
    bufsize = desc->attrs.loadBufSize / wordsize;
    buf = desc->loadbuf;
    
    /*
     * Data must be written back out the same as it is read in,
     * so no byte swapping will be done.  With TI tools,
     * data is always in DOS-style little endian format, regardless
     * of whether the header data is byte swapped, and regardless
     * of the host operating system (e.g., SUN, DOS, or VxWorks).
     * With the Motorola tools, data is always in big endian format
     * regardless of host.
     */
    
    for (total = sectPtr->size; total > 0; total -= nwords) {
        nwords = (Int)MIN(total, bufsize);
        nbytes = nwords * wordsize;

        /* read data from COF file unless it's a bss section (assumed = 0) */
        if (!bss) {

            if ((*desc->attrs.fread)(buf, nbytes, 1, desc->file) != 1) {
                return (FALSE);
            }
        }

        /* apply relocation records to data in buf */
        if (sectPtr->nRelocs) {
            save = (*desc->attrs.ftell)(desc->file);
            if (!doReloc(desc, sectPtr, sectNum, buf, addr, nwords, sectBase)) {
                (*desc->attrs.fseek)(desc->file, save, SEEK_SET);
                return (FALSE);
            }
            (*desc->attrs.fseek)(desc->file, save, SEEK_SET);
        }
        
        /*
         * write buffer to target or, if it's a no-load .cinit section, 
         * apply records
         */
        if (applyCinit == TRUE) {
#if defined(_TI_)
            if (desc->coftype == COF_C62) {
                if (!doCinit6x(desc, desc->loadbuf, nbytes + extra, &extra)) {
                    return (FALSE);
                }
            }
            else if (targetTab[desc->coftype].wordsize == 4) {
                if (!doCinit32(desc, desc->loadbuf, nbytes + extra, &extra)) {
                    return (FALSE);
                }
            }
            else {
                if (!doCinit(desc, desc->loadbuf, nbytes + extra, &extra)) {
                    return (FALSE);
                }
            }
#endif
            buf = desc->loadbuf + extra;
            bufsize = (desc->attrs.loadBufSize - extra) / wordsize;
        }
        else {
            if (!(*desc->attrs.write)(desc->attrs.wp, addr,
                buf, (ULong)nbytes, space)) {
    
                return (FALSE);
            }
        }

        addr += nwords;
    }

    return (TRUE);
}

/*
 *  ======== COF_wordSize ========
 *
 *  Return the word size of the target processor for which the COFF file is
 *  intended.  Note that the word size that is returned is the least power
 *  of two greater than or equal to the number of 8-bit bytes in a target
 *  word. For example, the word size returned for the Motorola 24-bit
 *  processors is 4.
 */
unsigned COF_wordSize(COF_Handle desc)
{
    if (desc->coftype < TARGETTABLEN) {
        return (targetTab[desc->coftype].wordsize);
    }
    else {
        return (0);
    }
}

/*
 *  ======== COF_writeFileHeader ========
 *
 *  Writes a COFF file header to a COFF file.  Returns the number of bytes
 *  in a COFF file header.
 */
unsigned COF_writeFileHeader(FILE *file, COF_FileHdr *header, 
         Fxn fwriteFxn)
{
    (*fwriteFxn)((Char *)header, _COF_FILEHDRSIZE, 1, file);

    return((unsigned)_COF_FILEHDRSIZE);
}

/*
 *  ======== COF_writeSectHeader ========
 *
 *  Writes a COFF section header to a COFF file.  
 */
unsigned COF_writeSectHeader(FILE *file, COF_SectHdr *header, UInt size,
        Fxn fwriteFxn)
{
    (*fwriteFxn)((Char *)header, size, 1, file);

    return(size);
}

#if defined(_MOT_)
/*
 *  ======== doBlockSection ========
 */

static Bool doBlockSection(COF_Handle desc, COF_SectHdr *sectPtr, ULong addr)
{
    ULong   value;
    ULong   total;
    ULong   nwords;
    ULong   bufWords;
    ULong   *buf;
    int     i;

    /* value to initialize block is in the first word of the section */
    if ((*desc->attrs.fread)(&value, 1, sizeof(ULong), 
        desc->file) != sizeof(ULong)) {
        return (FALSE);
    }

    if (desc->byteSwapped) {
        _COF_swapLgUns(&value);
    }

    buf = (ULong *)desc->loadbuf;

    bufWords = desc->attrs.loadBufSize / sizeof(ULong);

    for (i = bufWords; i > 0; i--) {
        *buf++ = value;
    }

    /* size of the block is the virtual address */
    for (total = sectPtr->virtAddr.addr; total != 0; total -= nwords) {
        nwords = MIN(total, bufWords);

        if (!(*desc->attrs.write)(desc->attrs.wp, addr,
            desc->loadbuf, nwords * sizeof(ULong), (int)sectPtr->physAddr.map)) {

            return (FALSE);
        }

        addr += nwords;
    }

    return (TRUE);
}
#endif  /* _MOT_ */

#if defined (_TI_)
/*
 *  ======== doCinit ========
 *  Apply TI ".cinit" records contained in data to target.  Since
 *  the last record may not be complete (truncated due to finite
 *  buffering), this function will shift unused data to start of buffer
 *  and return the number of bytes remaining in the buffer (extra).
 */
static Bool doCinit(COF_Handle desc, UChar *data, Int nbytes, Int *extra)
{
    struct Record {UShort count; UShort addr;} *record;
    UShort bufsize, nwords;
    ULong remain, addr;
    UChar *buf = data;
    
    remain = nbytes;
    nwords = 0;
    
    /* apply .cinit records until we reach a partial record */
    while (remain > sizeof(struct Record)) {
        
        record = (struct Record *)buf;
        buf += sizeof(struct Record);
        remain -= sizeof(struct Record);

        if (desc->byteSwapped) {          /* ~~~ IS THIS THE RIGHT TEST ??? */
            /* byte swap record if host and target are different endians */
            _COF_swapMdUns(&record->count);
            _COF_swapMdUns(&record->addr);
        }

        /* if record->count == 0, we're at the end of the .cinit section */
        if (record->count == 0) {
            break;
        }

        /* otherwise, we should write as much as possible to target */
        addr = record->addr;
        bufsize = record->count * targetTab[desc->coftype].mausize;
        if (remain < bufsize) {
            nwords = (UShort)(remain / targetTab[desc->coftype].mausize);
            bufsize = (UShort)remain;
        }

        /* write data to target */
        if ((*desc->attrs.write)(desc->attrs.wp, addr, buf, bufsize, COF_MEM_D)
                != bufsize) {
            return (FALSE);
        }

        /* update buf pointer and remain count to reflect write to target */
        buf += bufsize;
        remain -= bufsize;
    }

    /* set extra to number of bytes spanned by any initial partial record */
    if (record->count == 0) {   /* end of .cinit reached */
        *extra = 0;
    }
    else if (remain == 0) {     
        if (nwords != 0) {  /* the data buffer split a .cinit record's data */
            *extra = sizeof(struct Record);
            ((struct Record *)data)->count = record->count - nwords;
            ((struct Record *)data)->addr = record->addr + nwords;
        }
        else {              /* completed entire .cinit record */
            *extra = 0;
        }
    }
    else {                  /* the data buffer split a record structure */
        memcpy((Char *)data, (Char *)buf, (size_t)remain);
        *extra = (size_t)remain;
    }
    
    return (TRUE);
}
#endif                  /* #if defined (_TI_) */


#if defined(_TI_)
/*
 *  ======== doCinit32 ========
 *  Apply TI ".cinit" records contained in data to target.  Since
 *  the last record may not be complete (truncated due to finite
 *  buffering), this function will shift unused data to start of buffer
 *  and return the number of bytes remaining in the buffer (extra).
 */
static Bool doCinit32(COF_Handle desc, UChar *data, Int nbytes, Int *extra)
{
    struct Record {ULong count; ULong addr;} *record;
    ULong bufsize, nwords, remain;
    ULong addr;
    UChar *buf = data;
   
    remain = nbytes;
    nwords = 0;
   
    /* apply .cinit records until we reach a partial record */
    while (remain > sizeof(struct Record)) {
 
        record = (struct Record *)buf;
        buf += sizeof(struct Record);
        remain -= sizeof(struct Record);
 
        if (desc->byteSwapped) {          /* ~~~ IS THIS THE RIGHT TEST ??? */
            /* byte swap record if host and target are different endians */
            _COF_swapLgUns(&record->count);
            _COF_swapLgUns(&record->addr);
        }
 
        /* if record->count == 0, we're at the end of the .cinit section */
        if (record->count == 0) {
            break;
        }
 
        /* otherwise, we should write as much as possible to target */
        addr = record->addr;
        bufsize = record->count * targetTab[desc->coftype].mausize;
        if (remain < bufsize) {
            nwords = remain / targetTab[desc->coftype].mausize;
            bufsize = remain;
        }
 
        /* write data to target */
        if ((*desc->attrs.write)(desc->attrs.wp, addr, buf, bufsize, COF_MEM_D)
                != bufsize) {
            return (FALSE);
        }
 
        /* update buf pointer and remain count to reflect write to target */
        buf += bufsize;
        remain -= bufsize;
    }

    /* set extra to number of bytes spanned by any initial partial record */
    if (record->count == 0) {   /* end of .cinit reached */
        *extra = 0;
    }
    else if (remain == 0) {
        if (nwords != 0) {  /* the data buffer split a .cinit record's data */
            *extra = sizeof(struct Record);
            ((struct Record *)data)->count = record->count - nwords;
            ((struct Record *)data)->addr = record->addr + nwords;
        }
        else {              /* completed entire .cinit record */
            *extra = 0;
        }
    }
    else {                  /* the data buffer split a record structure */
        memcpy((Char *)data, (Char *)buf, (size_t)remain);
        *extra = (size_t)remain;
    }
 
    return (TRUE);
}
#endif          /* _TI_ */


#if defined(_TI_)
/*
 *  ======== doCinit6x ========
 *  Apply TI ".cinit" records contained in data to target.  Since
 *  the last record may not be complete (truncated due to finite
 *  buffering), this function will shift unused data to start of buffer
 *  and return the number of bytes remaining in the buffer (extra).
 */
static Bool doCinit6x(COF_Handle desc, UChar *data, Int nbytes, Int *extra)
{
    struct Record {ULong count; ULong addr;} *record;
    ULong bufsize, nwords, remain;
    ULong buf_adj = 0;
    ULong addr;
    UChar *buf_start = data;
    UChar *buf = data;

    remain = nbytes;
    nwords = 0;

    /* apply .cinit records until we reach a partial record */
    while (remain > sizeof(struct Record)) {
        
        record = (struct Record *)buf;
        buf += sizeof(struct Record);
        remain -= sizeof(struct Record);

        /* if record->count == 0, we're at the end of the .cinit section */
        if (record->count == 0) {
            break;
        }

        /* otherwise, we should write as much as possible to target */
        addr = record->addr;
        bufsize = record->count * targetTab[desc->coftype].mausize;

        if (remain < bufsize) {
            nwords = remain / targetTab[desc->coftype].mausize;
            bufsize = remain;
        }

        /* write data to target */
        if (!(*desc->attrs.write)(desc->attrs.wp, addr, buf, bufsize, 
            COF_MEM_D)) {
            return (FALSE);
        }

        /* update buf pointer and remain count to reflect write to target */
        buf += bufsize;
        remain -= bufsize;

        /* if needed, adjust buf pointer per C6x cinit record alignment rules */
        if (buf_adj = ((buf - buf_start) & (COF_C6XALIGN - 1))) {
            buf_adj = COF_C6XALIGN - buf_adj; 
            buf = buf + buf_adj;
            remain = remain - buf_adj;
        }
    }

    /* set extra to number of bytes spanned by any initial partial record */
    if (record->count == 0) {   /* end of .cinit reached */
        *extra = 0;
    }
    else if (remain == 0) {     
        if (nwords != 0) {  /* the data buffer split a .cinit record's data */
            *extra = sizeof(struct Record);
            ((struct Record *)data)->count = record->count - nwords;
            ((struct Record *)data)->addr = record->addr + nwords;
        }
        else {              /* completed entire .cinit record */
            *extra = 0;
        }
    }
    else {                  /* the data buffer split a record structure */
        memcpy((Char *)data, (Char *)buf, (size_t)remain);
        *extra = (size_t)remain;
    }
    
    return (TRUE);
}
#endif          /* _TI_ */

/*
 *  ======== doReloc ========
 *  Apply all relocation entries that are relevant to the address range
 *  [addr, addr + nwords - 1] to the data in the buffer buf.
 */
static Bool doReloc(COF_Handle desc, COF_SectHdr *sectPtr, Int sectNum, UChar *buf,
                    ULong addr, Int nwords, ULong sectBase[])
{
    COF_Reloc   reloc;
    COF_Symbol  symbol;
    Char        name[COF_MAXEXPR];
    Ptr        *valPtr;
    ULong       raddr;
    ULong       base;
    ULong       value;
    Int         bytesize;

    bytesize = targetTab[desc->coftype].mausize;

    /* start the scan of relocation entries for this section */

    if (COF_scanReloc(desc, sectNum) == 0) {
        return (TRUE);
    }

    if
#if defined (_TI_)
        (desc->coftype != COF_C50)
#else
        (1)
#endif  
        {
        return (FALSE);
    }

    /* apply relocation expressions to the section */
    
    while (COF_nextReloc(desc, &reloc, &symbol, name) == COF_EOK) {

        /* compute relocation physical address */
        raddr = (reloc.r_vaddr - COF_offset(sectPtr->physAddr)) + 
                sectBase[sectNum];

#if defined(_TI_)
        /*
         *  if relocation address is outside buffer range, skip it
         *  TI COFF relocation info is sorted in increasing addresses
         */
        if (raddr < addr) {
            continue;
        }
        else if (raddr >= (addr + nwords)) {
            break;
        }
#elif defined(_MOT_)
        /* if relocation address is outside buffer range, skip it */
        if (raddr < addr || raddr >= (addr + nwords)) {
            continue;
        }
#endif

        /* get word in buf that's the target of reloc */

        valPtr = (Ptr)(buf + ((raddr - addr) * bytesize));

        if (4 == bytesize) {
            value = *(ULong*)valPtr;
        }
        else if (2 == bytesize) {
            value = (ULong)(*(UShort*)valPtr);
        }
        else {
            return(FALSE);
        }

#if defined(gnu_targets_Sparc) || defined(_VXWORKS_)

        /* IS THIS TI-SPECIFIC? */

        _COF_swapLgUns(&value);

        if (2 == bytesize) {
            value >>= 16;
        }
#endif

#if defined(_TI_)
        /*
         *  Note: the relocation information is derived from code in cload.c
         *  (which was downloaded from the TI bulltetin board) and looking at
         *  the fields in the instruction set.
         *
         *  Apply relocation record reloc to value.
         *
         *  If r_symndx == -1, the relocation is relative to the start of
         *  the current section (sectNum); otherwise the relocation
         *  amount is determined by the symbol referenced by r_symndx.
         *
         *  If the symbol's section number is 0 (i.e. the symbol is undefined),
         *  it must be defined by a previously loaded file.  If it's > 0, the
         *  symbol is defined within the current COF file, and the relocation
         *  is relative to base of the section defining the symbol.
         *
         *  The relocation type (r_type) should be COF_R_RELWORD for all 
         *  relocation entries that have r_symndx == -1.
         */
        if (reloc.r_symndx >= 0) {
            if (symbol.sectNum > 0) {       /* sym defined in this file */
                base = sectBase[symbol.sectNum] - sectPtr->physAddr;
            }
            else if (symbol.sectNum == 0) { /* undefined symbol */
                /* call back to client to lookup value for symbol */
                if (desc->attrs.lookup == NULL
                    || (*desc->attrs.lookup)(desc->attrs.lp, name, &symbol,
                                             (ULong *)&base) == FALSE) {
                    return (FALSE); 
                }
            }
            else {
                return (FALSE);             /* bogus symbol section number */
            }
        }
        else if (reloc.r_symndx == -1) {    /* use current section base */
            base = sectBase[sectNum] - sectPtr->physAddr;

            /* .cinit is not allocated on the DSP! */
            if (strcmp(".cinit", sectPtr->nameDesc.name) == 0) {
                return(FALSE);              /* bogus relocation entry! */
            }
        }
        else {
            return (FALSE);                 /* bogus symbol table index! */
        }
    
        switch (reloc.r_type) {

            case COF_R_RELWORD:/* normal relocations: add the reloc amount */
            case COF_R_RELBYTE:
            case COF_R_REL24:
            case COF_R_RELLONG:
            case COF_R_PARTLS16:
                value += (COF_Uns) base; 
                break;
    
            case COF_R_PARTLS7:     /* DSP: 7 bit offset of 16 bit address */
                /* BUG ????, cload.c says "(value & 0x80) | ..." */
                value = (value & 0xFF80) 
                         | ((UShort)(reloc.r_disp + base) & 0x7F);
                break;
    
            case COF_R_PARTMS9:     /* DSP: 9 bit offset of 16 bit address */
                value = (value & 0xFE00) 
                        | ((UShort)(((ULong)reloc.r_disp + base) >> 7) & 0x1FF);
                break;
    
            case COF_R_REL13:                      /* DSP: 13 bits, direct */
                value = (value & 0xE000) | ((value + (UShort)base) & 0x1FFF);
                break;
    
            default:
                return (FALSE);     /* OOOPS! Don't know how to handle this */
        }
#elif defined(_MOT_)
        /*
         *  Apply relocation record reloc to value
         */
        /* call back to client to lookup value for symbol */
        base = sectBase[sectNum];   /* pass section base to lookup function */
        if (desc->attrs.lookup == NULL
            || (*desc->attrs.lookup)(desc->attrs.lp, name, &symbol, &base) 
               == FALSE) {
            return (FALSE); 
        }

        /* do relocation here */
        value = base;
#endif

#if defined(gnu_targets_Sparc) || defined(_VXWORKS_)

        /* IS THIS TI-SPECIFIC?  NECESSARY? */

        if (2 == bytesize) {
            value <<= 16;   /* Get bits in right position for swapping. */
        }

        _COF_swapLgUns(&value);

#endif
        /* Store word in buf that's the target of reloc. */

        if (4 == bytesize) {
            *(ULong*)valPtr = value;
        }
        else {            /* From previous test we know bytesize is 2 or 4 */
            *(UShort*)valPtr = (UShort)value;
        }
    }
    return (TRUE);
}

/*
 *  ======== getFileMagic ========
 *
 *  Get the "magic" number from the COFF file, without byte-swapping the
 *  value.  Check to see if the COFF file is a new or old format file, and
 *  appropriately assign the version and magic fields in the file header.
 */
static COF_Uns getFileMagic(COF_Handle desc)
{
    COF_Uns magic;
    COF_Uns version;

    /*
     * Modified to handle new COFF format as well as old; 1st word is COFF
     * version, header has additional word (at end of structure) for target ID.
     */
    version = desc->header.version;

    /*
     * Default case:  assume old version, and the "version" field is really
     * the magic number.  Make the assignment now, since "version" could get
     * byte-swapped below.
     */

    magic = version;

    if (version == COF_VER0MAGIC || version == COF_VER1MAGIC
            || version == COF_VER2MAGIC) {
        (*desc->attrs.fread)((Char *)&magic, sizeof (magic), 1, desc->file);
        desc->sectHdrOffset += sizeof(magic);
    }
    else if (_COF_swapUns(&version), 
             version == COF_VER0MAGIC || version == COF_VER1MAGIC
            || version == COF_VER2MAGIC) {
        (*desc->attrs.fread)((Char*)&magic, sizeof (magic), 1, desc->file);
        desc->sectHdrOffset += sizeof(magic);
    }
    else {
        desc->header.version = 0;    /* old format - clear out version field */
    }

    desc->header.magic = magic;      /* either way, fill in magic field */

    return (magic);
}

/*
 *  ======== getHeaders ========
 *
 *  Get the file and section headers from the COFF file, and byte-swap the
 *  data if necessary to match the "endian" of the host processor.  
 */
static Int getHeaders(COF_Handle desc)
{
    Void    *file = desc->file;
    COF_Uns magic, fileMagic;

    /*
     * In case we're reading an old-format TI COFF file, don't read in
     * the header.magic field now; wait 'til we see whether it's there.
     */

    if (!(*desc->attrs.fread)(&desc->header, (Int)_COF_OLDHDRSIZE, 1, file)) {
        return (COF_EHEADER);
    }

    /*
     * Assume for now that we're reading an old format COFF file, so the offset
     * to the section headers is not fully the size of COF_FileHdr, since
     * COF_FileHdr's last field is "magic", which isn't used in the old format.
     */
    
    desc->sectHdrOffset = (Long)_COF_OLDHDRSIZE;
    
    fileMagic = getFileMagic(desc);
    if (desc->coftype == COF_UNKNOWN) {
        desc->coftype = magic2type(desc, fileMagic);
    }
    magic = targetTab[desc->coftype].magic;
    if (fileMagic != magic) {
        _COF_swapUns(&fileMagic);

        if (fileMagic != magic) {
            return (COF_EMAGIC);
        }

        desc->byteSwapped = TRUE;

        _COF_swapUns(&desc->header.version);
        _COF_swapUns(&desc->header.nSects);
        _COF_swapLong(&desc->header.date);
        _COF_swapLong(&desc->header.symTabPtr);
        _COF_swapLong(&desc->header.nSyms);
        _COF_swapUns(&desc->header.optHdrSize);
        _COF_swapUns(&desc->header.flags);
        _COF_swapUns(&desc->header.magic);
    }

    /* read optional header */
    if (desc->header.optHdrSize == sizeof(COF_OptHdr)) {
        if ((*desc->attrs.fread)(&desc->optHeader,
                              (size_t)desc->header.optHdrSize, 1, file) != 1) {
            return (COF_EOHEADER);
        }

        if (desc->byteSwapped) {
            _COF_swapInt(&desc->optHeader.magic);
            _COF_swapInt(&desc->optHeader.vers);
            _COF_swapSize(&desc->optHeader.textSize);
            _COF_swapSize(&desc->optHeader.dataSize);
            _COF_swapSize(&desc->optHeader.bssSize);
            _COF_swapAddr(&desc->optHeader.entryPoint);
            _COF_swapAddr(&desc->optHeader.textAddr);
            _COF_swapAddr(&desc->optHeader.dataAddr);
#if defined(_MOT_)
            _COF_swapAddr(&desc->optHeader.textEnd);
            _COF_swapAddr(&desc->optHeader.dataEnd);
#endif
        }
    }
    else {
        memset((char *)&desc->optHeader, 0, sizeof(COF_OptHdr));
        
        if (desc->header.optHdrSize == sizeof(COF_LinkHdr)) {
            if ((*desc->attrs.fread)(&desc->linkHeader,
                    (size_t)desc->header.optHdrSize, 1, file) != 1) {
                return (COF_EOHEADER);
            }
        }

        else {
            memset((char *)&desc->linkHeader, 0, sizeof(COF_OptHdr));
        }
    }
    
    desc->sectHdrOffset += (Long)desc->header.optHdrSize;
    
    /*
     * In the TI world we'll read in all section headers all at one time. In
     * the Motorola world there are too many section to read the headers all
     * at once, so we'll just read _COF_NHDRS of them at a time.
     */
    
#if defined(_TI_)
    desc->numCurSects = desc->header.nSects;
#elif defined(_MOT_)
    desc->numCurSects = _COF_NHDRS;
#endif

    if (desc->sectHdrs != NULL) {
        frees(desc->sectHdrs, (size_t)desc->numCurSects
                * sizeof(COF_SectHdr));
        desc->sectHdrs = NULL;
    }

    /* allocate space for section headers and read them in */

    desc->sectHdrs = (COF_SectHdr *)malloc((size_t)desc->numCurSects *
                                             sizeof(COF_SectHdr));

    if (desc->sectHdrs == NULL) {
        return (COF_ESHEADER);
    }

    /* read in a block of section headers */

    return (getSectHdrs(desc, 1));
}

/*
 *  ======== getSectHdrs ========
 *
 *  Read in a block of section headers, starting with the section header
 *  indicated by the paramater, "base".  This capability is provided to
 *  support COFF files that have a large number of section headers (e.g.,
 *  Motorola) but works equally well with files that have only a small
 *  number of section headers.  The convention is that the first section
 *  header is numbered "1" rather than "0", so an adjustment has to be made
 *  to "base" to get the correct offset.
 */
static Int getSectHdrs(COF_Handle desc, Int base)
{
    Int         nhdrs;
    Long        offset;
    Int         i;
    Int         version;

    COF_SectHdr *sectPtr;

    Short mnRelocs;     /* smaller fields for version 1 or 0 */
    Short mnLines;
    Short mflags;

#if defined(_MOT_)
    Bool isMot = TRUE;
#elif defined(_TI_)
    Char sdummy;
    Char spageNum;
    Bool isMot = FALSE;
#endif
    
    Bool swap = desc->byteSwapped;
    Void* file = desc->file;

    /* section numbers are 1-based. */

    if (base < 1 || base > (Int)desc->header.nSects) {
        return (COF_ESHEADER);
    }
    
    /* compute the actual number of headers to read into memory */

    nhdrs = desc->header.nSects - (base - 1);
    if (nhdrs > desc->numCurSects) {
        nhdrs = desc->numCurSects;
    }

    switch (desc->header.version) {
        case COF_VER0MAGIC:
            version = 0;
            break;
        case COF_VER1MAGIC:
            version = 1;
            break;
        case COF_VER2MAGIC:
            version = 2;
            break;
        default:
            version = 2;
    }

    offset = desc->sectHdrOffset
            + (Long)(base - 1) * (Long)sectHdrSize(version);
    if ((*desc->attrs.fseek)(desc->file, offset, SEEK_SET) == -1) {

        return (COF_ESHEADER);
    }

    for (i = 0, sectPtr = desc->sectHdrs; i++ < nhdrs; sectPtr++) {
        if (desc->attrs.fread(sectPtr->nameDesc.name, COF_NAMELEN, 1, file)
                != 1) {
            return (FALSE);
        }

        /* don't swap the name field if it's a string */
        if (swap && sectPtr->nameDesc.stringPtr.immedFlag == 0) {
            _COF_swapPtr(&sectPtr->nameDesc.stringPtr.ptr);
        }
        
        readAddrAt (&sectPtr->physAddr, file, swap, desc->attrs.fread);
        readAddrAt (&sectPtr->virtAddr, file, swap, desc->attrs.fread);
        readDatumAt(&sectPtr->size, file, swap, desc->attrs.fread);
        readDatumAt(&sectPtr->dataPtr, file, swap, desc->attrs.fread);
        readDatumAt(&sectPtr->relocPtr, file, swap, desc->attrs.fread);
        readDatumAt(&sectPtr->linePtr, file, swap, desc->attrs.fread);
        if (desc->header.version == COF_VER2MAGIC || isMot) {
            readDatumAt(&sectPtr->nRelocs, file, swap, desc->attrs.fread);
            readDatumAt(&sectPtr->nLines, file, swap, desc->attrs.fread);
            readDatumAt(&sectPtr->flags, file, swap, desc->attrs.fread);
#if defined(_TI_)
            readDatumAt(&sectPtr->dummy, file, swap, desc->attrs.fread);
            readDatumAt(&sectPtr->pageNum, file, swap, desc->attrs.fread);
#endif
        }
        else {

        /* TI Version 1 or 0: smaller fields; copy into large parameters. */
            
            readDatumAt(&mnRelocs, file, swap, desc->attrs.fread);
            readDatumAt(&mnLines, file, swap, desc->attrs.fread);
            readDatumAt(&mflags, file, swap, desc->attrs.fread);
#if defined(_TI_)
            readDatumAt(&sdummy, file, swap, desc->attrs.fread);
            readDatumAt(&spageNum, file, swap, desc->attrs.fread);
            /* ignore 'dummy' */
            sectPtr->pageNum = spageNum;
#endif
            sectPtr->nRelocs = mnRelocs;
            sectPtr->nLines = mnLines;
            sectPtr->flags = mflags;
        }
    }

    desc->sectHdrBase = base;
    
    return (COF_EOK);
}

/*
 *  ======== getSpace ========
 *
 *  Return the memory space indicated by the given section header.
 */
static Int getSpace(COF_SectHdr *sect)
{
#if defined(_TI_)
    if (sect->pageNum == 0) {   /* page 0 is P memory for C5x! */
        return (COF_MEM_P);
    }

    return (COF_MEM_D);
#elif defined(_MOT_)
    return ((Int) sect->physAddr.map);
#endif
}

#if 0
/*
 *  ======== od ========
 */
static Void od(ULong start, Char *buffer, Int nbytes, Int mausize)
{
    Int i;
    ULong mau;
    
    for (i = 0; i < (Int)(nbytes / mausize); i++) {
        if ((i % 4) == 0) {
            printf("0x%.4x(0x%.4x): ", start, start / 2);
            start += 4;
        }

        switch (mausize) {
            case 1: {
                mau = *buffer++;
                printf("0x%.2x ", mau);
                break;
            }
            case 2: {
                mau = *(UShort *)buffer;
                buffer += sizeof(UShort);
                printf("0x%.4x ", mau);
                break;
            }
            case 4: {
                mau = *(ULong *)buffer;
                buffer += sizeof(ULong);
                printf("0x%.8x ", mau);
                break;
            }
            default: {
                fprintf(stderr, "unknown mau size %d.\n", mausize);
                exit (1);
            }
        }

        if ((i % 4) == 3) {
            printf("\n");
        }
    }
    printf("\n");
}
#endif

/*
 *  ======== loadArgs ========
 */
static Int loadArgs(COF_Handle desc, Bool cgFormat,
    ULong argsAddr, ULong argsSize,
    Int argc, Char *argv[], Char *envp[])
{
    Int         envc;
    unsigned    mausize = targetTab[desc->coftype].mausize;
    unsigned    charsize = targetTab[desc->coftype].charsize;
    unsigned    ptrsize = targetTab[desc->coftype].ptrsize;
    unsigned    packetSize;
    unsigned    nbytes;
    unsigned    bufsize;
    ULong       argsByteAddr = argsAddr;
    Char        *argbuf;
    Int         i;
    ULong       total;
    
    /* compute envc: the number of environment variables */
    envc = 0;
    if (envp != NULL) {
        while (envp[envc]) {
            envc++;
        }
    }

#if defined(_TI_)
    /*
     *  Need to cut the argsAddr in half for C55.  The C55 uses byte addresses
     *  for program memory but word addresses for data memory; argAddr is
     *  a byte address but we want to fill data memory.
     */
    if (desc->coftype == COF_C55 || desc->coftype == COF_C55L) {
        argsAddr /= 2;
    }
#endif

    /*
     *  Compute total target buffer size required (in host bytes)
     */

    /* 3 words for argc, argv, and envp; one per argv and env + NULL term */
    total = (3 + argc + 1 + envc + 1) * ptrsize;
    for (i = 0; i < argc; i++) {    /* space argv strings */
        total += (strlen(argv[i]) + 1) * charsize;
    }
    for (i = 0; i < envc; i++) {    /* space for envp strings */
        total += (strlen(envp[i]) + 1) * charsize;
    }
    if (charsize > 1) {        /* round total to even number of target chars */
        total = charsize * ((total + charsize - 1) / charsize);
    }

    /*
     *  if .args section is too small, return error. Note that argSize is
     *  in bytes for C55x, even though this is data. Therefore we must use
     *  mausize in the computation below, not charsize.
     */
    if ((argsSize * mausize) < total) {
        return (COF_EARGS);
    }

    /* allocate a host buffer to build an image of the target's args buffer */
    if ((argbuf = calloc((size_t)argsSize * charsize, 1)) == NULL) {
        return (COF_EMEM);
    }

    /* create target .args image */
    bufsize = fillArgs(desc, cgFormat,
        argsAddr, argc, argv, envc, envp, argbuf);

    if (charsize > 1) {        /* round total to even number of target chars */
        bufsize = charsize * ((bufsize + charsize - 1) / charsize);
    }

    /* od(argsByteAddr, argbuf, bufsize, mausize); */

    argsByteAddr = argsAddr;
    
    for (nbytes = 0; nbytes < bufsize; nbytes += packetSize) {
        packetSize = MIN(desc->attrs.loadBufSize, (bufsize - nbytes));
        
        (*desc->attrs.write)(desc->attrs.wp, argsByteAddr, 
                             (UChar *)(argbuf + nbytes),
                             (long unsigned)packetSize, COF_MEM_D);

        argsByteAddr += packetSize / charsize;
    }

    /* free local arg buffer and return */
    frees(argbuf, (size_t)argsSize * charsize);

    return (COF_EOK);
}

/*
 *  ======== fillArgs ========
 *  argbuf - host buffer conatining bit to be downloaded
 */
static UInt fillArgs(COF_Handle desc, Bool cgFormat,
    ULong argsAddr, Int argc, String argv[], Int envc, String envp[],
    Char *argbuf)
{
    unsigned    charsize = targetTab[desc->coftype].charsize;
    unsigned    ptrsize = targetTab[desc->coftype].ptrsize;
    char        *bufp;
    Char        *src;
    
    if (ptrsize == 2) {
        UShort    *bufptr;
        UShort    *argvp, *envpp;

        /* fill in the argbuf array with contents of .args section */
        bufptr = (UShort *)argbuf;
        *bufptr++ = (UShort)argc;   /* argc */
        if (!cgFormat) {
            *bufptr++ = (UShort)argsAddr + 3;     /* &argv, ending with 0 */
            *bufptr++ = (UShort)argsAddr + argc + 4;  /* &envp */
        }

        argvp = bufptr;             /* set start address of argv array */
        bufptr += argc + 1;         /* reserve space for argv array */

        if (cgFormat) {
            *bufptr++ = (UShort)envc;   /* envc */
        }
        envpp = bufptr;             /* set start address of envp array */
        bufptr += envc + 1;         /* reserve space for envp array */

        /* fill in argv array and the strings that it refers to */
        for (; argc > 0; argc--) {
            *argvp++ = (UShort)(bufptr - (UShort *)argbuf)+(UShort)argsAddr;
            src = *argv++;

            while ((*bufptr++ = (UShort)*src++) != 0) {
                ;
            }
        }
        *argvp = 0;     /* NULL terminiate argv[] */

        /* fill in the envp array and the strings it refers to */
        for (; envc > 0; envc--) {
            *envpp++ = (UShort)(bufptr - (UShort *)argbuf)+(UShort)argsAddr;
            src = *envp++;
            
            while ((*bufptr++ = (UShort)*src++) != 0) {
                ;
            }
        }
        *envpp = 0;     /* NULL terminiate envp[] */

        bufp = (char *)bufptr;  /* save end to compute bufsize below */

        /* byte/word swap as necessary before writing argbuf to target */
#if defined(gnu_targets_Sparc) || defined(_VXWORKS_)
        {
            UShort *tbufp;

            for (tbufp = (UShort *)argbuf; tbufp < bufptr; tbufp++) {
                _COF_swapMdUns(tbufp);
            }
        }
#endif
    }
    
    /* ptrsize == 4 */
    else {
        ULong   *bufptr;
        ULong   *argvp, *envpp;
        ULong   tpinc = ptrsize / charsize; /* targ pointer increment */
        
        /* fill in the argbuf array with contents of .args section */
        bufptr = (ULong *)argbuf;
        *bufptr++ = argc;           /* argc (should be copyInt()!) */
        if (!cgFormat) {
            bufptr = copyLongPtr(
                argsAddr + 3 * tpinc,           /* &argv, ending with 0 */
                desc->coftype, bufptr);
            bufptr = copyLongPtr(
                argsAddr + (argc + 4) * tpinc,  /* &envp, ending with 0 */
                desc->coftype, bufptr);
        }

        argvp = bufptr;             /* set start address of argv array */
        bufptr += argc + 1;         /* reserve space for argv array */

        if (cgFormat) {
            *bufptr++ = envc;       /* envc (should be copyInt()!)*/
        }
        envpp = bufptr;             /* set start address of envp array */
        bufptr += envc + 1;         /* reserve space for envp array */

        /* fill in argv array and the strings that it refers to */
        for (; argc > 0; argc--) {
            argvp = copyLongPtr(
                (ULong)((Char *)bufptr - argbuf) / charsize + argsAddr,
                desc->coftype, argvp);

            /* copy argv[] string to bufptr and advance bufptr */
            bufptr = (ULong *)copyString((Char *)bufptr, *argv++, charsize);
        }
        *argvp = 0L;     /* NULL terminiate argv[] */

        /* fill in the envp array and the strings it refers to */
        for (; envc > 0; envc--) {
            envpp = copyLongPtr(
                (ULong)((Char *)bufptr - argbuf) / charsize + argsAddr,
                desc->coftype, envpp);

            /* copy envp[] string to bufptr and advance bufptr */
            bufptr = (ULong *)copyString((Char *)bufptr, *envp++, charsize);
        }
        *envpp = 0L;     /* NULL terminiate envp[] */

        bufp = (char *)bufptr;  /* save end to compute bufsize below */

        /* byte/word swap as necessary before writing argbuf to target */
#if defined(gnu_targets_Sparc) || defined(_VXWORKS_)
        {
            ULong *tbufp;

            for (tbufp = (ULong *)argbuf; tbufp < bufptr; tbufp++) {
                _COF_swapLgUns(tbufp);
            }
        }
#endif
    }
    
    /* return buffer size in bytes */
    return ((unsigned)(bufp - argbuf));
}

/*
 *  ======== magic2type ========
 *  Make best guess about what the COF type is based on the
 *  magic number supplied.
 */
static Int magic2type(COF_Handle desc, COF_Uns magic)
{
    COF_Uns swapm = magic;
    Target *tp;

    _COF_swapUns(&swapm);
    
    for (tp = targetTab + TARGETTABLEN - 1; tp >= targetTab; tp--) {
        if (tp->magic == magic || tp->magic == swapm) {

#if defined _TI_
            COF_Uns flags = desc->header.flags;
            if (tp->magic == swapm) {
                _COF_swapUns(&flags);
            }
            
            /*
             *  Needed since both byte mode and word mode Ryujin (56)
             *  have the same magic number
             */
            if (tp->magic == COF_C56MAGIC) {
                /* byte mode if f_vers1 bit set */
                if (flags & COF_F_VERS1) {
                    return (COF_C56B);
                }
                else {
                    return (COF_C56W);
                }
            }
            else if (tp->magic == COF_C55MAGIC) {
                /*  Warning!!! HACK!!! This test was determined by reverse
                 *  engineering the COFF file header and may be wrong.
                 */
                if ((flags & 0xf0) == 0xe0) {
                    return (COF_C55L);
                }
                else {
                    return (COF_C55);
                }
            }
            else {
                return (tp - targetTab);
            }
#else
            return (tp - targetTab);
#endif
        }
    }

    /* can't guess from the magic number, so return arbitrary choice */
#if defined (_TI_)
    return (COF_C30);
#elif defined (_MOT_)
    return (COF_56K);
#else
    return (COF_UNKNOWN);
#endif    
}

/*
 *  ======== nop ========
 *
 *  This function matches the prototype for the write function assigned
 *  to the "write" field of the attrs structure, but does nothing.  This
 *  allows COF_create() to be called without a real write function.
 */
static ULong nop(void * p, ULong addr, void * data, ULong nbytes, Int mtype)
{
    _COF_USEARG(p);
    _COF_USEARG(addr);
    _COF_USEARG(data);
    _COF_USEARG(nbytes);
    _COF_USEARG(mtype);
    return (1);
}


#define SWAP_LONG(x) ((((x) << 24) & 0xFF000000) | (((x) << 8) & 0xFF0000L) | \
                      (((x) >> 8) & 0xFF00L) | (((x) >> 24) & 0xFF))

#define SWAP_LWORD(x)  ( (((x) << 16) & 0xFFFF0000) | (((x) >> 16) & 0xFFFFL) )

#define SWAP_WORD(x) ((((x) << 8) & 0xFF00) | (((x) >> 8) & 0xFF))

/*
 *  ======== copyLongPtr ========
 */
static ULong *copyLongPtr(ULong targPtr, Int cofType, ULong *hostBuf)
{
#if defined(_TI_)
    *hostBuf = (cofType == COF_C55L) ? SWAP_LWORD(targPtr) : targPtr;
#else
    *hostBuf = targPtr;
#endif

    return (hostBuf + 1);
}

/*
 *  ======== copyString ========
 */
static Char *copyString(Char *dst, Char *src, Int charsize)
{
#if 1   /* this works on Linux/Windows machines for C55 and C55L */
    /* copy string to dst */
    while (*src != '\0') {
        *dst = *src++;
        dst += charsize;
    }

    /* NULL terminate dst */
    *dst = '\0';
    dst += charsize;
#else   /* this works on ??? */
    /* copy string to dst */
    while (*src != '\0') {
        *(dst + charsize - 1) = *src++;
        dst += charsize;
    }

    /* NULL terminate dst */
    *(dst + charsize - 1) = '\0';
    dst += charsize;
#endif
    return (dst);
}

/*
 *  ======== _COF_swapMdInt ========
 *  Swap the order of bytes in a Short (signed short)
 */
Void _COF_swapMdInt(Short *addr)
{
    UShort word = *addr;
    
    *addr = SWAP_WORD(word);
}

/*
 *  ======== _COF_swapMdUns ========
 *  Swap the order of bytes in a UShort (unsigned short)
 */
Void _COF_swapMdUns(UShort *addr)
{
    UShort word = *addr;
    
    *addr = SWAP_WORD(word);
}

/*
 *  ======== _COF_swapLgInt ========
 *  Swap the order of bytes in a Long (signed long)
 */
Void _COF_swapLgInt(Long *addr)
{
    ULong   word = *addr;
    
    *addr = SWAP_LONG(word);
}

/*
 *  ======== _COF_swapLgUns ========
 *  Swap the order of bytes in a ULong (unsigned long)
 */
Void _COF_swapLgUns(ULong *addr)
{
    ULong   word = *addr;
    
    *addr = SWAP_LONG(word);
}

/*
 *  ======== COF_readSect ========
 *
 *  Read a section's data from the COFF file into the buffer pointed to
 *  by the "buf" parameter.
 */
Bool COF_readSect(COF_Handle desc, COF_SectHdr *sectPtr,  void *buf, int nmaus)
{
    unsigned mausize;

    mausize = COF_byteSize(desc);

    if ((*desc->attrs.fseek)(desc->file, sectPtr->dataPtr, SEEK_SET)) {
        return (FALSE);
    }

    if ((*desc->attrs.fread)(buf, mausize, nmaus, desc->file) != nmaus) {
        return (FALSE);
    }

    return (TRUE);
}

/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 10-21-2016 18:37:04; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

