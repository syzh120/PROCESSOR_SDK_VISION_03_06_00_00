/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


/* ============================================================================
* STANDARD INCLUDE FILES
* =============================================================================
*/
#include "stdint.h"
#include "stdint.h"
#include "hw_types.h"


/* ============================================================================
* PROJECT SPECIFIC INCLUDE FILES
* =============================================================================
*/


/* ============================================================================
* GLOBAL VARIABLES DECLARATIONS
* =============================================================================
*/


/* ============================================================================
* LOCAL TYPES AND DEFINITIONS
* =============================================================================
*/

#if defined(__UMA__) || defined(C55)

   #ifndef __TMS320C55X_PLUS_BYTE__
          #define MEMUTIL_DSP_ADJUST  >> 1
   #else
      #define MEMUTIL_DSP_ADJUST
   #endif

#else
    #define MEMUTIL_DSP_ADJUST
#endif

#define LITTLE (0x78563412)
#define   BIG  (0x12345678)
/* ============================================================================
* LOCAL VARIABLES DECLARATIONS
* =============================================================================
*/


/* ============================================================================
* LOCAL FUNCTIONS PROTOTYPES
* =============================================================================
*/


/* ============================================================================
* FUNCTIONS
* =============================================================================
*/


/*==================== Function Separator =============================*/
void MEMUTIL_FillConst32( uint32_t *StartAddress,
                          uint32_t  Length,
                          uint32_t  Pattern )
{

    uint32_t count;
    uint32_t *addr;
    uint32_t tmp_l;

    tmp_l = (uint32_t)StartAddress;

    for ( count = 0; count < Length; count++ )
    {
        addr = (uint32_t *)tmp_l;
        *addr = Pattern;
        tmp_l += (4 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_FillConst32() */



/*==================== Function Separator =============================*/
void MEMUTIL_FillRamp32( uint32_t *StartAddress,
                         uint32_t  Length,
                         uint32_t  Pattern )
{

    uint32_t count;
    uint32_t *addr;
    uint32_t tmp_l;

    tmp_l = (uint32_t)StartAddress;

    for ( count = 0; count < Length; count++ )
    {
        addr = (uint32_t *)tmp_l;
        *addr = count | Pattern;
        tmp_l += (4 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_FillRamp32() */



/*==================== Function Separator =============================*/
uint32_t MEMUTIL_Compare32( uint32_t *B1Address,
                           uint32_t *B2Address,
                           uint32_t  Length )
{

    uint32_t count;
    uint32_t *b1;
    uint32_t *b2;
    uint32_t tmp_l1;
    uint32_t tmp_l2;
    uint32_t error_count;

    tmp_l1 = (uint32_t)B1Address;
    tmp_l2 = (uint32_t)B2Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint32_t *)tmp_l1;
        b2 = (uint32_t *)tmp_l2;
        if ( *b1 != *b2 )
        {
            error_count ++;
        }

        tmp_l1 += (4 MEMUTIL_DSP_ADJUST);
        tmp_l2 += (4 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_Compare32() */



/*==================== Function Separator =============================*/
uint32_t MEMUTIL_CompareConst32( uint32_t *B1Address,
                                uint32_t  Pattern,
                                uint32_t  Length )
{

    uint32_t count;
    uint32_t *b1;
    uint32_t tmp_l1;
    uint32_t error_count;

    tmp_l1 = (uint32_t)B1Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint32_t *)tmp_l1;
        if ( *b1 != Pattern )
        {
            error_count ++;
        }

        tmp_l1 += (4 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_CompareConst32() */



/*==================== Function Separator =============================*/
uint32_t MEMUTIL_CompareRamp32( uint32_t *B1Address,
                               uint32_t  Length,
                               uint32_t  Pattern )
{

    uint32_t count;
    uint32_t *b1;
    uint32_t tmp_l;
    uint32_t error_count;


    tmp_l = (uint32_t)B1Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint32_t *)tmp_l;
        if ( *b1 != (count | Pattern) )
        {
            error_count++;
        }
        tmp_l += (4 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_CompareRamp32() */



/*==================== Function Separator =============================*/
void MEMUTIL_Copy32( uint32_t *Destination,
                     uint32_t *Source,
                     uint32_t  Length )
{

    uint32_t count;
    uint32_t *dst;
    uint32_t *src;
    uint32_t tmp_l1;
    uint32_t tmp_l2;

    tmp_l1 = (uint32_t)Destination;
    tmp_l2 = (uint32_t)Source;

    for ( count = 0; count < Length; count++ )
    {
        dst = (uint32_t *)tmp_l1;
        src = (uint32_t *)tmp_l2;

        *dst = *src;

        tmp_l1 += (4 MEMUTIL_DSP_ADJUST);
        tmp_l2 += (4 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_Copy32() */



/*==================== Function Separator =============================*/
void MEMUTIL_FillConst16( uint16_t *StartAddress,
                          uint32_t  Length,
                          uint16_t  Pattern )
{

    uint32_t count;
    uint16_t *addr;
    uint32_t tmp_l;

    tmp_l = (uint32_t)StartAddress;

    for ( count = 0; count < Length; count++ )
    {
        addr = (uint16_t *)tmp_l;
        *addr = Pattern;
        tmp_l += (2 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_FillConst16() */



/*==================== Function Separator =============================*/
void MEMUTIL_FillRamp16( uint16_t *StartAddress,
                         uint32_t  Length,
                         uint16_t  Pattern )
{

    uint32_t count;
    uint16_t *addr;
    uint32_t tmp_l;

    tmp_l = (uint32_t)StartAddress;

    for ( count = 0; count < Length; count++ )
    {
        addr = (uint16_t *)tmp_l;
        *addr = (uint16_t)count | Pattern;
        tmp_l += (2 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_FillRamp16() */



/*==================== Function Separator =============================*/
uint32_t MEMUTIL_Compare16( uint16_t *B1Address,
                           uint16_t *B2Address,
                           uint32_t  Length )
{

    uint32_t count;
    uint16_t *b1;
    uint16_t *b2;
    uint32_t tmp_l1;
    uint32_t tmp_l2;
    uint32_t error_count;

    tmp_l1 = (uint32_t)B1Address;
    tmp_l2 = (uint32_t)B2Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint16_t *)tmp_l1;
        b2 = (uint16_t *)tmp_l2;
        if ( *b1 != *b2 )
        {
            error_count ++;
        }

        tmp_l1 += (2 MEMUTIL_DSP_ADJUST);
        tmp_l2 += (2 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_Compare16() */



/*==================== Function Separator =============================*/
uint32_t MEMUTIL_CompareConst16( uint16_t *B1Address,
                                uint16_t  Pattern,
                                uint32_t  Length )
{

    uint32_t count;
    uint16_t *b1;
    uint32_t tmp_l1;
    uint32_t error_count;

    tmp_l1 = (uint32_t)B1Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint16_t *)tmp_l1;
        if ( *b1 != Pattern )
        {
            error_count ++;
        }

        tmp_l1 += (2 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_CoompareConst16() */



/*==================== Function Separator =============================*/
uint32_t MEMUTIL_CompareRamp16( uint16_t *B1Address,
                               uint32_t  Length,
                               uint16_t  Pattern )
{

    uint32_t count;
    uint16_t *b1;
    uint32_t tmp_l;
    uint32_t error_count;


    tmp_l = (uint32_t)B1Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint16_t *)tmp_l;
        if ( *b1 != (count | Pattern) )
        {
            error_count++;
        }
        tmp_l += (2 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_CompareRamp16() */

uint32_t MEMUTIL_Compare(uint32_t *AddressSrc,
                        uint32_t *AddressDst,
                        uint32_t LengthinWords,
                        uint16_t datasize,
                        uint32_t endianess)
{
    uint32_t count = 0;

    //fprintf(UARTW, "Verifying %lx (%ld) words endianess=%08lx\r\n", LengthinWords, LengthinWords, endianess);

    if (datasize == 8)
    {
        uint8_t *AddressSrc8 = (uint8_t*) AddressSrc;
        uint8_t *AddressDst8 = (uint8_t*) AddressDst;

        while (LengthinWords--)
        {
            uint8_t src1, src2, src3, src4, dst1, dst2, dst3, dst4;

            src1 = *AddressSrc8++;
            src2 = *AddressSrc8++;
            src3 = *AddressSrc8++;
            src4 = *AddressSrc8++;
            dst1 = *AddressDst8++;
            dst2 = *AddressDst8++;
            dst3 = *AddressDst8++;
            dst4 = *AddressDst8++;

            if (endianess == LITTLE)
            {
                if (src1 != dst1)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-4, src1, AddressDst8-4, dst1); */
                }
                if (src2 != dst2)
                {
                   count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-3, src2, AddressDst8-3, dst2); */
                }
                if (src3 != dst3)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-2, src3, AddressDst8-2, dst3); */
                }
                if (src4 != dst4)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-1, src4, AddressDst8-1, dst4);*/
                }
            }
            else
            {
                if (src1 != dst4)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-4, src1, AddressDst8-4, dst4); */
                }
                if (src2 != dst3)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-3, src2, AddressDst8-3, dst3); */
                }
                if (src3 != dst2)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-2, src2, AddressDst8-2, dst2); */
                }
                if (src4 != dst1)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc8-1, src4, AddressDst8-1, dst1); */
                }
            }
        }
    }

    if (datasize == 16)
    {
        uint16_t *AddressSrc16 = (uint16_t*) AddressSrc;
        uint16_t *AddressDst16 = (uint16_t*) AddressDst;

        while (LengthinWords--)
        {
            uint16_t src1, src2, dst1, dst2;

            src1 = *AddressSrc16++;
            src2 = *AddressSrc16++;
            dst1 = *AddressDst16++;
            dst2 = *AddressDst16++;

            if (endianess == LITTLE)
            {
                if (src1 != dst1)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc16-2, src1, AddressDst16-2, dst1); */
                }
                if (src2 != dst2)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc16-1, src2, AddressDst16-1, dst2); */
                }
            }
            else
            {
                if (src1 != dst2)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc16-2, src1, AddressDst16-2, dst2); */
                }
                if (src2 != dst1)
                {
                    count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc16-1, src2, AddressDst16-1, dst1); */
                }
            }
        }
    }

    if (datasize == 32)
    {
        while (LengthinWords--)
        {
            uint32_t src, dst;

            src = *AddressSrc++;
            dst = *AddressDst++;

            if (src != dst)
            {
                count++; /*fprintf(UARTW, "fail @%06lx=%04x @%06lx=%04x\r\n", AddressSrc, src, AddressDst, dst); */
            }
        }
    }

    return (count);
}


/*==================== Function Separator =============================*/
void MEMUTIL_Copy16( uint16_t *Destination,
                     uint16_t *Source,
                     uint32_t  Length )
{

    uint32_t count;
    uint16_t *dst;
    uint16_t *src;
    uint32_t tmp_l1;
    uint32_t tmp_l2;

    tmp_l1 = (uint32_t)Destination;
    tmp_l2 = (uint32_t)Source;

    for ( count = 0; count < Length; count++ )
    {
        dst = (uint16_t *)tmp_l1;
        src = (uint16_t *)tmp_l2;

        *dst = *src;

        tmp_l1 += (2 MEMUTIL_DSP_ADJUST);
        tmp_l2 += (2 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_Copy16() */


/*==================== Function Separator =============================*/
void MEMUTIL_FillConst8( uint8_t *StartAddress,
                         uint32_t  Length,
                         uint8_t  Pattern )
{

    uint32_t count;
    uint8_t  *addr;
    uint32_t tmp_l;

    tmp_l = (uint32_t)StartAddress;

    for ( count = 0; count < Length; count++ )
    {
        addr = (uint8_t *)tmp_l;
        *addr = Pattern;
        tmp_l += (1 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_FillConst8() */

/*==================== Function Separator =============================*/
void MEMUTIL_FillRamp8( uint8_t *StartAddress,
                         uint32_t  Length,
                         uint8_t  Pattern )
{

    uint32_t count;
    uint8_t *addr;
    uint32_t tmp_l;

    tmp_l = (uint32_t)StartAddress;

    for ( count = 0; count < Length; count++ )
    {
        addr = (uint8_t *)tmp_l;
        *addr = (uint8_t)count | Pattern;
        tmp_l += (1 MEMUTIL_DSP_ADJUST);
    }

} /* MEMUTIL_FillRamp8() */

/*==================== Function Separator =============================*/
uint32_t MEMUTIL_Compare8( uint8_t *B1Address,
                           uint8_t *B2Address,
                           uint32_t  Length )
{

    uint32_t count;
    uint8_t *b1;
    uint8_t *b2;
    uint32_t tmp_l1;
    uint32_t tmp_l2;
    uint32_t error_count;

    tmp_l1 = (uint32_t)B1Address;
    tmp_l2 = (uint32_t)B2Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint8_t *)tmp_l1;
        b2 = (uint8_t *)tmp_l2;
        if ( *b1 != *b2 )
        {
            error_count ++;
        }

        tmp_l1 += (1 MEMUTIL_DSP_ADJUST);
        tmp_l2 += (1 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_Compare8() */

/*==================== Function Separator =============================*/
uint32_t MEMUTIL_CompareRamp8( uint8_t *B1Address,
                               uint32_t  Length,
                               uint8_t  Pattern )
{

    uint32_t count;
    uint8_t *b1;
    uint32_t tmp_l;
    uint32_t error_count;


    tmp_l = (uint32_t)B1Address;
    error_count = 0L;

    for ( count = 0; count < Length; count++ )
    {
        b1 = (uint8_t *)tmp_l;
        if ( *b1 != (count | Pattern) )
        {
            error_count++;
        }
        tmp_l += (1 MEMUTIL_DSP_ADJUST);
    }

    return error_count;

} /* MEMUTIL_CompareRamp8() */

/*==================== Function Separator =============================*/
static __inline uint32_t switch_endianess(uint32_t a, uint32_t endianess)
{
   if (endianess == BIG)
     return (((a & 0xff) << 24) | ((a & 0xff00) << 8) | ((a & 0xff0000) >> 8) | ((a & 0xff000000) >> 24));
   return (a);
}

uint32_t MEMUTIL_CompareRamp(uint32_t *Address,
                            uint32_t Length,
                            uint32_t Pattern,
                            uint32_t datasize,
                            uint32_t endianess)
{
   /* Pre-Condition: Address must be 4 word aligned */
   uint32_t count;
   uint32_t count_Pattern;
   uint32_t errors;
   /*
   32/32 -> 1
   32/16 -> 2
   32/8  -> 4
    */
   uint32_t and8[4] = { 0xff, 0xff00, 0xff0000, 0xff000000 };
   uint32_t and16[4] = { 0xffff, 0xffff0000 };
   uint32_t shift8[4] = { 0, 8, 16, 24 };
   uint32_t shift16[4] = { 0, 16 };

   errors = count_Pattern = 0;
   for (count = 0; count < Length; count += (32 / datasize))
   {
      uint32_t tmp32;
      uint32_t j;

      tmp32 = switch_endianess(*(Address++), endianess);
      switch (datasize)
      {
      case 8:
          for (j = 0; j < 4; ++j)
         if (((tmp32 & and8[j]) >> shift8[j]) != ((count_Pattern++ & 0xff) | Pattern))
          errors++;
          break;
      case 16:
          for (j = 0; j < 2; ++j)
         if (((tmp32 & and16[j]) >> shift16[j]) != ((count_Pattern++ & 0xffff) | Pattern))
          errors++;

          break;
      case 32:
          if (tmp32 != (count_Pattern++ | Pattern))
          errors++;
          break;
      default:
          errors++;
      }
   }
   return (errors);
}

/*==================== Function Separator =============================*/

void MEMUTIL_FillRamp(uint32_t *Address,
                      uint32_t Length,
                      uint32_t Pattern,
                      uint32_t datasize)
{
   /* Pre-Condition: Address must be 4 word aligned */
   uint32_t count;
   uint32_t count_Pattern;
   /*
   32/32 -> 1
   32/16 -> 2
   32/8  -> 4
    */
   uint32_t shift8[4] = { 0, 8, 16, 24 };
   uint32_t shift16[4] = { 0, 16 };

   count_Pattern = 0;
   for (count = 0; count < Length; count += (32 / datasize))
   {
      uint32_t j;

      switch (datasize)
      {
      case 8:
         *Address = 0;
          for (j = 0; j < 4; ++j)
         *Address |= (((count_Pattern++ & 0xff) | Pattern) << shift8[j]);
          break;
      case 16:
         *Address = 0;
          for (j = 0; j < 2; ++j)
         *Address |= (((count_Pattern++ & 0xffff) | Pattern) << shift16[j]);
          break;
      case 32:
          *Address = (count_Pattern++ | Pattern);
          break;
      }
      ++Address;
   }
}

/*==================== Function Separator =============================*/

void MEMUTIL_FillRampwithEndianness(uint32_t *Address,
                                    uint32_t Length,
                                    uint32_t Pattern,
                                    uint32_t datasize,
                                    uint32_t endianess)
{
  /* Pre-Condition: Address must be 4 word aligned */
  uint32_t count;
  uint32_t count_Pattern;
  /*
     32/32 -> 1
     32/16 -> 2
     32/8  -> 4
   */
  uint32_t shift8[4] = { 0, 8, 16, 24 };
  uint32_t shift16[4] = { 0, 16 };

  count_Pattern = 0;
  for (count = 0; count < Length; count += (32 / datasize))
  {
    uint32_t j;

    switch (datasize)
    {
      case 8:
        *Address = 0;
        for (j = 0; j < 4; ++j)
          *Address |= (((count_Pattern++ & 0xff) | Pattern) << shift8[j]);
        break;
      case 16:
        *Address = 0;
        for (j = 0; j < 2; ++j)
          *Address |= (((count_Pattern++ & 0xffff) | Pattern) << shift16[j]);
        break;
      case 32:
        *Address = (count_Pattern++ | Pattern);
        break;
    }
    *Address = switch_endianess(*Address, endianess);
    ++Address;
  }
}

/* EOF */
