/*
 *  Copyright 2016 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== cof.h ========
 *
 *  Motorola and TI DSP COFF support.
 *
 */

#ifndef COF_
#  define COF_

#  include <stddef.h>
#  include <xdc/std.h>
#  include <stdio.h>

/* chip types - BEWARE! These definitions must match targetTab in cof.c */

#  define COF_UNKNOWN   -1

#  if defined _TI_

#    define COF_C30     0
#    define COF_C40     1
#    define COF_C50     2
#    define COF_C54     3
#    define COF_C62     4
#    define COF_C80     5
#    define COF_C55     6
#    define COF_C28     7
#    define COF_C56B    8
#    define COF_C56W    9
#    define COF_ARM     10
#    define COF_C55L    11
#    define COF_C430    12

#  elif defined _MOT_

#    define COF_56K     0
#    define COF_561C    1
#    define COF_563C    2
#    define COF_96K     3

#  endif

#  define COF_MAXEXPR     128

/*
 *  TI separates program code and data into separate memory spaces.
 *  COF_Addr structure defines a Motorola DSP address that reflects
 *  the Harvard architecture of the 56K and 96K processors.
 */

#  define COF_MEM_P       0               /* Program (code) */
#  define COF_MEM_X       1
#  define COF_MEM_Y       2
#  define COF_MEM_L       3
#  define COF_MEM_NONE    4
#  define COF_MEM_LAA     5
#  define COF_MEM_LAB     6
#  define COF_MEM_LBA     7
#  define COF_MEM_LBB     8
#  define COF_MEM_LE      9
#  define COF_MEM_LI      10
#  define COF_MEM_PA      11
#  define COF_MEM_PB      12
#  define COF_MEM_PE      13
#  define COF_MEM_PI      14
#  define COF_MEM_PR      15
#  define COF_MEM_XA      16
#  define COF_MEM_XB      17
#  define COF_MEM_XE      18
#  define COF_MEM_XI      19
#  define COF_MEM_XR      20
#  define COF_MEM_YA      21
#  define COF_MEM_YB      22
#  define COF_MEM_YE      23
#  define COF_MEM_YI      24
#  define COF_MEM_YR      25
#  define COF_MEM_PT      26
#  define COF_MEM_PF      27
#  define COF_MEM_ERROR   666666L

#  if defined(_TI_)
#    define COF_MEM_D       1               /* Data */
#  elif defined(_MOT_)
#    define COF_MEM_D       COF_MEM_Y       /* default data to off-chip Y */
#  endif

#  define COF_NAMELEN     8
#  define COF_FILELEN     14
#  define COF_DIMNUM      4

/* error codes */
#  define COF_EOK         0       /* no error */
#  define COF_EMEM        1       /* memory allocation failed */
#  define COF_EOPEN       2       /* cannot open COFF file */
#  define COF_ESECT       3       /* named section not found */
#  define COF_ELOAD       4       /* cannot load board */
#  define COF_EMAGIC      5       /* bad magic number */
#  define COF_EHEADER     6       /* invalid COFF header */
#  define COF_EOHEADER    7       /* invalid optional header */
#  define COF_ESHEADER    8       /* invalid section header */
#  define COF_EARGS       9       /* error loading arguments */
#  define COF_EBADARG     10      /* bad argument supplied to a function */
#  define COF_ESYMBOL     11      /* problem with symbol location */
#  define COF_ERELOC      12      /* problem with reloc information */

/*
 *  File Header flags
 */
#  define COF_F_RELFLG (0x0001)   /* relocation info stripped from file      */
#  define COF_F_EXEC   (0x0002)   /* file is executable (no unresolved refs) */
#  define COF_F_LNNO   (0x0004)   /* line nunbers stripped from file         */
#  define COF_F_ESYMS  (0x0008)

#  if defined(_TI_)
#    define COF_F_LSYMS  (0x0008)   /* local symbols stripped from file      */
#  elif defined(_MOT_)
#    define COF_F_LSYMS  (0x0010)   /* local symbols stripped from file      */
#  endif

#  define COF_F_VERS0   0x0
#  define COF_F_VERS1   0x10
#  define COF_F_VERS2   0x20
#  define COF_F_VERS3   0x40
#  define COF_F_VERS4   0x80
#  define COF_F_VERSION (COF_F_VERS1 | COF_F_VERS2 | COF_F_VERS3 | COF_F_VERS4)

#  define COF_F_LITTLE  (0x0100)
#  define COF_F_BIG     (0x0200)
#  define COF_F_AR32WR  (0x0040)
#  define COF_F_STRP30  (0x1000)

/*
 *  Section Header flags
 */
#  define COF_S_REG    (0x0000) /* "regular" : allocated, relocated, loaded */
#  define COF_S_DSECT  (0x0001) /* "dummy": not allocated, relocated,   */
                                /* not loaded                           */
#  define COF_S_NOLOAD (0x0002) /* "noload"  : allocated, relocated,    */
                                /* not loaded                           */
#  define COF_S_GROUP  (0x0004) /* "grouped" : formed of input sections */
#  define COF_S_PAD    (0x0008) /* "padding" : not allocated, not relocated, */
                                /* loaded                                    */
#  define COF_S_COPY   (0x0010)   /* "copy"    : used for C init tables - 
                                                not allocated, relocated,
                                                loaded;  reloc & lineno
                                                entries processed normally */
#  define COF_S_TEXT   (0x0020)   /* section contains text only */
#  define COF_S_DATA   (0x0040)   /* section contains data only */   
#  define COF_S_BSS    (0x0080)   /* section contains bss only */
#  define COF_S_CLINK  (0x4000)
#  if defined(_MOT_)
#    define COF_S_BLOCK  (0x0400)   /* block data section */
#  endif

/* storage classes */
#  define COF_C_EFCN      (-1)    /* physical end of function */
#  define COF_C_NULL      (0)     /* no storage class */
#  define COF_T_AUTO      (1)     /* automatic variable */
#  define COF_C_EXT       (2)     /* external symbol */
#  define COF_C_STA       (3)     /* static */
#  define COF_C_REG       (4)     /* register variable */
#  define COF_C_EXTDEF    (5)     /* external definition */
#  define COF_C_LABEL     (6)     /* label */
#  define COF_C_ULABEL    (7)     /* undefined label */
#  define COF_C_MOS       (8)     /* member of structure */
#  define COF_C_ARG       (9)     /* function argument */
#  define COF_C_STRTAG    (10)    /* structure tag */
#  define COF_C_MOU       (11)    /* member of union */
#  define COF_C_UNTAG     (12)    /* union tag */
#  define COF_C_TPDEF     (13)    /* type definition */
#  define COF_C_USTATIC   (14)    /* undefined static */
#  define COF_C_ENTAG     (15)    /* enumeration tag */
#  define COF_C_MOE       (16)    /* member of enumeration */
#  define COF_C_REGPARM   (17)    /* register parameter */
#  define COF_C_FIELD     (18)    /* bit field */
#  define COF_C_BLOCK     (100)   /* ".bb" or ".eb" */
#  define COF_C_FCN       (101)   /* ".bf" or ".ef" */
#  define COF_C_EOS       (102)   /* end of structure */
#  define COF_C_FILE      (103)   /* file name */
#  define COF_C_LINE      (104)   /* dummy sclass for line number entry */
#  define COF_C_ALIAS     (105)   /* duplicated tag */
#  define COF_C_HIDDEN    (106)   /* XDEF reference */
#  define COF_A_FILE      (200)   /* assembly source file name */
#  define COF_A_SECT      (201)   /* beginning and end of section */
#  define COF_A_BLOCK     (202)   /* beginning and end of COFF section */
#  define COF_A_MACRO     (203)   /* macro expansion */
#  define COF_A_GLOBAL    (210)   /* global assembly language symbol */
#  define COF_A_XDEF      (211)   /* XDEF symbol */
#  define COF_A_XREF      (212)   /* XREF'd symbol */
#  define COF_A_SLOCAL    (213)   /* section local label */
#  define COF_A_ULOCAL    (214)   /* underscore local label */
#  define COF_A_MLOCAL    (215)   /* macro local label */
 
/* section numbers  */
#  define COF_N_DEBUG  (-2)
#  define COF_N_ABS    (-1)
#  define COF_N_UNDEF  (0)
#  define COF_N_TEXT   (1)
#  define COF_N_DATA   (2)
#  define COF_N_BSS    (3)

#  if defined(_MOT_)
/*------------------------------------------------------------------------*/
/* The fundamental type of a symbol packed into the low                   */
/* 4 bits of the word.                                                    */
/*------------------------------------------------------------------------*/
#    define  COF_EF    ".ef"

#    define  COF_T_NULL     0       /* no type info */
#    define  COF_T_ARG      1       /* fxn argument (only used by compiler)*/
#    define  COF_T_CHAR     2       /* character */
#    define  COF_T_SHORT    3       /* short integer */
#    define  COF_T_INT      4       /* integer */
#    define  COF_T_LONG     5       /* long integer */
#    define  COF_T_FLOAT    6       /* floating point */
#    define  COF_T_DOUBLE   7       /* double word */
#    define  COF_T_STRUCT   8       /* structure  */
#    define  COF_T_UNION    9       /* union  */
#    define  COF_T_ENUM     10      /* enumeration  */
#    define  COF_T_MOE      11      /* member of enumeration */
#    define  COF_T_UCHAR    12      /* unsigned character */
#    define  COF_T_USHORT   13      /* unsigned short */
#    define  COF_T_UINT     14      /* unsigned integer */
#    define  COF_T_ULONG    15      /* unsigned long */

/* derived types */
#    define  COF_DT_NON      0      /* no derived type */
#    define  COF_DT_PTR      1      /* pointer */
#    define  COF_DT_FCN      2      /* function */
#    define  COF_DT_ARY      3      /* array */
#  endif                        /* #if _MOT_ */

/* The following sizes must be defined because some hosts pad structure sizes
 * to be a multiple of a word length but the actual size of the structure
 * in the COF file is precisely the number of bytes in the fields defined
 * in the structure.
 */

#  if defined(_TI_)

#    define COF_SYMBOLSIZE  18      /* "real" sizeof(COF_Symbol) in COF file */
#    define COF_RELOCSIZE   12      /* "real" sizeof(COF_Reloc) in COF file */
#    define COF_LINESIZE    6       /* "real" sizeof(COF_Line) in COF file */
#    define COF_FILEHDRSIZE 22      /* "real" sizeof(COF_FileHdr) */
#    define COF_SECTHDRSIZE 48      /* "real" sizeof(COF_SectHdr) */

/* TI Relocation types */
#    define COF_R_ABS           0   /* absolute address - no relocation      */
#    define COF_R_DIR16         01  /* UNUSED                                */
#    define COF_R_REL16         02  /* UNUSED                                */
#    define COF_R_DIR24         04  /* UNUSED                                */
#    define COF_R_REL24         05  /* 24 bits, direct                       */
#    define COF_R_DIR32         06  /* UNUSED                                */
#    define COF_R_RELBYTE      017  /* 8 bits, direct                        */
#    define COF_R_RELWORD      020  /* 16 bits, direct                       */
#    define COF_R_RELLONG      021  /* 32 bits, direct                       */
#    define COF_R_PCRBYTE      022  /* 8 bits, PC-relative                   */
#    define COF_R_PCRWORD      023  /* 16 bits, PC-relative                  */
#    define COF_R_PCRLONG      024  /* 32 bits, PC-relative                  */
#    define COF_R_PCR24        025  /* 24 bits, PC-relative                  */
#    define COF_R_OCRLONG      030  /* GSP: 32 bits, one's complement direct */
#    define COF_R_GSPPCR16     031  /* GSP: 16 bits, PC relative (in words)  */
#    define COF_R_GSPOPR32     032  /* GSP: 32 bits, direct big-endian       */
#    define COF_R_GSPPCA16     033  /* GSP: same as GSPPCR16, but PC constant*/
#    define COF_R_PARTLS16     040  /* Brahma: 16 bit offset of 24 bit addr  */
#    define COF_R_PARTMS8      041  /* Brahma: 8 bit page of 24 bit address  */
#    define COF_R_PARTLS7      050  /* DSP: 7 bit offset of 16 bit address   */
#    define COF_R_PARTMS9      051  /* DSP: 9 bit page of 16 bit address     */
#    define COF_R_REL13        052  /* DSP: 13 bits, direct                  */
#    define COF_R_SUBSCRIPT    060  /* RR: 8 bit relocatable reg as subscript*/
#    define COF_R_HIWORD       061  /* RR: 8 bit relocation. hi byte of word */

#  elif defined(_MOT_)

#    define COF_SYMBOLSIZE  32      /* "real" sizeof(COF_Symbol) in COF file */
#    define COF_RELOCSIZE   12      /* "real" sizeof(COF_Reloc) in COF file  */
#    define COF_FILEHDRSIZE 32      /* "real" sizeof(COF_FileHdr) */
#    define COF_SECTHDRSIZE 44      /* "real" sizeof(COF_SectHdr) */

#  endif                        /* #if defined (_TI_) / #elif defined (_MOT_)*/

#  if defined(_TI_)
typedef Char            COF_Byte;
typedef UShort          COF_Uns;
typedef Short           COF_Int;

typedef ULong           COF_Addr;

#  elif defined(_MOT_)

typedef Long            COF_Byte;
typedef ULong           COF_Uns;
typedef Long            COF_Int;

typedef struct COF_Addr {
    ULong addr;                 /* memory address */
    ULong map;                  /* memory map */
} COF_Addr;

#  endif                /* #if defined(_TI_) / #elif defined (_MOT_) */

typedef Long           COF_Size;
typedef Long           COF_Ptr;

typedef struct COF_FileHdr {
    COF_Uns  version;           /* version number */
    COF_Uns  nSects;            /* number of sections */
    Long date;                  /* time & date stamp */
    Long symTabPtr;             /* file pointer to symtab */
    Long nSyms;                 /* number of symtab entries */
    COF_Uns  optHdrSize;        /* sizeof(optional hdr) */
    COF_Uns  flags;             /* flags */
    COF_Uns  magic;             /* magic number */
} COF_FileHdr;

/*
 *  Optional Runtime Header
 */
typedef struct COF_OptHdr {
    COF_Int     magic;          /* magic number                         */
    COF_Int     vers;           /* version stamp                        */
    COF_Size    textSize;       /* text size in bytes, padded to FW     */
    COF_Size    dataSize;       /* initialized data "  "                */
    COF_Size    bssSize;        /* uninitialized data "   "             */
    COF_Addr    entryPoint;     /* entry pt.                            */
    COF_Addr    textAddr;       /* base of text used for this file      */
    COF_Addr    dataAddr;       /* base of data used for this file      */
#  if defined(_MOT_)
    COF_Addr    textEnd;        /* end address of text */
    COF_Addr    dataEnd;        /* end address of data */
#  endif
} COF_OptHdr;

typedef struct COF_LinkHdr {
    Long       objSize;        /* object module size (file size - 104)? */
    Long       dataSize;       /* sum of all COFF section sizes */
    Long       endString;      /* end directive string in string table */
    Long       sectCount;      /* number of assembler "section" sections */
    Long       counterCnt;     /* number of COFF sections */
    Long       relocCount;     /* relocation entry count */
    Long       lineCount;      /* line number entry count */
    Long       bufCount;       /* buffer count */
    Long       overCount;      /* overlay count */
    Long        majorVers;      /* major version number */
    Long        minorVers;      /* minor version number */
    Long        revNum;         /* revision number */
    Long        optFlags;       /* optional header flags */
} COF_LinkHdr;

typedef union COF_NameDesc {
    struct {
        Long   immedFlag;
        COF_Ptr ptr;
    } stringPtr;
    Char name[COF_NAMELEN];
} COF_NameDesc;

/*
 *  Section Header for TI Versions 0 & 1, and all Motorola.
 */

typedef struct COF_SectHdr01 {
    COF_NameDesc    nameDesc;   /* name or offset into string table */
    COF_Addr   physAddr;        /* physical address */
    COF_Addr   virtAddr;        /* virtual address */
    COF_Size   size;            /* section size */
    COF_Ptr    dataPtr;         /* file ptr to raw data for section */
    COF_Ptr    relocPtr;        /* file ptr to relocation */
    COF_Ptr    linePtr;         /* file ptr to line numbers */
    COF_Uns    nRelocs;         /* number of relocation entries */
    COF_Uns    nLines;          /* number of line number entries */
    COF_Uns    flags;           /* flags */

#  if defined(_TI_)
    Char       dummy;
    Char       pageNum;
#  endif
        
} COF_SectHdr01;

/*
 *  Section Header for TI Version 2; for Motorola this is identical
 *  to COF_SectHdr01.
 */

typedef struct COF_SectHdr {
    COF_NameDesc    nameDesc;   /* name or offset into string table */
    COF_Addr   physAddr;        /* physical address */
    COF_Addr   virtAddr;        /* virtual address */
    COF_Size   size;            /* section size */
    COF_Ptr    dataPtr;         /* file ptr to raw data for section */
    COF_Ptr    relocPtr;        /* file ptr to relocation */
    COF_Ptr    linePtr;         /* file ptr to line numbers */
    ULong      nRelocs;         /* number of relocation entries */
    ULong      nLines;          /* number of line number entries */
    ULong      flags;           /* flags */
        
#  if defined(_TI_)
    UShort      dummy;
    UShort      pageNum;
#  endif
        
} COF_SectHdr;

/*
 *  COFF Symbol Table Entry
 */

typedef struct COF_Symbol {
    COF_NameDesc    nameDesc;   /* name union */
    COF_Addr        value;      /* value of symbol */
    COF_Int         sectNum;    /* section number */
    COF_Uns         type;       /* type and derived type */
    COF_Byte        stoClass;   /* storage class */
    COF_Byte        numAux;     /* number of aux. entries */
} COF_Symbol;

#  if defined(_TI_)
typedef union COF_Aux {
    struct {
        Long   scnlen;         /* section length */
        UShort   nreloc;         /* number of relocation entries */
        UShort   nlinno;         /* number of line numbers */
    } scn;
    
    struct {
        Char    fname[14];
    } file;

    struct {
        Long   tagndx;     /* str, un, or enum tag indx */

        union {
            struct {
                UShort lnno;         /* declaration line number */
                UShort size;         /* str, union, array size */
            } lnsz;
            Long fsize;        /* size of function */
        } misc;

        union {
            struct {            /* if ISFCN, tag, or .bb */
                Long lnnoptr;      /* ptr to fcn line # */
                Long endndx;       /* entry ndx past block end */
            } fcn;
            struct {            /* if ISARY, up to 4 dimen. */
                UShort dimen[4];
            } ary;
        } fcnary;

        UShort regcount;     /* number of registers used by func */
    } sym;
    
} COF_Aux;

typedef struct COF_Line {
    union {
        Long   symndx;     /* sym. table index of function name
                               iff lnno == 0      */
        Long   paddr;      /* (physical) address of line number */
    } addr ;
    UShort lnno;             /* line number */
} COF_Line;

#  elif defined(_MOT_)
typedef struct COF_Aux {
    Long        scnlen;         /* section length */
    ULong       nreloc;         /* number of relocation entries */
    ULong       nlinno;         /* number of line numbers */
    ULong       unused[5];      /* unused (zero filled) */
} COF_Aux;

#  endif                        /* #if _MOT_ / #else */

typedef struct COF_Reloc {
    Long   r_vaddr;        /* virtual address of word to be modified */
    Long r_symndx;       /* string table pointer to relocation expression */
#  if defined(_TI_)
    COF_Uns r_disp;         /* additional bits for address calculation */
# endif
    COF_Uns r_type;         /* relocation type */

} COF_Reloc;
    
/*
 *  ======== COF_Attrs ========
 */
typedef ULong   (*COF_WriteFxn)(Ptr, ULong, Ptr, ULong, Int);
typedef Bool    (*COF_LookupFxn)(Ptr, String, COF_Symbol*, ULong*);
typedef Int     (*COF_FreadFxn)(Ptr, size_t, size_t, Ptr);
typedef Int     (*COF_FseekFxn)(Ptr, Long, Int);
typedef Long   (*COF_FtellFxn)(Ptr);
typedef Int     (*COF_FcloseFxn)(Ptr);
typedef Ptr     (*COF_FopenFxn)(const Char *, const Char *);
typedef Int     (*COF_FwriteFxn)(Ptr, size_t, size_t, Ptr);

typedef struct COF_Attrs {
    COF_WriteFxn        write;
    Ptr                 wp;   /* argument passed to write callback function */
    COF_LookupFxn       lookup;
    Ptr                 lp;   /* argument passed to lookup callback function */
    COF_FreadFxn        fread;
    COF_FseekFxn        fseek;
    COF_FtellFxn        ftell;
    COF_FcloseFxn       fclose;
    COF_FopenFxn        fopen;
    COF_FwriteFxn       fwrite;
    ULong               argsAddr;    /* addr for arguments */
    ULong               argsSize;    /* size of arguments section */
    UInt                 loadBufSize; /* size of load buffer */
} COF_Attrs;

typedef struct COF_HandleObj *COF_Handle;

#  if defined(_TI_)
#    define COF_offset(x)   (x)
#  elif defined(_MOT_)
#    define COF_offset(x)   ((x).addr)

#  endif                /* #if defined(_TI_) / #elif defined (_MOT_) */


/* ======== COF Interface Prototypes and Descriptions ======== */

/*
 *  ======== COF_byteSize ========
 *
 *  Return the byte size of the target processor for which the COFF file is
 *  intended.  Note that the byte size that is returned is the least power
 *  of two greater than or equal to the number of 8-bit bytes in a target
 *  byte. For example, the byte size returned for a 24-bit byte processor
 *  is 4.
 */
extern unsigned int COF_byteSize(COF_Handle hnd);

/*
 *  ======== COF_byteSwapped ========
 *
 *  Return TRUE if bytes are swapped, FALSE otherwise.
 */
extern Bool COF_byteSwapped(COF_Handle hnd);

/*
 *  ======== COF_charSize ========
 *
 *  Return the size of a character. This is needed to support C55x, where
 *  characters are 2 bytes, but MAU size is 1 byte.
 */
extern unsigned int COF_charSize(COF_Handle desc);

/*
 *  ======== COF_create ========
 *  Create COFF object of type type (= COF_C30, COF_56K, COF_96K, ...), with
 *  COF file fname.  Returns handle of object (NULL on failure), and error
 *  number value in errno.
 */
extern COF_Handle COF_create(int type, char *fname, int *status,
                             COF_Attrs *attrs);

/*
 *  ======== COF_delete ========
 *  Delete COF COFF object referenced by hnd.
 */
extern void COF_delete(COF_Handle hnd);

/*
 *  ======== COF_exit ========
 *  Undo anything done by COF_init.  COF_exit must
 *  be called only as part of system shutdown.
 */
extern void COF_exit(void);

/*
 *  ======== COF_getCSymbol ========
 *
 *  Retrieve the symbol indicated by '_' + name and return it in *sym.  Return
 *  COF_EOK on success, COF_EBADARG if the parameter "symbol" is null or if
 *  name is not found.
 */
extern int COF_getCSymbol(COF_Handle hnd, String name, COF_Symbol *sym);

/*
 *  ======== COF_getEntry ========
 *  Get the COFF entry point address and return in *entry.  Return COF_EOK on
 *  success, COF_EBADARG if either hnd or entry is NULL, or COF_EOHEADER if
 *  the COFF optional header doesn't fit the expected format.
 */
extern int COF_getEntry(COF_Handle hnd, ULong *entry);

/*
 *  ======== COF_getHeader ========
 *  Get the file header from the COF object referenced by hnd and return it in
 *  *header.
 */
extern void COF_getHeader(COF_Handle hnd, COF_FileHdr *header);

/*
 *  ======== COF_getOptHdr ========
 *  Get the optional file header from the COF object referenced by hnd and
 *  return it in *header.  Return COF_EOK on success, COF_EOHEADER if optional
 *  header is not accessible, or COF_EBADARG if desc or hdr aren't valid.
 */
extern int COF_getOptHdr(COF_Handle hnd, COF_OptHdr *header);

/*
 *  ======== COF_getSect ========
 *  Given a section name, find the first section with that name and return
 *  it in *sect.  Return COF_EOK on success, or COF_ESECT on failure.
 */
extern int COF_getSect(COF_Handle hnd, String name, COF_SectHdr *sect);

/*  ======== COF_getSectHdrSize ========
 *
 *  Given a COFF file handle, return the section header size being used.
 */
extern unsigned int COF_getSectHdrSize(COF_Handle hnd);

/*
 *  ======== COF_getSectNum ========
 *
 *  Given an ordinal integer num, copy the num'th section header into *sect.
 *  If the "name" parameter is not null, the section header's name will be
 *  copied into name.  Note that sections are numbered starting with 1, not
 *  0.  Returns COF_EOK on success, COF_EBADARG if either hnd or sect is NULL,
 *  or COF_ESHEADER if the num'th section header is not available or num is
 *  out of range.
 */
extern int COF_getSectNum(COF_Handle hnd, int num, COF_SectHdr *sect,
                          String name);

/*
 *  ======== COF_getStrTab ========
 *  reads the current contents of the string table into the buffer strTab.
 *  Only size characters will be copied (use COF_getStrTabSize() to get
 *  the size of the table).
 *
 *  Returns COF_EOK on success; otherwise
 *      COF_EBADARG - strTab is NULL or the read failed
 *      COF_EHEADER - the seek to the string table failed
 */
extern int COF_getStrTab(COF_Handle desc, Char *strTab, Long size);

/*
 *  ======== COF_getStrTabSize ========
 *  Returns the current size of the string table in the COFF file.
 *
 *  Returns 0 on any error.
 */
extern long COF_getStrTabSize(COF_Handle desc);

/*
 *  ======== COF_getSymbol ========
 *
 *  Retrieve the symbol indicated by name and return it in *sym.  Return
 *  COF_EOK on success, COF_EBADARG if the parameter "symbol" is null or if
 *  name is not found.
 */
extern int COF_getSymbol(COF_Handle hnd, String name, COF_Symbol *sym);

/*
 *  ======== COF_getSymbolNum ========
 *  Retrieve the symbol specified by num and return it in *sym. If name is not
 *  null, copy the symbol's name to name.  Note that symbols are stored
 *  contiguously and some symbols may contain auxilliary symbols.  Symbols are
 *  indexed starting with 0, so num would be 0 in order to retrieve the first
 *  symbol.  Return COF_EOK on success, COF_EBADARG if hnd or symbol are NULL,
 *  or COF_ESYMBOL if num is out of range.
 */
extern int COF_getSymbolNum(COF_Handle hnd, long num, COF_Symbol *sym,
                            String name);
/*
 *  ======== COF_getTargetType ========
 *  Return the target type that was used when COF_create() was called.
 */
extern int COF_getTargetType(COF_Handle hnd);

/*
 *  ======== COF_init ========
 *  Do all initialization required by the Spectron COF module.  COF_init must
 *  be called before any of the Spectron COF functions are used.
 */
extern void COF_init(void);

/*
 *  ======== COF_load ========
 *  Load the program in the COFF file onto a processor, along with the
 *  arguments and environment passed to COF_load() in the argc, argv, and
 *  envp arguments.  If the COFF file doesn't have a ".args" section, the
 *  target destination for the arguments and environment must be specified
 *  with the "argsAddr" and "argsSize" fields in the "attrs" parameter to
 *  COF_create().  The program's entry point is returned in *entry.  Return
 *  COF_EOK on success, COF_EOHEADER if the optional header is inaccessible,
 *  COF_EMEM if memory cannot be allocated, or COF_EARGS if the space allowed
 *  for arguments is too small.
 */
extern int COF_load(COF_Handle hnd, Int argc, String argv[], String envp[],
                    ULong *entry);
/*
 *  ======== COF_loadArgs ========
 *  Load argc, argv[], and envp[] onto the target processor, using the "write"
 *  function specified in the "attrs" structure passed to COF_create.  The
 *  "argsAddr" and "argsSize" parameters to COF_loadArgs indicate the
 *  destination address and the amount of space on the target processor
 *  available for arguments and environment.  Returns COF_EOK on success,
 *  COF_EARGS if the memory allocation fails or if argSize is too small.
 */
extern Int COF_loadArgs(COF_Handle desc, ULong argsAddr, ULong argsSize,
                             Int argc, String argv[], String envp[]);
/*
 *  ======== COF_loadCGArgs ========
 *  Same as COF_loadArgs, except that the format conforms to CodeGens's
 *  format.
 */
extern Int COF_loadCGArgs(COF_Handle desc, ULong argsAddr, ULong argsSize,
                             Int argc, String argv[], String envp[]);

/*
 *  ======== COF_loadCode ========
 *  This function loads the program in the COFF file into the target processor
 *  and returns the entry point address in *entry.  A board-specific write
 *  function must be assigned to the "write" field of the "attrs" parameter to
 *  COF_create().  Returns COF_EOK on success, COF_ESECT if a section cannot be
 *  loaded, or COF_EOHEADER if the entry point cannot be extracted from the
 *  COFF files's optional header.
 */
extern Int COF_loadCode(COF_Handle desc, ULong *entry);

/*
 *  ======== COF_loadSect ========
 *  Write the data from section sect (section number sectNum)  to the target
 *  processor, using the function specified with the "write" field in the
 *  "attrs" parameter to COF_create().  Indicate whether this is a bss section
 *  with the boolean parameter bss.  Although *sect and sectNum are redundant,
 *  both parameters are required.  Returns TRUE on success or FALSE on failure.
 */
extern Bool COF_loadSect(COF_Handle hnd, COF_SectHdr *sect, Int sectNum,
                         ULong buf[], Bool bss);

/*
 *  ======== COF_nextReloc ========
 *
 *  Read the next relocation record into *reloc, its associated symbol into
 *  *sym, and the associated symbol's name into name.  COF_scanReloc() must
 *  be called prior to COF_nextReloc() calls.  Neither COF_scanSymbols() nor
 *  COF_nextSymbol() may be called between COF_scanReloc() and COF_nextReloc().
 *  Returns COF_EOK on success, COF_EBADARG if either desc or sym are NULL,
 *  COF_ESYMBOL if there are no more relocation records in the current section
 *  if the symbol record cannot be read, or COF_ERELOC if  the relocation
 *  record cannot be read from the COFF file.
 */
extern Int COF_nextReloc(COF_Handle hnd, COF_Reloc *reloc, COF_Symbol *sym,
                         String name);

/*
 *  ======== COF_nextSymbol ========
 *
 *  Read the next symbol into *sym, and read the symbol's name into name.
 *  COF_scanSymbol() must be called prior to COF_nextSymbol() calls. Neither
 *  COF_scanReloc() nor COF_nextReloc() may be called between COF_scanSymbol()
 *  and COF_nextSymbol().  Returns COF_EBADARG if either desc or symbol is
 *  NULL, COF_ESYMBOL if the symbol cannot be read, or COF_EOK on success.
 */
extern int COF_nextSymbol(COF_Handle hnd, COF_Symbol *sym, String name);

/*
 *  ======== COF_putStrTab ========
 *  Write new string table, strTab, to COFF file.
 *
 *  Returns COF_EOK on success; otherwise
 *      COF_EHEADER - unable to seek in COFF file to existing string table
 *      COF_EBADARG - either no fwrite function was supplied or the write
 *                    failed.
 */
extern int COF_putStrTab(COF_Handle desc, Char *strTab, Long size);

/*
 *  ======== COF_putSymbolNum ========
 *  Overwite existing symbol in COFF file.  The symbol to be written is
 *  specified by the number id.
 *
 *  Returns COF_EOK on success; otherwise
 *      COF_ESYMBOL - id is an invalid symbol id
 *      COF_EBADARG - desc or symbol is NULL
 *      COF_EHEADER - unable to seek to specified symbol or the write failed
 */
extern int COF_putSymbolNum(COF_Handle desc, Long id, COF_Symbol *symbol);

/*
 *  ======== COF_readSect ========
 *  Read nwords of  data from the section indicated by sect into the buffer
 *  pointed to by buf.  Return TRUE on success or FALSE on failure.
 */
extern Bool COF_readSect(COF_Handle hnd, COF_SectHdr *sect, Ptr buf,
                         Int nwords);

/*
 *  ======== COF_scanReloc ========
 *  Prepare to read relocation records for the section indicated by sectNum.
 *  Returns the number of relocation records in the section.  Note that
 *  sections are numbered beginning with 1, not 0.
 */
extern ULong      COF_scanReloc(COF_Handle desc, Int sectNum);

/*
 *  ======== COF_scanSymbols ========
 *  Prepare to read symbols from the COFF file, prior to calling
 *  COF_nextSymbol().  Returns COF_EBADARG if hnd is NULL, COF_ESYMBOL if
 *  there are no symbols to be read, or COF_EOK on success.
 */
extern int      COF_scanSymbols(COF_Handle hnd);

/*
 *  ======== COF_sectionType ========
 *  Get the section attributes flags for the section indicated by sectNum.
 *  The attribute flags are returned in *type.   Return COF_EBADARG if hnd is
 *  null, COF_ESECT if sectNum is out of range, or COF_EOK on success.
 */
extern int      COF_sectionType(COF_Handle hnd, long sectNum, long *type);

/*
 *  ======== COF_wordSize ========
 *
 *  Return the word size of the target processor for which the COFF file is
 *  intended.  Note that the word size that is returned is the least power
 *  of two greater than or equal to the number of 8-bit bytes in a target
 *  word. For example, the word size returned for a 24-bit processors is 4.
 */
extern unsigned int COF_wordSize(COF_Handle hnd);

/*
 *  ======== COF_writeFileHeader ========
 *
 *  Writes a COFF file header to a COFF file.  Returns the number of bytes
 *  in a COFF file header.
 */
extern unsigned int COF_writeFileHeader(FILE *file, COF_FileHdr *header,
        Fxn fwriteFxn);

/*
 *  ======== COF_writeSectHeader ========
 *
 *  Writes a COFF section header to a COFF file.  
 */
extern unsigned int COF_writeSectHeader(FILE *file, COF_SectHdr *header, 
        UInt size, Fxn fwriteFxn);


extern const COF_Attrs COF_ATTRS;
extern const COF_Attrs COF_STDATTRS;

#endif /*COF_*/
/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 10-21-2016 18:37:04; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

