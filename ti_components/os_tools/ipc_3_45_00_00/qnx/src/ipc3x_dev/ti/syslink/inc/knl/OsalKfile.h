/**
 *  @file   OsalKfile.h
 *
 *  @brief      Kernel File operation interface definitions.
 *
 *              This abstracts the file operation interface in the Kernel
 *              code. All the usual operations like open, close, read, write,
 *              seek and tell will be supported.
 *
 *
 *  @ver        02.00.00.46_alpha1
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2009, Texas Instruments Incorporated
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


#ifndef OSALKFILE_H_0x3046
#define OSALKFILE_H_0x3046


/* OSAL and utils */


#if defined (__cplusplus)
extern "C" {
#endif


/*!
 *  @def    OSALKFILE_MODULEID
 *  @brief  Module ID for OsalKfile OSAL module.
 */
#define OSALKFILE_MODULEID                 (UInt16) 0x3046

/* =============================================================================
 *  All success and failure codes for the module
 * =============================================================================
 */
/*!
* @def   OSALKFILE_STATUSCODEBASE
* @brief Stauts code base for MEMORY module.
*/
#define OSALKFILE_STATUSCODEBASE      (OSALKFILE_MODULEID << 12u)

/*!
* @def   OSALKFILE_MAKE_FAILURE
* @brief Convert to failure code.
*/
#define OSALKFILE_MAKE_FAILURE(x)    ((Int) (0x80000000  \
                                      + (OSALKFILE_STATUSCODEBASE + (x))))
/*!
* @def   OSALKFILE_MAKE_SUCCESS
* @brief Convert to success code.
*/
#define OSALKFILE_MAKE_SUCCESS(x)      (OSALKFILE_STATUSCODEBASE + (x))

/*!
* @def   OSALKFILE_E_MEMORY
* @brief Indicates OsalKfile alloc/free failure.
*/
#define OSALKFILE_E_MEMORY             OSALKFILE_MAKE_FAILURE(1)

/*!
* @def   OSALKFILE_E_INVALIDARG
* @brief Invalid argument provided
*/
#define OSALKFILE_E_INVALIDARG         OSALKFILE_MAKE_FAILURE(2)

/*!
* @def   OSALKFILE_E_FAIL
* @brief Generic failure
*/
#define OSALKFILE_E_FAIL               OSALKFILE_MAKE_FAILURE(3)

/*!
* @def   OSALKFILE_E_OUTOFRANGE
* @brief Indicates that specified value is out of range
*/
#define OSALKFILE_E_OUTOFRANGE         OSALKFILE_MAKE_FAILURE(4)

/*!
 *  @def    OSALKFILE_E_FILEOPEN
 *  @brief  Failure to open the file.
 */
#define OSALKFILE_E_FILEOPEN           OSALKFILE_MAKE_FAILURE(5)

/*!
 *  @def    OSALKFILE_E_FILEREAD
 *  @brief  Failure to read from the file.
 */
#define OSALKFILE_E_FILEREAD           OSALKFILE_MAKE_FAILURE(6)

/*!
 *  @def    OSALKFILE_E_HANDLE
 *  @brief  Invalid handle provided
 */
#define OSALKFILE_E_HANDLE             OSALKFILE_MAKE_FAILURE(7)

/*!
* @def   OSALKFILE_SUCCESS
* @brief Operation successfully completed
*/
#define OSALKFILE_SUCCESS              OSALKFILE_MAKE_SUCCESS(0)


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Declaration for the OsalKfile object handle.
 *          Definition of OsalKfile_Object is not exposed.
 */
typedef struct OsalKfile_Object * OsalKfile_Handle;

/*!
 *  @brief   Enumerates the values used for repositioning the file position
 *           indicator.
 */
typedef enum {
    OsalKfile_Pos_SeekSet  = 0x0,
    /* !< Seek from beginning of file. */
    OsalKfile_Pos_SeekCur  = 0x1,
    /* !< Seek from current position. */
    OsalKfile_Pos_SeekEnd  = 0x2,
    /* !< Seek from end of file. */
    OsalKfile_Pos_EndValue = 0x3
    /*!< End delimiter indicating start of invalid values for this enum */
} OsalKfile_Pos;


/* =============================================================================
 *  APIs
 * =============================================================================
 */
/* Opens the file object. */
Int OsalKfile_open (String             fileName,
                    Char *             fileMode,
                    OsalKfile_Handle * fileHandle);

/* Closes the underlying file. */
Int OsalKfile_close (OsalKfile_Handle * fileHandle);

/* Reads the block of data from current position in the file. */
Int OsalKfile_read (OsalKfile_Handle fileHandle,
                    Char *           buffer,
                    UInt32           size,
                    UInt32           count);

/* Repositions the file pointer according to specified arguments.*/
Int OsalKfile_seek (OsalKfile_Handle fileHandle,
                    Int32            offset,
                    OsalKfile_Pos    pos);

/* Returns the current file pointer position for a specified file handle. */
UInt32 OsalKfile_tell (OsalKfile_Handle fileHandle);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* ifndef OSALKFILE_H_0x3046 */
