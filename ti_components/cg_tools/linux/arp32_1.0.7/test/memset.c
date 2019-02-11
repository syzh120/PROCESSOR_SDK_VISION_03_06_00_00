
#undef _INLINE
#include <string.h>

/*---------------------------------------------------------------------------*/
/* MEMSET: Generic memory set/fill routine.  This is an optimized routine    */
/*         based on c6x memset.c                                             */
/*---------------------------------------------------------------------------*/
_CODE_ACCESS void *memset(void *dst, int fill, size_t len)
{
    int   pre_bytes, post_bytes, wfill, i;
    char *restrict dst1 = (char *)dst;

    /*--------------------------------------------------------------------*/
    /* Replicate the 8-bit value in fill into all 4 bytes of wfill        */
    /*--------------------------------------------------------------------*/
    wfill  = 0x101 * (fill & 0xff);
    wfill += wfill << 16;

    /*--------------------------------------------------------------------*/
    /* Calculate number of bytes to pre-copy to get to an alignment of 4  */
    /*--------------------------------------------------------------------*/
    pre_bytes = (4 - (int) dst1) & 3;
    if (len > pre_bytes)
    {
        len -= pre_bytes;
        if (pre_bytes & 1) { *(char *) dst1 = fill;  dst1 += 1; }
        if (pre_bytes & 2) { *(short *)dst1 = wfill; dst1 += 2; }
    }

    /*--------------------------------------------------------------------*/
    /* Double word fills.  Since we want to get the most out of HLA loop  */
    /* conversion, it is better to have two 32-bit stores here rather than*/
    /* one.  HLA loops require at least two instructions to be valid,     */
    /* and the compiler would end up inserting NOP padding, making HLA be */
    /* counter productive and inefficient.  The updates to dst1 and       */
    /* post_bytes are hoisted out of the loop itself.                     */
    /*--------------------------------------------------------------------*/
    post_bytes = len > 0 ? len : 0;
    if (len > 7)
    {
        for (i = 0; i < (len >> 3); i++)
        {
            *(int *)dst1 = wfill; dst1 += 4;
            *(int *)dst1 = wfill; dst1 += 4;
            post_bytes -= 8;
        }
    }

    /*--------------------------------------------------------------------*/
    /* Finish transfer 1-byte writes                                      */
    /*--------------------------------------------------------------------*/
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    if (post_bytes) { *dst1++ = fill; post_bytes--; }
    return dst;
}
