/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file file_api.h Wrapper API's to use FAT filesystem with MMC/SD
 *
 *******************************************************************************
 */

#ifndef FILE_API_H_
#define FILE_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/link_api/system.h>

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

/*
 *******************************************************************************
 * \brief Init Filesystem and MMCSD
 *
 *        Called during system init. User application should not call this API.
 *
 * \return 0 on success, else failure
 *******************************************************************************
 */
Int32 File_init(void);

/*
 *******************************************************************************
 * \brief De-Init Filesystem
 *
 *        Called during system deinit. User application should not call this API.
 *
 *******************************************************************************
 */
void  File_deInit(void);

/*
 *******************************************************************************
 * \brief Mount Filesystem
 *
 *        Called during system deinit. User application should not call this API.
 *
 *******************************************************************************
 */
void File_mountFs(void);

/*
 *******************************************************************************
 * \brief Un-Mount Filesystem
 *
 *        Called during system deinit. User application should not call this API.
 *
 *******************************************************************************
 */
void File_unmountFs(void);

/*
 *******************************************************************************
 * \brief Open a file in read or write mode
 *
 * \param filename [IN] MUST be in 8.3 format, long filename's not supported
 * \param mode     [IN] MUST be "rb" or "wb"
 *
 * \return -1 if file could not be opened, else file handle
 *******************************************************************************
 */
Int32 File_open(char *filename, char *mode);

/*
 *******************************************************************************
 * \brief Read from a file which is previously opened
 *
 * \param fd            [IN] File handle
 * \param dataBuf       [IN] buffer in which data will be read
 * \param bytesToRead   [IN] Number of bytes to read
 * \param bytesRead     [OUT] Number of bytes actually read
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_read(Int32 fd, UInt8 *dataBuf, UInt32 bytesToRead, UInt32 *bytesRead);

/*
 *******************************************************************************
 * \brief Write to a file which is previously opened
 *
 * \param fd        [IN] File handle
 * \param dataBuf   [IN] buffer from which data will be written
 * \param dataSize  [IN] Number of bytes to write
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_write(Int32 fd, UInt8 *dataBuf, UInt32 dataSize);

/*
 *******************************************************************************
 * \brief Write to a file which is previously opened
 *
 * \param fd        [IN] File handle
 * \param dataBuf   [IN] buffer from which data will be written
 * \param dataSize  [IN] Number of bytes to write
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_seek(Int32 fd,UInt32 offset);

/*
 *******************************************************************************
 * \brief Write to a file which is previously opened
 *
 * \param fd        [IN] File handle
 * \param dataBuf   [IN] buffer from which data will be written
 * \param dataSize  [IN] Number of bytes to write
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_chDir(char *dirName);

/*
 *******************************************************************************
 * \brief Write to a file which is previously opened
 *
 * \param fd        [IN] File handle
 * \param dataBuf   [IN] buffer from which data will be written
 * \param dataSize  [IN] Number of bytes to write
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_getCwd(char *dirName, UInt32 len);

/*
 *******************************************************************************
 * \brief Close a previously opened file
 *
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_close(Int32 fd);

/*
 *******************************************************************************
 * \brief Delete a file at the specified path
 *
 * \param filename [IN] MUST be in 8.3 format, long filename's not supported
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */
Int32 File_delete(char *filename);

/*
 *******************************************************************************
 * \brief Checks end of file
 *
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_eof(Int32 fd);

/*
 *******************************************************************************
 * \brief write a character to file
 *
 * \param character [IN] charcter to be written
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_putc(Int32 character, Int32 fd);

/*
 *******************************************************************************
 * \brief write a string to file
 *
 * \param str [IN] string to be written
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_puts(const char* str, Int32 fd);

/*
 *******************************************************************************
 * \brief get string from file
 *
 * \param buff [OUT] buffer to be filled with string from file
 * \param len [IN] length of the buffer to be read
 * \param fd [IN] File handle
 *
 * \return string read if success, else failure
 *******************************************************************************
 */

char* File_gets(char* buff, Int32 len, Int32 fd);

/*
 *******************************************************************************
 * \brief set position of file pointer to beginning
 *
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_rewind(Int32 fd);

/*
 *******************************************************************************
 * \brief get the status of file
 *
 * \param filename [IN] MUST be in 8.3 format, long filename's not supported
 *
 * \return file pointer position if success, else failure
 *******************************************************************************
 */

Int32 File_stat(char *filename);

/*
 *******************************************************************************
 * \brief get the current position of the file pointer
 *
 * \param fd [IN] File handle
 *
 * \return file pointer position if success, else failure
 *******************************************************************************
 */

Int64 File_tell(Int32 fd);

/*
 *******************************************************************************
 * \brief get the current working directory
 *
 @ \param buff [OUT] buffer to be filled with current working directory info
 * \param fd [IN] length of the buffer
 *
 * \return return buff if success, else failure
 *******************************************************************************
 */

char* File_getcwd(char* buff, Int32 len);

/*
 *******************************************************************************
 * \brief print data into file
 *
 * \param fd [IN] File handle
 * \param fmt [IN] data format
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_printf(Int32 fd, char* fmt, ...);

 /*
 *******************************************************************************
 * \brief print variable number of data into file
 *
 * \param fd [IN] File handle
 * \param fmt [IN] data format
 * \param apr [IN] va_list of arguments
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_vprintf(Int32 fd, char* fmt, va_list apr);

/*
 *******************************************************************************
 * \brief create directory
 *
 * \param path [IN] directory path to be created
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_mkdir(const char* path);

/*
 *******************************************************************************
 * \brief Check if directory exists
 *
 * \param path [IN] directory path
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_isdir(const char* path);

/*
 *******************************************************************************
 * \brief flush any write in buffer to file
 *
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_flush(Int32 fd);

/*
 *******************************************************************************
 * \brief check for file open error
 *
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_error(Int32 fd);

/*
 *******************************************************************************
 * \brief Query the file size
 *
 * \param fd [IN] File handle
 *
 * \return 0 if success, else failure
 *******************************************************************************
 */

Int32 File_size(Int32 fd);

/*
 * Utility wrapper APIs to read/write complete file's
 */
Int32 Utils_fileReadFile(char *fileName, UInt8 *addr, UInt32 readSize, Uint32 *actualReadSize);
Int32 Utils_fileWriteFile(char *fileName, Uint8 *addr, Uint32 size);


/*
 * Utility APIs to run basic file IO test
 */
void Utils_fileTestRun(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


