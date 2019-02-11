/**
 *  @file   String.h
 *
 *  @brief      Defines for String manipulation library.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2011-2012, Texas Instruments Incorporated
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


#ifndef UTILS_STRING_H_0XEFC8
#define UTILS_STRING_H_0XEFC8


#if defined (__cplusplus)
//extern "C" {
#endif


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Function to add a string at the end of another one */
String String_cat (String s1, String s2);

/* Function to compare two string */
Int String_cmp (String s1, String s2);

/* Function to compare two string only first n characters */
Int String_ncmp (String s1, String s2, UInt32 n);

/* Function to copy strings */
String String_cpy (String s1, String s2);

/* Function to copy first n bytes from s2 to s1 */
String String_ncpy (String s1, String s2, UInt32 n);

/* Function to returns the number of characters in s */
Int String_len (String s);

/* Function to returns the number of characters in s up to max of n */
Int String_nlen (String s, UInt32 n);

/* Function to get string representation of a hex number */
Int String_hexToStr (String s, UInt32 hex);

/* Function to calculate hash for a string */
UInt32 String_hash (String s);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* STRING_H_0X5B4D */
