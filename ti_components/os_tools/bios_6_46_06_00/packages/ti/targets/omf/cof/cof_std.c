/*
 *  Copyright 2016 by Texas Instruments Incorporated.
 *
 */

/*
 * ======== cof_std.c ========
 *
 * This module provides an object pointing to standard C I/O functions
 * for COF users.
 *
 */

#include <stdio.h>

#include <xdc/std.h>
#include <cof.h>

const COF_Attrs COF_STDATTRS = {
    (COF_WriteFxn)NULL,                 /* write function callback      */
    (Ptr)NULL,                          /* write function argument      */
    (COF_LookupFxn)NULL,                /* lookup function callback     */
    (Ptr)NULL,                          /* lookup function argument     */
    (COF_FreadFxn)fread,                /* read function                */
    (COF_FseekFxn)fseek,                /* seek function                */
    (COF_FtellFxn)ftell,                /* tell function                */
    (COF_FcloseFxn)fclose,              /* file close function          */
    (COF_FopenFxn)fopen,                /* file open function           */
    (COF_FwriteFxn)NULL,                /* file write function          */
    0L,                                 /* default arguments address    */
    0L,                                 /* default arguments size       */
    0x800                               /* default load buffer size     */
};
/*
 *  @(#) ti.targets.omf.cof; 1,0,0,0; 10-21-2016 18:37:04; /db/ztree/library/trees/xdctargets/xdctargets-l07/src/ xlibrary

 */

