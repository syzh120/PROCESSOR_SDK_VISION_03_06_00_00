/*
 *  Copyright 2016 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== cof_syms.c ========
 *
 *  Motorola and TI DSP COFF support.
 *
 *  This file supports manipulations of symbols and sections in COFF files.
 *
 */

#if defined(_VXWORKS_)
/* This must be before std.h because it indirectly redefines TRUE and FALSE. */
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

static Void copySymbol(COF_Symbol * src, COF_Symbol * dst);
static Int  getNextSymbol(COF_Handle desc, FILE *file, COF_Symbol * symbol);
static Int  putSymbol(COF_Handle desc, FILE *file, COF_Symbol *symbol);

/*
 *  ======== COF_getCSymbol ========
 *
 *  Retrieve the symbol indicated by '_' + name and return it in *sym.  Return
 *  COF_EOK on success, COF_EBADARG if the parameter "symbol" is null or if
 *  name is not found.
 */
int COF_getCSymbol(COF_Handle desc, String name, COF_Symbol *symbol)
{
    Char        symName[COF_MAXEXPR];
    Int         error = COF_EBADARG;
    Long       i;

    if (symbol == NULL) {
        return (COF_EBADARG);
    }
    
    (*desc->attrs.fseek)(desc->file, desc->header.symTabPtr, SEEK_SET);
    
    for (i = 0; i < desc->header.nSyms; ) {

        i += getNextSymbol(desc, desc->file, symbol);

        _COF_getName(desc, &symbol->nameDesc, symName);

        if (strcmp(name, symName + 1) == 0 && symName[0] == '_') {
            error = COF_EOK;
            break;
        }
    }

    return (error);
}

/*
 *  ======== COF_getOptHdr ========
 *
 *  Given a COF_Handle, copy its optional header into the structure pointed to
 *  by the parameter "hdr".
 */

int COF_getOptHdr(COF_Handle desc, COF_OptHdr *hdr)
{
    if ((desc == NULL) || (hdr == NULL)) {
        return (COF_EBADARG);
    }
    else if (desc->header.optHdrSize != sizeof(COF_OptHdr)) {
        return (COF_EOHEADER);
    }
    else {
        *hdr = desc->optHeader;
        return (COF_EOK);
    }
}

/*
 *  ======== COF_getSectNum ========
 *
 *  Given a COF_Handle and an integer "num", find the num'th section header,
 *  then copy it into the structure pointed to by "sect".  If the "name"
 *  parameter is not null, the section header's name will be copied into
 *  "name".
 */

int COF_getSectNum(COF_Handle desc, Int num, COF_SectHdr *sect, String name)
{
    COF_SectHdr *sptr;

    if ((sect == NULL) || (desc == NULL)) {
        return (COF_EBADARG);
    }

    if ((num > 0) && ((unsigned)num <= desc->header.nSects)) {
        if ((sptr = _COF_getSectPtr(desc, num)) != NULL) {
            *sect = *sptr;
        }
        else {
            return (COF_ESHEADER);
        }

        if (name) {
            _COF_getName(desc, &sect->nameDesc, name);
        }

        return (COF_EOK);
    }
    return (COF_ESECT);
}

/*
 *  ======== COF_getStrTab ========
 */
int COF_getStrTab(COF_Handle desc, Char *strTab, Long size)
{
    if ((*desc->attrs.fseek)(desc->scanFile, desc->strTab, SEEK_SET)) {
        return (COF_EHEADER);
    }
    
    if (strTab == NULL
        || (*desc->attrs.fread)(strTab, size, 1, desc->scanFile) != 1) {
        return (COF_EBADARG);
    }

    if (desc->byteSwapped) {
        _COF_swapLong((Long *)strTab);
    }

    return (COF_EOK);
}

/*
 *  ======== COF_getStrTabSize ========
 */
long COF_getStrTabSize(COF_Handle desc)
{
    long size;
    
    if ((*desc->attrs.fseek)(desc->scanFile, desc->strTab, SEEK_SET)) {
        return (0);
    }
    
    if ((*desc->attrs.fread)(&size, sizeof (long), 1, desc->scanFile) != 1) {
        return (0);
    }

    if (desc->byteSwapped) {
        _COF_swapLong(&size);
    }
    
    return (size);
}

/*
 *  ======== COF_getSymbol ========
 *
 *  Retrieve the symbol indicated by name and return it in the structure
 *  pointed to by symbol.  Return COF_EOK on success, COF_EBADARG if the
 *  parameter "symbol" is NULL or if name is not found.
 */

int COF_getSymbol(COF_Handle desc, String name, COF_Symbol *symbol)
{
    Char        symName[COF_MAXEXPR];
    Int         error = COF_EBADARG;
    Long        i;
    COF_Symbol  temp;

    if (symbol == NULL) {
        return (COF_EBADARG);
    }

    (*desc->attrs.fseek)(desc->file, desc->header.symTabPtr, SEEK_SET);
    
    for (i = 0; i < desc->header.nSyms; ) {

        i += getNextSymbol(desc, desc->file, symbol);

        _COF_getName(desc, &symbol->nameDesc, symName);

        if (strcmp(name, symName) == 0) {
            copySymbol(symbol, &temp);
            /* If we find an external definition, we get out, otherwise save
             * the found one to return it, if we can't find and external one.
             */
            if (symbol->type == COF_C_EXT) {
                error = COF_EOK;
                break;
            }
            else {
                copySymbol(symbol, &temp);
                error = COF_EOK;
            }
        }
    }
    copySymbol(&temp, symbol);
    return (error);
}

/*
 *  ======== COF_getSymbolNum ========
 *
 *  Retrieve the symbol specified by "id". Note that symbols are stored
 *  contiguously and some symbols may contain auxilliary symbols.
 *
 *  This function does not preserve the file position.
 */

int COF_getSymbolNum(COF_Handle desc, Long id, COF_Symbol *symbol,
    String name)
{
    if ((desc == NULL) || (symbol == NULL)) {
        return (COF_EBADARG);
    }
    
    if (id >= desc->header.nSyms) {
        return (COF_ESYMBOL);
    }

    /* move to the beginning of the symbol plus an offset*/
    if ((*desc->attrs.fseek)(desc->scanFile, desc->header.symTabPtr 
                         + (id * COF_SYMBOLSIZE), SEEK_SET)) {
        return (COF_EHEADER);
    }

    getNextSymbol(desc, desc->scanFile, symbol);

    if (name) {
        _COF_getName(desc, &symbol->nameDesc, name);
    }

    return (COF_EOK);
}

/*
 *  ======== COF_nextReloc ========
 *
 *  Read the next relocation record into *reloc, its associated symbol into
 *  *sym, and the associated symbol's name into name.  COF_scanReloc() must
 *  be called prior to COF_nextReloc() calls.  Neither COF_scanSymbols() nor
 *  COF_nextSymbol() may be called between COF_scanReloc() and COF_nextReloc()
 *  without saving and restoring the desc->scanFile file handle.  Returns
 *  COF_EOK on success, COF_EBADARG if either desc or sym are NULL, COF_ESYMBOL
 *  if there are no more relocation records in the current section if the
 *  symbol record cannot be read, or COF_ERELOC if  the relocation record
 *  cannot be read from the COFF file.
 */

Int COF_nextReloc(COF_Handle desc, COF_Reloc *reloc, COF_Symbol *sym, 
                  String name)
{
    if ((desc == NULL) || (reloc == NULL)) {
        return (COF_EBADARG);
    }

    if (desc->curRelocIndex++ >= (Long)desc->curSect->nRelocs) {
        return (COF_ESYMBOL);
    }

    if ((*desc->attrs.fread)(reloc, COF_RELOCSIZE, 1, desc->scanFile) != 1) {
        return (COF_ERELOC);
    }

    if (desc->byteSwapped) {
        _COF_swapLong(&reloc->r_vaddr);
        _COF_swapLong(&reloc->r_symndx);
#if defined(_TI_)
        _COF_swapUns(&reloc->r_disp);
#endif
        _COF_swapUns(&reloc->r_type);
    }
    
#if defined(_TI_)
    if (sym) {
        Long       save;
        
        /* symndx == -1 implies relcation is relative to current section */
        if (reloc->r_symndx < 0) {  
            name[0] = '\0';
            return (COF_EOK);
        }

        /* save current file position */
        save = (*desc->attrs.ftell)(desc->scanFile);
        
        /* move to the beginning of the symbol */
        if ((*desc->attrs.fseek)(desc->scanFile,
            desc->header.symTabPtr + (reloc->r_symndx * COF_SYMBOLSIZE),
            SEEK_SET)) {
            return (COF_EHEADER);
        }
    
        if (getNextSymbol(desc, desc->scanFile, sym) == 0) {
            (*desc->attrs.fseek)(desc->scanFile, save, SEEK_SET);
            return (COF_ESYMBOL);
        }
    
        if (name) {
            _COF_getName(desc, &sym->nameDesc, name);
        }

        /* restore current file position */
        (*desc->attrs.fseek)(desc->scanFile, save, SEEK_SET);
    }
#elif defined(_MOT_)                    /* #if defined(_TI_) */
    _COF_USEARG(sym);
    
    if (name) {
        Int nChar;
        
        (*desc->attrs.fseek)(desc->stfile, desc->strTab + reloc->r_symndx, 
                             SEEK_SET);

        /* copy the string from the file; guaranteed to be null-terminated */
        for (nChar = 0; nChar < COF_MAXEXPR; nChar++) {
            if ((*desc->attrs.fread)(name, sizeof(Char), 1, desc->stfile) != 1) {
                return (COF_ERELOC);
            }
            if (*name++ == '\0') {
                break;
            }
        }
        if (nChar >= COF_MAXEXPR) { /* loop above didn't copy '\0' into name */
            return (COF_ERELOC);
        }
    }

#endif                  /* #if defined(_TI_) / #elif defined (_MOT_) */
    return (COF_EOK);
}

/*
 *  ======== COF_nextSymbol ========
 *
 *  Read the next symbol into *symbol, and read the symbol's name into name.
 *  COF_scanSymbols() must be called prior to COF_nextSymbol() calls. Neither
 *  COF_scanReloc() nor COF_nextReloc() may be called between COF_scanSymbols()
 *  and COF_nextSymbol() without saving and restoring the desc->scanFile file
 *  handle.  Returns COF_EBADARG if either desc or symbol is NULL, COF_ESYMBOL
 *  if the symbol cannot be read, or COF_EOK on success.
 */
Int COF_nextSymbol(COF_Handle desc, COF_Symbol *symbol, String name)
{
    if ((desc == NULL) || (symbol == NULL)) {
        return (COF_EBADARG);
    }

    if (desc->curSymIndex >= desc->header.nSyms) {
        return (COF_ESYMBOL);
    }

    desc->curSymIndex += getNextSymbol(desc, desc->scanFile, symbol);

    if (name) {
        _COF_getName(desc, &symbol->nameDesc, name);
    }
    
    return (COF_EOK);
}

/*
 *  ======== COF_putStrTab ========
 */
int COF_putStrTab(COF_Handle desc, Char *strTab, Long size)
{
    if ((*desc->attrs.fseek)(desc->scanFile, desc->strTab, SEEK_SET)) {
        return (COF_EHEADER);
    }
    
    if (desc->attrs.fwrite == NULL) {
        return (COF_EBADARG);
    }

    *(Long *)strTab = size;

    if (desc->byteSwapped) {
        _COF_swapLong((Long *)strTab);
    }

    if (size <= sizeof(Long)
        || (*desc->attrs.fwrite)(strTab, size, 1, desc->scanFile) != 1) {
        return (COF_EBADARG);
    }

    return (COF_EOK);
}

/*
 *  ======== COF_putSymbolNum ========
 *
 *  Write the symbol specified by "id". Note that symbols are stored
 *  contiguously and some symbols may contain auxilliary symbols.
 *
 *  This function does not preserve the file position.
 */

int COF_putSymbolNum(COF_Handle desc, Long id, COF_Symbol *symbol)
{
    if ((desc == NULL) || (symbol == NULL)) {
        return (COF_EBADARG);
    }
    
    if (id >= desc->header.nSyms) {
        return (COF_ESYMBOL);
    }

    /* move to the beginning of the symbol plus an offset*/
    if ((*desc->attrs.fseek)(desc->scanFile, desc->header.symTabPtr 
                         + (id * COF_SYMBOLSIZE), SEEK_SET)) {
        return (COF_EHEADER);
    }
    
    if (putSymbol(desc, desc->scanFile, symbol) != 1) {
        return (COF_EHEADER);
    }

    return (COF_EOK);
}

/*
 *  ======== COF_scanReloc ========
 *
 *  Position the COF_Handle's file pointer to the relocation block pointed
 *  to by section header indicated by "sectNum".  Also, reset the COF_Handle's
 *  current relocation index (curRelocIndex) and set the COF_Handle's "curSect"
 *  pointer to the section header indicated by "sectNum".  Return the number
 *  of relocations in the current section.
 */
ULong COF_scanReloc(COF_Handle desc, Int sectNum)
{
    COF_SectHdr    *curSect;        /* current section for scan reloc info */

    if ((curSect = _COF_getSectPtr(desc, sectNum)) != NULL) {
        desc->curRelocIndex = 0;
        desc->curSect = curSect;
        
        if (curSect->size && curSect->dataPtr && curSect->nRelocs) {
            /* move to the location of the relocation info for this section */
            (*desc->attrs.fseek)(desc->scanFile, curSect->relocPtr, SEEK_SET);

            return (curSect->nRelocs);
        }
    }

    return (0);
}

/*
 *  ======== COF_scanSymbols ========
 *
 *  Move the COF_Handle's file pointer ("scanFile") to the beginning of the
 *  symbol table, and set the COF_Handle's current symbol table index
 *  ("curSymIndex") to zero.
 */
Int COF_scanSymbols(COF_Handle desc)
{
    if (desc == NULL) {
        return (COF_EBADARG);
    }

    if (desc->header.nSyms == 0) {
        return (COF_ESYMBOL);
    }

    (*desc->attrs.fseek)(desc->scanFile, desc->header.symTabPtr, SEEK_SET);

    desc->curSymIndex = 0;

    return(COF_EOK);
}


/*
 *  ======== COF_sectionType ========
 *
 *  Get the section attributes flags for the section indicated by "sectNum".
 */
Int COF_sectionType(COF_Handle desc, Long sectNum, Long *outType)
{
    COF_SectHdr    *sptr;           /* current section for scan reloc info */

    if (desc == NULL) {
        return (COF_EBADARG);
    }

    if ((sectNum > 0) && (sectNum <= (Long)desc->header.nSects)) {
        if ((sptr = _COF_getSectPtr(desc, sectNum)) != NULL) {
            *outType = sptr->flags;
            return (COF_EOK);
        }
    }

    return (COF_ESECT);
}


/*
 *  ======== _COF_getName ========
 *
 *  This function copies the a null-terminated string into the provided
 *  output string. The name is found based on the fields in the COFF
 *  name descriptor.
 *
 *  Names are stored directly in the 8 bytes of the name descriptor if
 *  they are less than 8 bytes, or are stored in the string table of the
 *  COFF file if they are 8 bytes or greater.
 *
 *  NOTE: assumes that offset has already been byte swapped (if needed)
 */
Void _COF_getName(COF_Handle desc, COF_NameDesc *nameDesc, String name)
{
    ULong   strTab;
    Int     nChar;

    if (nameDesc->stringPtr.immedFlag) {
        /* the name is in the nameDesc field directly */
        strncpy(name, nameDesc->name, COF_NAMELEN);
        name[COF_NAMELEN] = '\0';  /* nameDesc is not always 0 terminated! */
    }
    else {
        /* offset in the file of the string table (first 4 bytes are length) */
        strTab = desc->header.symTabPtr +
            (desc->header.nSyms * COF_SYMBOLSIZE);

        /* move to the location of the string entry */
        (*desc->attrs.fseek)(desc->stfile, strTab + nameDesc->stringPtr.ptr, 
                             SEEK_SET);

        /* copy the string from the file; guaranteed to be null-terminated */
        for (nChar = 0; nChar < COF_MAXEXPR; nChar++) {
            if ((*desc->attrs.fread)(name, sizeof(Char), 1, desc->stfile) 
                    != 1) {
                *name = '\0';
            }

            if (*name++ == '\0') {
                break;
            }
        }

        if (nChar >= COF_MAXEXPR) { /* loop above didn't copy '\0' into name */
            name[-1] = '\0';        /* force '\0' termination of name */
        }
    }
}

/*
 *  ======== copySymbol ========
 *
 *  Copy the symbol data from src to dst. */

static Void copySymbol(COF_Symbol * src, COF_Symbol * dst)
{
#  if defined(_TI_)

    dst->value = src->value;

#  elif defined(_MOT_)
    
    dst->value.addr = src->value.addr;
    dst->value.map = src->value.map;

#  endif                /* #if defined(_TI_) / #elif defined (_MOT_) */

    dst->sectNum = src->sectNum;
    dst->type = src->type;
    dst->stoClass = src->stoClass;
    dst->numAux = src->numAux;
    
    dst->nameDesc = src->nameDesc;
}

/*
 *  ======== getNextSymbol ========
 *
 *  Read the next symbol entry. This function assumes that the file for
 *  COFF handle is already correctly positioned.
 *
 *  Returns the number of symbols read. The symbol count in the COFF
 *  header indicates the total number of symbols and associated auxilliary
 *  symbols. This function skips over the auxilliary symbols.
 */
static Int getNextSymbol(COF_Handle desc, FILE *file, COF_Symbol *symbol)
{
    COF_Symbol      auxSymbol;
    Int             numSymbolsRead = 0;
    Long           i;
    
    if ((*desc->attrs.fread)((Char *)symbol, COF_SYMBOLSIZE, 1, file)) {

        if (desc->byteSwapped) {
            if (symbol->nameDesc.stringPtr.immedFlag == 0L) {
                _COF_swapPtr(&symbol->nameDesc.stringPtr.ptr);
            }
            _COF_swapAddr(&symbol->value);
            _COF_swapInt(&symbol->sectNum);
            _COF_swapUns(&symbol->type);
            _COF_swapByte(&symbol->stoClass);
            _COF_swapByte(&symbol->numAux);
        }

        numSymbolsRead = (Int)symbol->numAux + 1;

        /* read the aux symbols so we are left positioned at next real symbol*/
        for (i = symbol->numAux; i > 0; i--) {
            (*desc->attrs.fread)((Char *)&auxSymbol, COF_SYMBOLSIZE, 1, file);
        }
    }

    return (numSymbolsRead);
}

/*
 *  ======== putSymbol ========
 *
 *  Write the next symbol entry. This function assumes that the file for
 *  COFF handle is already correctly positioned.
 *
 *  Returns the number of symbols written
 */
static Int putSymbol(COF_Handle desc, FILE *file, COF_Symbol *symbol)
{

    if (desc->byteSwapped) {
        if (symbol->nameDesc.stringPtr.immedFlag == 0L) {
            _COF_swapPtr(&symbol->nameDesc.stringPtr.ptr);
        }
        _COF_swapAddr(&symbol->value);
        _COF_swapInt(&symbol->sectNum);
        _COF_swapUns(&symbol->type);
        _COF_swapByte(&symbol->stoClass);
        _COF_swapByte(&symbol->numAux);
    }

    if ((*desc->attrs.fwrite)((Char *)symbol, COF_SYMBOLSIZE, 1, file) == 1) {
        return (1);
    }

    return (0);
}
/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 10-21-2016 18:37:04; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

