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

/**
 *   @Component    MEMUTIL
 *
 *   @Filename     MEMUTIL.h
 *
 *   @Description  Various memory fill/compare/copy utilites
 *                 Little bit slower but :
 *                 avoids DSP page boundary wrap problem;
 *                 avoids DSPMMU endianism conversion problem;
 *
 *    Available Functions:
 *                 MEMUTIL_FillConst32()
 *                 MEMUTIL_FillRamp32()
 *                 MEMUTIL_Compare32()
 *                 MEMUTIL_CompareConst32()
 *                 MEMUTIL_CompareRamp32()
 *                 MEMUTIL_Copy32()
 *                 MEMUTIL_FillConst16()
 *                 MEMUTIL_FillRamp16()
 *                 MEMUTIL_Compare16()
 *                 MEMUTIL_CompareConst16()
 *                 MEMUTIL_CompareRamp16()
 *                 MEMUTIL_Copy16()
 *                 MEMUTIL_FillConst8()
 *                 MEMUTIL_Compare8()
 *                 MEMUTIL_CompareRamp()
 *                 MEMUTIL_FillRamp()
 *                 MEMUTIL_FillRampwithEndianness()
 *
 *                        ================================
 *
 *   ARM Specific Functions:
 *                   MEMUTIL_BcopyByte  -- copies source array to destination array
 *                                         with 8-bit accesses
 *                   MEMUTIL_BcopyWord  -- copies source array to destination array
 *                                         with 16-bit accesses
 *                   MEMUTIL_BcopyDword -- copies source array to destination array
 *                                         with 32-bit accesses
 *                   MEMUTIL_BcopyBurst -- copies source array to destination array
 *                                         with burst accesses(8byte, 16byte or 32byte)
 *
 *                   MEMUTIL_BcmpByte  -- compares source array to destination array
 *                                         with 8-bit accesses
 *                   MEMUTIL_BcmpWord  -- compares source array to destination array
 *                                         with 16-bit accesses
 *                   MEMUTIL_BcmpDword -- compares source array to destination array
 *                                         with 32-bit accesses
 *                   MEMUTIL_BcmpBurst -- compares source array to destination array
 *                                         with burst accesses(8byte, 16byte)
 *
 *
 *  Domain:                 common
    *//*======================================================================== */
#ifndef __MEMUTIL_H
#define __MEMUTIL_H

/* ============================================================================
* INCLUDE FILES (only if necessary)
* =============================================================================
*/


#ifdef __cplusplus
extern "C"
{
#endif

/* ============================================================================
* EXPORTED DEFINITIONS
* =============================================================================
*/



/* ============================================================================
* EXPORTED TYPES
* =============================================================================
*/

#define __MPU__
#ifdef __MPU__

/* ----------------------------------------------------------------------------
* TYPE:         MEMUTIL_Btype
*
* DESCRIPTION:  Enumerated Type used to specify type of element to be copied
*               as part of a burst
*
* -----------------------------------------------------------------------------
*/
  typedef enum MEMUTIL_Btype_label
  {
    MEMUTIL_8_BYTE = 0,
    MEMUTIL_16_BYTE = 1,
    MEMUTIL_32_BYTE = 2
  } MEMUTIL_Btype_t, *pMEMUTIL_Btype_t;

#endif            /* __MPU__ */




/* ============================================================================
* EXPORTED VARIABLES
* =============================================================================
*/



/* ============================================================================
* EXPORTED FUNCTIONS
* =============================================================================
*/

                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_FillConst32
 *
 * @BRIEF         fills Length of uint32_t with Pattern
 *
 * @param[in]     StartAddress   Pointer to the begining of memory to be filled
 * @param[in]     Length         Number of uint32_t values to fill
 * @param[in]     Pattern        Value to be written from *StartAddress
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function fills Length of uint32_t starting from
 *                StartAddress with Pattern.
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_FillConst32 (uint32_t * StartAddress,
               uint32_t Length, uint32_t Pattern);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_FillRamp32
 *
 * @BRIEF         fills Length of uint32_t
 *
 * @param[in]     StartAddress   Pointer to the begining of memory to be filled
 * @param[in]     Length         Number of uint32_t values to fill
 * @param[in]     Pattern        Value to be written from *StartAddress
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function fills Length of uint32_t starting from
 *                StartAddress with Pattern logically ored with data ramp
 *                in range 0 to Length
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_FillRamp32 (uint32_t * StartAddress,
              uint32_t Length, uint32_t Pattern);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_Compare32
 *
 * @BRIEF         compares Length number of uint32_t values in two buffers
 *
 * @param[in]     B1Address   Pointer to the first memory buffer
 * @param[in]     B2Address   Pointer to the second memory buffer
 * @param[in]     Length      Number of uint32_t values to compare
 *
 * @RETURNS       Number of uint32_t values which differ in two buffers
 *
 * @DESCRIPTION   This function compares Length number of uint32_t
 *                values in two buffers begining from B1Address and
 *                B2Address. If function returns 0, this means that
 *                two buffers are identical
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_Compare32 (uint32_t * B1Address,
                 uint32_t * B2Address, uint32_t Length);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_CompareConst32
 *
 * @BRIEF         compares Length number of uint32_t values in a buffer
 *
 * @param[in]     B1Address   Pointer to the memory buffer
 * @param[in]     Pattern     Value to compare buffer content with
 * @param[in]     Length      Number of uint32_t values to compare
 *
 * @RETURNS       Number of uint32_t values which differ from Pattern
 *
 * @DESCRIPTION   This function comapres Length number of uint32_t
 *                values in buffer begining from B1Address with
 *                value. If function returns 0, this means that
 *                buffer is filled with value
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_CompareConst32 (uint32_t * B1Address,
                 uint32_t Pattern, uint32_t Length);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_CompareRamp32
 *
 * @BRIEF         compares Length number of uint32_t values in a buffer
 *
 * @param[in]     B1Address   Pointer to the memory buffer
 * @param[in]     Length      Number of uint32_t values to compare
 * @param[in]     Pattern     Value to compare buffer content with
 *
 * @RETURNS       Number of uint32_t values which differ from expected data
 *
 * @DESCRIPTION   This function comapres Length number of uint32_t
 *                values in buffer begining from B1Address with Pattern
 *                data logically ored with ramp data in range 0 to Length.
 *                If function returns 0, this means that
 *                buffer contains expected data
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_CompareRamp32 (uint32_t * B1Address,
                uint32_t Length, uint32_t Pattern);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_Copy32
 *
 * @BRIEF         copy values from a memory buffer to another
 *
 * @param[in]     Destination   Pointer to the destination memory buffer
 * @param[in]     Source        Pointer to the source memory buffer
 * @param[in]     Length        Number of uint32_t values to copy
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function copy Length number of uint32_t
 *                values from memory buffer begining at Source to
 *                mmeory buffer begining at Destination
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_Copy32 (uint32_t * Destination,
               uint32_t * Source, uint32_t Length);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_FillConst16
 *
 * @BRIEF         fills Length of uint16_t with Pattern
 *
 * @param[in]     StartAddress   Pointer to the begining of memory to be filled
 * @param[in]     Length         Number of uint16_t values to fill
 * @param[in]     Pattern        Value to be written from *StartAddress
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function fills Length of uint16_t starting from
 *                StartAddress with Pattern
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_FillConst16 (uint16_t * StartAddress,
               uint32_t Length, uint16_t Pattern);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_FillRamp16
 *
 * @BRIEF         fills Length of uint16_t
 *
 * @param[in]     StartAddress   Pointer to the begining of memory to be filled
 * @param[in]     Length         Number of uint16_t values to fill
 * @param[in]     Pattern        Value to be written from *StartAddress
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function fills Length of uint16_t starting from
 *                StartAddress with Pattern logically ored with data ramp
 *                in range 0 to Length
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_FillRamp16 (uint16_t * StartAddress,
              uint32_t Length, uint16_t Pattern);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_Compare16
 *
 * @BRIEF         compares Length number of uint16_t values in two buffers
 *
 * @param[in]     B1Address   Pointer to the first memory buffer
 * @param[in]     B2Address   Pointer to the second memory buffer
 * @param[in]     Length      Number of uint16_t values to compare
 *
 * @RETURNS       Number of uint16_t values which differ in two buffers
 *
 * @DESCRIPTION   This function comapres Length number of uint16_t
 *                values in two buffers begining from B1Address and
 *                B2Address. If function returns 0, this means that
 *                two buffers are identical
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_Compare16 (uint16_t * B1Address,
                 uint16_t * B2Address, uint32_t Length);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_CompareConst16
 *
 * @BRIEF         compares Length number of uint16_t values in a buffer
 *
 * @param[in]     B1Address   Pointer to the memory buffer
 * @param[in]     Pattern     Value to compare buffer content with
 * @param[in]     Length      Number of uint16_t values to compare
 *
 * @RETURNS       Number of uint16_t values which differs from Pattern
 *
 * @DESCRIPTION   This function comapres Length number of uint16_t
 *                values in buffer begining from B1Address with
 *                value. If function returns 0, this means that
 *                buffer is filled with value
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_CompareConst16 (uint16_t * B1Address,
                 uint16_t Pattern, uint32_t Length);


                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_CompareRamp16
 *
 * @BRIEF         compares Length number of uint16_t values in a buffer
 *
 * @param[in]     B1Address   Pointer to the memory buffer
 * @param[in]     Length      Number of uint16_t values to compare
 * @param[in]     Pattern     Value to compare buffer content with
 *
 * @RETURNS       Number of uint16_t values which differs from expected data
 *
 * @DESCRIPTION   This function comapres Length number of uint16_t
 *                values in buffer begining from B1Address with Pattern
 *                data logically ored with ramp data in range 0 to Length.
 *                If function returns 0, this means that
 *                buffer contains expected data
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_CompareRamp16 (uint16_t * B1Address,
                uint32_t Length, uint16_t Pattern);



                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_Copy16
 *
 * @BRIEF         copy values from a memory buffer to another
 *
 * @param[in]     Destination   Pointer to the destination memory buffer
 * @param[in]     Source        Pointer to the source memory buffer
 * @param[in]     Length        Number of uint16_t values to copy
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function copy Length number of uint16_t
 *                values from memory buffer begining at Source to
 *                mmeory buffer begining at Destination
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_Copy16 (uint16_t * Destination,
               uint16_t * Source, uint32_t Length);



                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_FillConst8
 *
 * @BRIEF         fills Length of uint8_t with Pattern
 *
 * @param[in]     StartAddress   Pointer to the begining of memory to be filled
 * @param[in]     Length         Number of uint8_t values to fill
 * @param[in]     Pattern        Value to be written from *StartAddress
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function fills Length of uint16_t starting from
 *                StartAddress with Pattern
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_FillConst8 (uint8_t * StartAddress,
              uint32_t Length, uint8_t Pattern);

                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_FillRamp8
 *
 * @BRIEF         fills Length of uint8_t
 *
 * @param[in]     StartAddress   Pointer to the begining of memory to be filled
 * @param[in]     Length         Number of uint8_t values to fill
 * @param[in]     Pattern        Value to be written from *StartAddress
 *
 * @RETURNS       void
 *
 * @DESCRIPTION   This function fills Length of uint8_t starting from
 *                StartAddress with Pattern logically ored with data ramp
 *                in range 0 to Length
 *
    *//*------------------------------------------------------------------------ */
  extern void MEMUTIL_FillRamp8 (uint8_t * StartAddress,
             uint32_t Length, uint8_t Pattern);

                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_Compare8
 *
 * @BRIEF         compares Length number of uint8_t values in two buffers
 *
 * @param[in]     B1Address   Pointer to the first memory buffer
 * @param[in]     B2Address   Pointer to the second memory buffer
 * @param[in]     Length      Number of uint8_t values to compare
 *
 * @RETURNS       Number of uint8_t values which differ in two buffers
 *
 * @DESCRIPTION   This function comapres Length number of uint8_t
 *                values in two buffers begining from B1Address and
 *                B2Address. If function returns 0, this means that
 *                two buffers are identical
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_Compare8 (uint8_t * B1Address,
                uint8_t * B2Address, uint32_t Length);

                                /* ------------------------------------------------------------------------*//**
 * @FUNCTION      MEMUTIL_CompareRamp8
 *
 * @BRIEF         compares Length number of uint8_t values in a buffer
 *
 * @param[in]     B1Address   Pointer to the memory buffer
 * @param[in]     Length      Number of uint32_t values to compare
 * @param[in]     Pattern     Value to compare buffer content with
 *
 * @RETURNS       Number of uint8_t values which differs from expected data
 *
 * @DESCRIPTION   This function comapres Length number of uint8_t
 *                values in buffer begining from B1Address with Pattern
 *                data logically ored with ramp data in range 0 to Length.
 *                If function returns 0, this means that
 *                buffer contains expected data
 *
    *//*------------------------------------------------------------------------ */
  extern uint32_t MEMUTIL_CompareRamp8 (uint8_t * B1Address,
               uint32_t Length, uint8_t Pattern);

/* ======================= ARM Specific Functions ============================= */



#ifdef __MPU__

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcopyByte
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint8_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint8_t *const
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of bytes to be copied
*
*
* RETURNS:        Nothing
*
* PURPOSE:      : Function copies data from the source array to destination array
*                 in 8-bit quantities
*
* METHOD:       : Check blkSize. If '0', return
*                 Copy the block of data from the soruce array to destination array
*
* -----------------------------------------------------------------------------
*/
  extern void MEMUTIL_BcopyByte (uint8_t const *pSrcArray,
             uint8_t * const pDstArray,
             const uint32_t blkSize);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcopyWord
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint16_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint16_t *const
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of words to be copied
*
*
* RETURNS:        Nothing
*
* PURPOSE:      : Function copies data from the source array to destination array
*                 in 16-bit quantities
*
* METHOD:       : Check blkSize. If '0', return
*                 Copy the block of data from the soruce array to destination array
*
* -----------------------------------------------------------------------------
*/
  extern void MEMUTIL_BcopyWord (uint16_t const *pSrcArray,
             uint16_t * const pDstArray,
             const uint32_t blkSize);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcopyDword
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint32_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint32_t *const
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of dwords to be copied
*
*
* RETURNS:        Nothing
*
* PURPOSE:      : Function copies data from the source array to destination array
*                 in 32-bit quantities
*
* METHOD:       : Check blkSize. If '0', return
*                 Copy the block of data from the soruce array to destination array
*
* -----------------------------------------------------------------------------
*/
  extern void MEMUTIL_BcopyDword (uint32_t const *pSrcArray,
              uint32_t * const pDstArray,
              const uint32_t blkSize);


/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcopyBurst
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint32_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint32_t *const
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of blocks to be copied
*
*   Identifier  : blkType
*   Type        : const MEMUTIL_Btype_t
*   Description : The block type  (whether 8 byte,16 byte or 32-byte)
*
*
* RETURNS:        Nothing
*
* PURPOSE:      : Function copies data from the source array to destination array
*                 in blkType quantities
*
* METHOD:       : Check blkSize. If '0', return
*                 Copy the block of data from the soruce array to destination array
*
* -----------------------------------------------------------------------------
*/
  extern void MEMUTIL_BcopyBurst (uint32_t const *pSrcArray,
              uint32_t * const pDstArray,
              const uint32_t blkSize,
              const MEMUTIL_Btype_t blkType);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcmpByte
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint8_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint8_t const *
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of bytes to be compared
*
*
* RETURNS:
*
*    Type       : int32_t
*
*                 0 = Comparison was successful
*                -1 = Comparison failed
*
* PURPOSE:      : Function compares data from the source array to destination array
*                 in 8-bit quantities
*
* METHOD:       : Check blkSize. If '0', return 0
*                 Compare the block of data from the soruce array with destination array
*                 If comparison is successful, return 0 else -1
*
* -----------------------------------------------------------------------------
*/
  extern int32_t MEMUTIL_BcmpByte (uint8_t const *pSrcArray,
               uint8_t const *pDstArray,
               const uint32_t blkSize);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcmpWord
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint16_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint16_t const *
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of words to be compared
*
*
* RETURNS:
*
*    Type       : int32_t
*
*                 0 = Comparison was successful
*                -1 = Comparison failed
*
* PURPOSE:      : Function compares data from the source array to destination array
*                 in 16-bit quantities
*
* METHOD:       : Check blkSize. If '0', return 0
*                 Compare the block of data from the soruce array with destination array
*                 If comparison is successful, return 0 else -1
*
* -----------------------------------------------------------------------------
*/
  extern int32_t MEMUTIL_BcmpWord (uint16_t const *pSrcArray,
               uint16_t const *pDstArray,
               const uint32_t blkSize);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcmpDword
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint32_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint32_t const *
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of dwords to be compared
*
*
* RETURNS:
*
*    Type       : int32_t
*
*                 0 = Comparison was successful
*                -1 = Comparison failed
*
* PURPOSE:      : Function compares data from the source array to destination array
*                 in 32-bit quantities
*
* METHOD:       : Check blkSize. If '0', return 0
*                 Compare the block of data from the soruce array with destination array
*                 If comparison is successful, return 0 else -1
*
* -----------------------------------------------------------------------------
*/
  extern int32_t MEMUTIL_BcmpDword (uint32_t const *pSrcArray,
                uint32_t const *pDstArray,
                const uint32_t blkSize);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_BcmpBurst
*
* INPUTS:
*
*   Identifier  : pSrcArray
*   Type        : uint32_t const *
*   Description : Pointer to the source array
*
*   Identifier  : pDstArray
*   Type        : uint32_t const *
*   Description : Pointer to the destination array
*
*   Identifier  : blkSize
*   Type        : const uint32_t
*   Description : The number of blocks to be compared
*
*   Identifier  : blkType
*   Type        : const MEMUTIL_Btype_t
*   Description : The block type  (whether 8 byte,16 byte)
*
*
* RETURNS:
*
*    Type       : int32_t
*
*                 0 = Comparison was successful
*                -1 = Comparison failed
*
* PURPOSE:      : Function compares data from the source array to destination array
*                 in blktype quantities
*
* METHOD:       : Check blkSize. If '0', return 0
*                 Compare the block of data from the soruce array with destination array
*                 If comparison is successful, return 0 else -1
*
* -----------------------------------------------------------------------------
*/
  extern int32_t MEMUTIL_BcmpBurst (uint32_t const *pSrcArray,
                uint32_t const *pDstArray,
                const uint32_t blkSize,
                const MEMUTIL_Btype_t blkType);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_FillRamp
*
*
*
* PURPOSE:       : This function fills Length of uint32_t, uint16_t and uint8_t
*           starting from
*                      Address with Pattern logically ored with data ramp
*                         in range 0 to Length.
*
* -----------------------------------------------------------------------------
*/

  extern void MEMUTIL_FillRamp (uint32_t * Address,
            uint32_t Length,
            uint32_t Pattern, uint32_t datasize);


/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_CompareRamp
*
*
* PURPOSE:       : This function comapres Length number of uint32_t, uint16_t
*                 and uint8_t values in buffer begining from Address with Pattern
*                 data logically ored with ramp data in range 0 to Length.
*                 If function returns 0, this means that
*                 buffer contains expected data.
*
* -----------------------------------------------------------------------------
*/

  extern uint32_t MEMUTIL_CompareRamp (uint32_t * Address,
                   uint32_t Length,
                   uint32_t Pattern,
                   uint32_t datasize, uint32_t endianess);

/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_FillRampwithEndianness
*
*
* PURPOSE:       : Same as MEMUTIL_FillRamp with endianess support
*
* -----------------------------------------------------------------------------
*/

  void MEMUTIL_FillRampwithEndianness (uint32_t * Address,
                   uint32_t Length,
                   uint32_t Pattern,
                   uint32_t datasize, uint32_t endianess);



/* ----------------------------------------------------------------------------
* FUNCTION      : MEMUTIL_Compare
*
*
* PURPOSE:       :Compare source and destination with endianess support
*
* -----------------------------------------------------------------------------
*/
  uint32_t MEMUTIL_Compare (uint32_t * AddressSrc,
             uint32_t * AddressDst,
             uint32_t LengthinWords,
             uint16_t datasize, uint32_t endianess);



#endif            /* __MPU__ */



#ifdef __cplusplus
}
#endif

#endif            /* __MEMUTIL_H */

/* EOF */
