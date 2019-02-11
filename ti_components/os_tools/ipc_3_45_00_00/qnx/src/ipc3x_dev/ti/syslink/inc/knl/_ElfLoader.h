/**
 *  @file   _ElfLoader.h
 *
 *  @brief      Internal header for loader for ELF format.
 *
 *  ============================================================================
 *
 *  Copyright (c) 2008-2012, Texas Instruments Incorporated
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


#ifndef _ElfLoader_H_0x1bc5
#define _ElfLoader_H_0x1bc5


/* Module headers */
#include <LoaderDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 *  See ElfLoader.h, LoaderDefs.h
 * =============================================================================
 */


/* =============================================================================
 *  Internal functions accessed through function table
 * =============================================================================
 */
/* Function to attach to the Loader. */
Int ElfLoader_attach (Loader_Handle handle, Loader_AttachParams * params);

/* Function to detach from the Loader. */
Int ElfLoader_detach (Loader_Handle handle);

/* Function to load the slave processor.
 * Returns file ID in the passed fileId parameter.
 */
Int ElfLoader_load (Loader_Handle   handle,
                    String          imagePath,
                    UInt32          argc,
                    String *        argv,
                    Ptr             params,
                    UInt32 *        fileId);

/* Function to load symbols for the specified file. This will allow the symbols
 * to be usable when linked against another object file.
 * External symbols will be made available for global symbol linkage.
 * NOTE: This function is only relevant for dynamic loader. Other loaders can
 *       return ELFLOADER_E_NOTIMPL.
 */
Int ElfLoader_loadSymbols (Loader_Handle handle,
                           String        imagePath,
                           Ptr           params);

/* Function to unload the previously loaded file on the slave processor.
 * The fileId received from the load function must be passed to this
 * function.
 */
Int ElfLoader_unload (Loader_Handle handle, UInt32 fileId);

/* Function to retrieve the target address of a symbol from the specified file.
 * The fileId received from the load function must be passed to this
 * function.
 */
Int ElfLoader_getSymbolAddress (Loader_Handle   handle,
                                UInt32          fileId,
                                String          symName,
                                UInt32 *        symValue);

/* Function to retrieve the entry point of the specified file.
 * The fileId received from the load function must be passed to this
 * function.
 */
Int ElfLoader_getEntryPt (Loader_Handle   handle,
                          UInt32          fileId,
                          UInt32 *        entryPt);
/* Function that returns section information given the name of section and
 * number of bytes to read
 */
Int ElfLoader_getSectionInfo (Loader_Handle         handle,
                              UInt32                fileId,
                              String                sectionName,
                              ProcMgr_SectionInfo * sectionInfo);

/* Function that returns section data in a buffer given sectionInfo data
 * returned from previous call to ElfLoader_getSectionInfo.
 */
Int ElfLoader_getSectionData (Loader_Handle         handle,
                              UInt32                fileId,
                              ProcMgr_SectionInfo * sectionInfo,
                              Ptr                   buffer);



/* =============================================================================
 *  ELF core loader (DLIF) client lower edge functions
 * =============================================================================
 */



/*!
 *  @brief  Function to seek to a position in the file based on the values for
 *          offset and pos.
 */
Int ElfLoaderFile_seek (Ptr            clientHandle,
                        Ptr            fileDesc,
                        Int32          offset,
                        LoaderFile_Pos pos);


/*!
 *  @brief  Function to return the current file position in the file.
 *
 *          Returns the position in the file.
 */
UInt32 ElfLoaderFile_tell (Ptr clientHandle,
                           Ptr fileDesc);

/*!
 *  @brief  Function to read contents of file into specified buffer.
 *
 *          Returns number of bytes actually read.
 */
UInt32 ElfLoaderFile_read (Ptr    clientHandle,
                           Ptr    fileDesc,
                           Char * buffer,
                           UInt32 size,
                           UInt32 count);


/*!
 *  @brief  Function to close the file
 */
UInt32 ElfLoaderFile_close (Ptr clientHandle,
                            Ptr fileDesc);


/*!
 *  @brief  Function to allocate specified bytes of memory.
 *          Returns a pointer to the memory buffer.
 */
Ptr ElfLoaderMem_alloc (Ptr clientHandle,
                        UInt32 size);

/*!
 *  @brief  Function pointer type for the function to free the specified buffer.
 */
Void ElfLoaderMem_free (Ptr clientHandle,
                        Ptr buffer,
                        UInt32 size);

/*!
 *  @brief  Function to allocate specified bytes of target memory.
 */
Int ElfLoaderTrgMem_alloc (Ptr clientHandle,
                           struct DLOAD_MEMORY_REQUEST *  memReq);


/*!
 *  @brief  Function to to free the specified target memory buffer.
 */
Int ElfLoaderTrgMem_free (Ptr clientHandle,
                          struct DLOAD_MEMORY_SEGMENT * memReq);


/*!
 *  @brief  Function to copy data into the provided segment and making it
 *          available to generic ELF parser.
 *          Memory for buffer is allocated in this function.
 */
Int ElfLoaderTrgWrite_copy (Ptr clientHandle,
                            struct DLOAD_MEMORY_REQUEST * memReq);


/*!
 *  @brief  Function to write data to the target memory. For file based loader,
 *          this function also frees the section data host buffer after copying
 *          the data into target memory.
 */
Int ElfLoaderTrgWrite_write (Ptr clientHandle,
                             struct DLOAD_MEMORY_REQUEST * memReq);



/*!
 *  @brief  Function to start execution of the target from the given execAddr.
 */
Int ElfLoaderTrgWrite_execute (Ptr clientHandle,
                               UInt32 execAddr);



/*!
 *  @brief  Function to map a slave address into host address space.
 */
Int ElfLoaderTrgWrite_map (Ptr                clientHandle,
                           ProcMgr_MapMask    mapType,
                           ProcMgr_AddrInfo * aInfo,
                           ProcMgr_AddrType   srcAddrType);



/*!
 *  @brief  Function to unmap a slave address from host address space.
 */
Int ElfLoaderTrgWrite_unmap (Ptr                clientHandle,
                             ProcMgr_MapMask    mapType,
                             ProcMgr_AddrInfo * aInfo,
                             ProcMgr_AddrType   srcAddrType);

/*!
 *  @brief  Function to map a slave address into host address space.
 */
Int ElfLoaderTrgWrite_translate (Ptr              clientHandle,
                                Ptr *            dstAddr,
                                ProcMgr_AddrType dstAddrType,
                                Ptr              srcAddr,
                                ProcMgr_AddrType srcAddrType);


/*!
 *  @brief  Function to find and open a dependent file identified by the dllName
 *          parameter, then, if necessary, initiate a load call to actually load
 *          the shared object onto the target. A successful load will return a
 *          file ID that the client can associate with the newly loaded file.
 */
Int ElfLoaderDll_loadDependent (Ptr clientHandle,
                                String dllName);

/*!
 *  @brief  Function to unload a dependent file identified by the fileId
 *          parameter. Then, client must initiate an unload call to actually
 *          unload the shared object to free the target memory occupied by the
 *          object file.
 *          The fileId received from the load function must be passed to this
 *          function.
 */
Int ElfLoaderDll_unloadDependent (Ptr clientHandle,
                                  UInt32 fileId);


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* _ElfLoader_H_0x1bc5 */
