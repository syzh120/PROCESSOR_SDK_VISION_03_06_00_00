/**
 *  @file   std_qnx.h
 *
 *  @brief      TODO
 *
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2015, Texas Instruments Incorporated
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

#if !defined(STD_QNX_H)
#define STD_QNX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef IPC_BUILD_DEBUG
#ifndef IPC_BUILD_OPTIMIZE
/* Branch Prediction for likely true case */
#define EXPECT_TRUE(x)     (x)
/* Branch Prediction for likely false case */
#define EXPECT_FALSE(x)    (x)
#endif
#endif

#ifdef IPC_BUILD_RELEASE
/* Branch Prediction for likely true case */
#define EXPECT_TRUE(x)     __builtin_expect(!!(x), 1)
/* Branch Prediction for likely false case */
#define EXPECT_FALSE(x)    __builtin_expect(!!(x), 0)
#endif

#ifdef IPC_BUILD_OPTIMIZE
/* Branch Prediction for likely true case */
#define EXPECT_TRUE(x)     __builtin_expect(!!(x), 1)
/* Branch Prediction for likely false case */
#define EXPECT_FALSE(x)    __builtin_expect(!!(x), 0)
#endif

#endif /* if !defined(STD_QNX_H) */
