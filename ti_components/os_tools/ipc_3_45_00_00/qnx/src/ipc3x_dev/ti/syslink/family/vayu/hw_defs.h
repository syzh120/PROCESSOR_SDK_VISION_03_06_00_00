/*
 *  @file  hw_defs.h
 *
 *  @brief  Definitions required for HW module
 *
 *
 *  ============================================================================
 *
 *  Copyright (c) 2013, Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *  *  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  *  Neither the name of Texas Instruments Incorporated nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  Contact information for paper mail:
 *  Texas Instruments
 *  Post Office Box 655303
 *  Dallas, Texas 75265
 *  Contact information:
 *  http://www-k.ext.ti.com/sc/technical-support/product-information-centers.htm?
 *  DCMP=TIHomeTracking&HQS=Other+OT+home_d_contact
 *  ============================================================================
 *
 */

#ifndef __HW_DEFS_H
#define __HW_DEFS_H

#include <GlobalTypes.h>

/* Page size */
#define HW_PAGE_SIZE_4KB   0x1000
#define HW_PAGE_SIZE_64KB  0x10000
#define HW_PAGE_SIZE_1MB   0x100000
#define HW_PAGE_SIZE_16MB  0x1000000

/* hw_status:  return type for HW API */
typedef long hw_status;

/* hw_set_clear_t:  Enumerated Type used to set and clear any bit */
enum hw_set_clear_t {
    HW_CLEAR,
    HW_SET
} ;

/* hw_endianism_t:  Enumerated Type used to specify the endianism
 *        Do NOT change these values. They are used as bit fields. */
enum hw_endianism_t {
    HW_LITTLE_ENDIAN,
    HW_BIG_ENDIAN

} ;

/* hw_elemnt_siz_t:  Enumerated Type used to specify the element size
 *        Do NOT change these values. They are used as bit fields. */
enum hw_elemnt_siz_t {
    HW_ELEM_SIZE_8BIT,
    HW_ELEM_SIZE_16BIT,
    HW_ELEM_SIZE_32BIT,
    HW_ELEM_SIZE_64BIT

} ;

/* HW_IdleMode_t:  Enumerated Type used to specify Idle modes */
enum HW_IdleMode_t {
    HW_FORCE_IDLE,
    HW_NO_IDLE,
    HW_SMART_IDLE
} ;

#endif  /* __HW_DEFS_H */
