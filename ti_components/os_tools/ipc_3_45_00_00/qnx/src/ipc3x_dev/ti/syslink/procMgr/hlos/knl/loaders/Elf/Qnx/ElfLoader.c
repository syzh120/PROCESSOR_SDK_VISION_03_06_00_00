/*
 *  @file   ElfLoader.c
 *
 *  @brief      File-based ELF loader implementation
 *
 *              This ELF loader opens, parses and loads the ELF file that is
 *              present in the master file system, onto the slave processor.
 *
 *              @Example
 *              @code
 *              ElfLoader_Handle     loaderHandle = NULL;
 *              ElfLoader_Config     loaderConfig;
 *              ElfLoader_Params     loaderParams;
 *
 *              ElfLoader_getConfig (&loaderConfig);
 *              status = ElfLoader_setup (&loaderConfig);
 *
 *              ElfLoader_Params_init (NULL, &loaderParams);
 *              loaderHandle = ElfLoader_create (procId, &loaderParams);
 *
 *              ElfLoader_delete (&loaderHandle);
 *              ElfLoader_destroy ();
 *              @endcode
 *
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


/* Standard headers */
#include <ti/syslink/Std.h>

/* OSAL & Utils headers */
#include <OsalKfile.h>
#include <ti/syslink/utils/Memory.h>
#include <ti/syslink/utils/IGateProvider.h>
#include <ti/syslink/utils/Gate.h>
#include <ti/syslink/utils/GateMutex.h>
#include <ti/syslink/utils/Trace.h>
#include <OsalDriver.h>
#include <Bitops.h>
#include <ti/syslink/utils/String.h>

/* Module level headers */
#include <LoaderDefs.h>
#include <Loader.h>
#include <dload_api.h>
#include <ElfLoader.h>
#include <_ElfLoader.h>
#include <ti/syslink/ProcMgr.h>
#include <_ProcMgr.h>
#include <Processor.h>
#include <ti/ipc/MultiProc.h>
#include <_MultiProc.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/* Macro to make a correct module magic number with refCount */
#define LOADER_MAKE_MAGICSTAMP(x) ((LOADER_MODULEID << 12u) | (x))

#define START_SUFFIX       "_Start"
#define END_SUFFIX         "_End"
#define START_SUFFIX_LEN   6
#define END_SUFFIX_LEN     4

/*!
 *  @brief  ElfLoader Module state object
 */
typedef struct ElfLoader_ModuleObject_tag {
    Atomic                  refCount;
    /*!< Reference count */
    UInt32                  configSize;
    /*!< Size of configuration structure */
    ElfLoader_Config        cfg;
    /*!< ElfLoader configuration structure */
    ElfLoader_Config        defCfg;
    /*!< Default module configuration */
    Bool                    isSetup;
    /*!< Indicates whether the ElfLoader module is setup. */
    ElfLoader_Handle        loaderHandles [MultiProc_MAXPROCESSORS];
    /*!< Loader handle array. */
    IGateProvider_Handle    gateHandle;
    /*!< Handle of gate to be used for local thread safety */
    Ptr                     osalDrvHandle;
    /*!< OsalDriver handle for ElfLoader */
} ElfLoader_ModuleObject;

/*!
 *  @brief  Internal ElfLoader instance object.
 */
typedef struct _ElfLoader_Object_tag {
    ElfLoader_Params        params;
    /*!< Instance parameters (configuration values) */
    String                  fileName;
    /*!< Name of the file currently loaded. */
    Processor_Handle        procHandle;
    /*!< Handle to the Processor instance. */
    ProcMgr_Handle          pmHandle;
    /*!< Handle to the ProcMgr instance. */
    Processor_ProcArch      procArch;
    /*!< Processor architecture */
    Ptr                     fileDesc;
    /*!< File object for the slave base image file. */
} _ElfLoader_Object;


/* =============================================================================
 *  Globals
 * =============================================================================
 */
/*!
 *  @var    ElfLoader_state
 *
 *  @brief  ElfLoader state object variable
 */
#if !defined(IPC_BUILD_DEBUG)
static
#endif /* if !defined(IPC_BUILD_DEBUG) */
ElfLoader_ModuleObject ElfLoader_state =
{
    .isSetup = FALSE,
    .configSize = sizeof (ElfLoader_Config),
    .gateHandle = NULL,
    .osalDrvHandle = NULL
};

/* =============================================================================
 * Internal implementations of client Provided Functions
 * =============================================================================
 */

/* -----------------------------------------------------------------------------
 *  File I/O Interface
 *
 *  The client side of the loader must provide basic file I/O capabilities so
 *  that the core loader has random access into any file that it is asked to
 *  load.
 * -----------------------------------------------------------------------------
 */

/*!
 *  @brief  Function to seek to a position in the file based on the values for
 *          offset and pos.
 *
 *  @param  clientHandle    Handle to the client loader object.
 *  @param  fileDesc        File descriptor
 *  @param  offset          Offset (in bytes) from specified positioning command
 *  @param  pos             Positioning command for the file
 *
 *  @sa     ElfLoaderFile_tell
 */
inline
Int
ElfLoaderFile_seek (Ptr            clientHandle,
                    Ptr            fileDesc,
                    Int32          offset,
                    LoaderFile_Pos pos)
{
    GT_4trace (curTrace, GT_ENTER, "ElfLoaderFile_seek",
               clientHandle, fileDesc, offset, pos);

    (Void) clientHandle; /* Not used. */
    GT_assert (curTrace, (fileDesc != NULL));
    GT_assert (curTrace, (pos < LoaderFile_Pos_EndValue));

    GT_0trace (curTrace, GT_LEAVE, "ElfLoaderFile_seek");

    /*! @retval LOADER_SUCCESS Operation successfully completed. */
    return (OsalKfile_seek (fileDesc, offset, pos));
}

/*!
 *  @brief  Function to return the current file position in the file.
 *
 *          Returns the position in the file.
 *
 *  @param  clientHandle    Handle to the client loader object.
 *  @param  fileDesc        File descriptor
 *
 *  @sa     ElfLoaderMem_seek
 */
inline
UInt32
ElfLoaderFile_tell (Ptr clientHandle, Ptr fileDesc)
{
    GT_2trace (curTrace, GT_ENTER, "ElfLoaderFile_tell",
               clientHandle, fileDesc);

    (Void) clientHandle; /* Not used. */
    GT_assert (curTrace, (fileDesc != NULL));

    GT_0trace (curTrace, GT_LEAVE, "ElfLoaderFile_tell");

    /*! @retval Value: Current position in the file. */
    return (OsalKfile_tell (fileDesc));
}

/*!
 *  @brief  Function to read contents of file into specified buffer.
 *
 *          Returns number of bytes actually read.
 *
 *  @param  clientHandle    Handle to the client loader object.
 *  @param  fileDesc        File descriptor
 *  @param  buffer          Buffer to read into
 *  @param  size            Size of each record to be read
 *  @param  count           Number of records to be read
 *
 *  @sa     ElfLoaderMem_seek
 */
inline
UInt32
ElfLoaderFile_read (Ptr    clientHandle,
                    Ptr    fileDesc,
                    Char * buffer,
                    UInt32 size,
                    UInt32 count)
{
    GT_5trace (curTrace, GT_ENTER, "ElfLoaderFile_read",
               clientHandle, fileDesc, buffer, size, count);

    (Void) clientHandle; /* Not used. */
    GT_assert (curTrace, (fileDesc != NULL));
    GT_assert (curTrace, (buffer != NULL));
    GT_assert (curTrace, (size != 0));
    GT_assert (curTrace, (count != 0));

    GT_0trace (curTrace, GT_LEAVE, "ElfLoaderFile_read");

    /*! @retval Value: Number of bytes read */
    if (size != 0)
        return (OsalKfile_read (fileDesc, buffer, size, count));
    else
        return 0;
}

/*!
 *  @brief  Function to close the file
 *
 *  @param  clientHandle    Handle to the client loader object.
 *  @param  fileDesc        File descriptor
 *
 *  @sa
 */
inline
UInt32
ElfLoaderFile_close (Ptr clientHandle, Ptr fileDesc)
{
    GT_2trace (curTrace, GT_ENTER, "ElfLoaderFile_close",
               clientHandle, fileDesc);

    (Void) clientHandle; /* Not used. */
    GT_assert (curTrace, (fileDesc != NULL));

    GT_0trace (curTrace, GT_LEAVE, "ElfLoaderFile_close");

    /*! @retval LOADER_SUCCESS Operation successfully completed. */
    return (OsalKfile_close (fileDesc));
}


/* -----------------------------------------------------------------------------
 *  Host Memory management Interface
 *
 *  Allocate and free host memory as needed for the loader's internal data
 *  structures. If the loader resides on the target architecture, then this
 *  memory is allocated from a target memory heap that must be managed
 *  separately from memory that is allocated for a loaded file.
 * -----------------------------------------------------------------------------
 */
/*!
 *  @brief  Function to allocate specified bytes of memory.
 *          Returns a pointer to the memory buffer.
 *
 *  @param  clientHandle    Handle to the client loader object.
 *  @param  size            Size (in bytes) of buffer to be allocated.
 *
 *  @sa     ElfLoaderMem_free
 */
inline
Ptr
ElfLoaderMem_alloc (Ptr clientHandle, UInt32 size)
{
    GT_2trace (curTrace, GT_ENTER, "ElfLoaderMem_alloc", clientHandle, size);

    (Void) clientHandle; /* Not used. */
    GT_assert (curTrace, (size != 0));

    GT_0trace (curTrace, GT_LEAVE, "ElfLoaderMem_alloc");

    if(size == 0)
        return NULL;

    /*! @retval Pointer: Pointer to allocated buffer. */
    return (Memory_alloc (NULL, size, 0, NULL));
}


/*!
 *  @brief  Function pointer type for the function to free the specified buffer.
 */
/*!
 *  @brief  Function to free specified buffer.
 *
 *  @param  clientHandle       Handle to the client loader object.
 *  @param  buffer             Pointer to buffer to be freed.
 *  @param  size               Size (in bytes) of buffer to be freed.
 *
 *  @sa     ElfLoaderMem_alloc
 */
inline
Void
ElfLoaderMem_free (Ptr clientHandle, Ptr buffer, UInt32 size)
{
    GT_3trace (curTrace, GT_ENTER, "ElfLoaderMem_free",
               clientHandle, buffer, size);

    (Void) clientHandle; /* Not used. */
    GT_assert (curTrace, (buffer != NULL));
    GT_assert (curTrace, (size   != 0));

    Memory_free (NULL, buffer, size);

    GT_0trace (curTrace, GT_LEAVE, "ElfLoaderMem_free");
}


/* -----------------------------------------------------------------------------
 *  Target Memory Allocator Interface
 *
 *  The client side of the loader must create and maintain an infrastructure to
 *  manage target memory. The client must keep track of what target memory is
 *  associated with each object segment, allocating target memory for newly
 *  loaded objects and release target memory that is associated with objects
 *  that are being unloaded from the target architecture.
 *
 *  These functions are used by the core loader to interface into the client
 *  side's target memory allocator infrastructure.
 * -----------------------------------------------------------------------------
 */
/*!
 *  @brief  Function to allocate or mmap specified bytes of target memory.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  memReq       Memory request for this allocation.
 *
 *  @sa     ElfLoaderTrgMem_free
 */
inline
Int
ElfLoaderTrgMem_alloc (Ptr                  clientHandle,
                       struct DLOAD_MEMORY_REQUEST *  memReq)
{
    /* Need to ensure we map addresses of unitialized segments,
     * otherwise, will get a iommu handler fault when slave program runs.
     */
    Int                  status     = LOADER_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "ElfLoaderTrgMem_alloc",
               clientHandle, memReq);

    (Void) clientHandle; /* Not used. */
    (Void) memReq;       /* Not used. */

    /* Nothing to be done here. Target memory addresses are fixed since this
     * loader only supports static executables.
     */
    /* No need for the below trace */
    /*GT_0trace (curTrace, GT_3CLASS, "ElfLoaderTrgMem_alloc not implemented.");*/

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgMem_alloc", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief  Function to to free the specified target memory buffer.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  memReq       Memory request for this free.
 *
 *  @sa     ElfLoaderTrgMem_alloc
 */
inline
Int
ElfLoaderTrgMem_free (Ptr clientHandle,
                      struct DLOAD_MEMORY_SEGMENT * memReq)
{
    Int status = LOADER_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "ElfLoaderTrgMem_free",
               clientHandle, memReq);

    (Void) clientHandle; /* Not used. */
    (Void) memReq;       /* Not used. */

    /* Nothing to be done here. Target memory addresses are fixed since this
     * loader only supports static executables.
     */
    /* No need for the below trace */
    /*GT_0trace (curTrace, GT_3CLASS, "ElfLoaderTrgMem_free not implemented.");*/

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgMem_free", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;

}

/* -----------------------------------------------------------------------------
 *  Target Memory Access / Write Services
 *
 *  To complete the loading of an object segment, the segment may need to be
 *  relocated before it is actually written to target memory in the space that
 *  was allocated for it.
 *
 *  The client side of the loader provides the functions in this section to help
 *  complete the process of loading an object segment.
 *
 *  These functions help to make the core loader truly independent of
 *  whether it is running on the host or target architecture and how the
 *  client provides for reading/writing from/to target memory.
 * -----------------------------------------------------------------------------
 */
/*!
 *  @brief  Function to copy data into the provided segment and making it
 *          available to generic ELF parser.
 *          Memory for buffer is allocated in this function.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  memReq       Memory request for this copy
 *
 *  @sa     ElfLoaderTrgWrite_write
 */
inline
Int
ElfLoaderTrgWrite_copy (Ptr clientHandle, struct DLOAD_MEMORY_REQUEST * memReq)
{
    Int                  status     = LOADER_SUCCESS;
    Char *               sectData;
    UInt32               numBytes;
    _ElfLoader_Object *  elfLoaderObject;
    ProcMgr_AddrInfo     aInfo;
    UInt32               dstAddr;

    GT_2trace (curTrace, GT_ENTER, "ElfLoaderTrgWrite_copy",
               clientHandle, memReq);


    GT_assert (curTrace, (clientHandle != NULL));

    GT_assert (curTrace, (memReq       != NULL));

    elfLoaderObject = (_ElfLoader_Object *) clientHandle;
    GT_assert (curTrace, (elfLoaderObject != NULL));

    numBytes = memReq->segment->memsz_in_bytes;
    /* numBytes may be 0 if a section is of size 0. */
    if (numBytes != 0) {
        /* Translates slave phys to master physical address: */
        status = Processor_translateAddr (elfLoaderObject->procHandle,
                                          &dstAddr,
                                          (UInt32)memReq->segment->target_address);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoaderTrgWrite_copy",
                                 status,
                                 "Processor_translateAddr failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            aInfo.addr [ProcMgr_AddrType_MasterPhys] = dstAddr;
            aInfo.addr [ProcMgr_AddrType_SlaveVirt]  =
                                       (UInt32) memReq->segment->target_address;
            aInfo.size = numBytes;
            aInfo.isCached = FALSE;
            /*
             * Map master physical address to master virtual: this does NOT
             * program the MMU:
             */
            status = _ProcMgr_map (elfLoaderObject->pmHandle,
                                   (ProcMgr_MASTERKNLVIRT
                                    | ProcMgr_SLAVEVIRT),
                                   &aInfo,
                                   ProcMgr_AddrType_MasterPhys);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoaderTrgWrite_copy",
                                     status,
                                     "ProcMgr_map failed!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                sectData = (Ptr) aInfo.addr [ProcMgr_AddrType_MasterKnlVirt];
#if !defined(IPC_BUILD_OPTIMIZE)
            }
       }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        if (status >= 0) {
            /* Zero out unitialized data: */
        memset(sectData, 0, memReq->segment->memsz_in_bytes);

            /* Only write data if filesize (objsz_in_bytes) is non-zero,
             * otherwise, the file read asserts.
             */
            if (memReq->segment->objsz_in_bytes)  {

                /* Seek to the location of the section data. */
                status = ElfLoaderFile_seek (clientHandle,
                                              memReq->fp,
                                              memReq->offset,
                                              LoaderFile_Pos_SeekSet);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoaderTrgWrite_copy",
                                 status,
                                 "Failed to seek to location of section data!");
                }
                else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    /* Read from file if the loader is file-based. */
                    numBytes = ElfLoaderFile_read (clientHandle,
                                                memReq->fp,
                                                sectData,
                                                memReq->segment->objsz_in_bytes,
                                                sizeof (UInt8));
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (numBytes == 0u) {
                        /*! @retval LOADER_E_FILE Failed to read from file */
                        status = LOADER_E_FILE;
                        GT_setFailureReason (curTrace,
                                      GT_4CLASS,
                                      "ElfLoaderTrgWrite_copy",
                                      status,
                                      "Failed to read section data from file!");
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        /* Return section data address. */
                        memReq->host_address = sectData;
                        memReq->is_loaded = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
                    }
                }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            }
            else {  // if (memReq->segment->objsz_in_bytes)
                memReq->host_address = sectData;
                memReq->is_loaded = TRUE;
            }
        }
    }

    GT_3trace (curTrace, GT_LEAVE, "ElfLoaderTrgWrite_copy", status,
               dstAddr, numBytes);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief  Function to write data to the target memory. For file based loader,
 *          this function also frees the section data host buffer after copying
 *          the data into target memory.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  memReq       Memory request for this write
 *
 *  @sa     ElfLoaderTrgWrite_copy, Processor_write
 */
inline
Int
ElfLoaderTrgWrite_write (Ptr clientHandle, struct DLOAD_MEMORY_REQUEST * memReq)
{
    Int                  status        = LOADER_SUCCESS;
    UInt32               numBytes      = 0;
    _ElfLoader_Object * elfLoaderObject;
    ProcMgr_AddrInfo     aInfo;
    UInt32               dstAddr;

    GT_2trace (curTrace, GT_ENTER, "ElfLoaderTrgWrite_write",
               clientHandle, memReq);

    GT_assert (curTrace, (clientHandle != NULL));

    GT_assert (curTrace, (memReq       != NULL));

    elfLoaderObject = (_ElfLoader_Object *) clientHandle;
    GT_assert (curTrace, (elfLoaderObject != NULL));

    /* Only load the section if it is not already loaded. */
    if (memReq->is_loaded == FALSE) {
        /* numBytes may be 0 if a section is of size 0. */
        numBytes = memReq->segment->objsz_in_bytes;
        if (numBytes != 0) {
            /* First try to translate the address, if it is
             * premapped
             */
            /* TBD: Slave Virt addr is same as slave phys */
            status = Processor_translateAddr (elfLoaderObject->procHandle,
                                      &dstAddr,
                                      (UInt32)memReq->segment->target_address);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoaderTrgWrite_copy",
                                     status,
                                     "Processor_translateAddr failed!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                aInfo.addr [ProcMgr_AddrType_MasterPhys] = dstAddr;
                aInfo.addr [ProcMgr_AddrType_SlaveVirt]  =
                                        (UInt32)memReq->segment->target_address;
                aInfo.size = numBytes;
                aInfo.isCached = FALSE;
                /* Lock is held by ProcMgr_load API thus it is safe to call
                 * this API
                 */
                status = _ProcMgr_map (elfLoaderObject->pmHandle,
                                       (ProcMgr_MASTERKNLVIRT
                                        | ProcMgr_SLAVEVIRT),
                                       &aInfo,
                                       ProcMgr_AddrType_MasterPhys);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (status < 0) {
                    GT_setFailureReason (curTrace,
                                         GT_4CLASS,
                                         "ElfLoaderTrgWrite_copy",
                                         status,
                                         "ProcMgr_map failed!");
                }
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

            /* Write to target memory. */
            status = ProcMgr_write (elfLoaderObject->pmHandle,
                                      (UInt32)memReq->segment->target_address,
                                      &numBytes,
                                      memReq->host_address);

#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoaderTrgWrite_write",
                                     status,
                                     "Failed to write to target memory!");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }

    /* numBytes may be 0 if a section is of size 0. */
    numBytes = memReq->segment->memsz_in_bytes;
    if (numBytes != 0) {
        /* Translates slave phys to master physical address: */
        status = Processor_translateAddr (elfLoaderObject->procHandle,
                                          &dstAddr,
                                          (UInt32)memReq->segment->target_address);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoaderTrgWrite_copy",
                                 status,
                                 "Processor_translateAddr failed!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Un-map the target memory. */
            aInfo.size = numBytes;
            aInfo.isCached = FALSE;
            aInfo.addr[ProcMgr_AddrType_MasterPhys] = dstAddr;
            aInfo.addr[ProcMgr_AddrType_MasterKnlVirt] = (UInt32)memReq->host_address;
            aInfo.addr[ProcMgr_AddrType_SlaveVirt] = (UInt32)memReq->segment->target_address;
            status = _ProcMgr_unmap(elfLoaderObject->pmHandle,
                                    (ProcMgr_MASTERKNLVIRT
                                     | ProcMgr_SLAVEVIRT),
                                    &aInfo,
                                    ProcMgr_AddrType_MasterPhys);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoaderTrgWrite_copy",
                                     status,
                                     "_ProcMgr_unmap failed!");
            }
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgWrite_write", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief  Function to start execution of the target from the given execAddr.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  execAddr     Target address from which to execute it.
 *
 *  @sa
 */
inline
Int
ElfLoaderTrgWrite_execute (Ptr clientHandle, UInt32 execAddr)
{
    Int status = LOADER_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "ElfLoaderTrgWrite_execute",
               clientHandle, execAddr);

    (Void) clientHandle; /* Not used. */

    /* Nothing to be done here. Execution shall happen on request from user. */
    GT_0trace (curTrace, GT_3CLASS, "ElfLoaderTrgWrite_execute not supported.");

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgWrite_execute", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief  Function to map a slave address into host address space.
 *
 *  @param      clientHandle Handle to the client loader object.
 *  @param      mapType     Type of mapping to be performed.
 *  @param      addrInfo    Structure containing map info.
 *  @param      srcAddrType Source address type.
 *
 *  @sa     ElfLoaderTrgWrite_unmap
 */
inline
Int
ElfLoaderTrgWrite_map (Ptr                clientHandle,
                       ProcMgr_MapMask    mapType,
                       ProcMgr_AddrInfo * aInfo,
                       ProcMgr_AddrType   srcAddrType)
{
    Int                  status        = LOADER_SUCCESS;
    _ElfLoader_Object * elfLoaderObject;

    GT_4trace (curTrace, GT_ENTER, "ElfLoaderTrgWrite_map",
               clientHandle, mapType, aInfo, srcAddrType);

    GT_assert (curTrace, (clientHandle != NULL));

    GT_assert (curTrace, (aInfo != NULL));
    GT_assert (curTrace, (srcAddrType < ProcMgr_AddrType_EndValue));

    elfLoaderObject = (_ElfLoader_Object *) clientHandle;
    GT_assert (curTrace, (elfLoaderObject != NULL));

    /* Write to target memory. */
    status = _ProcMgr_map (elfLoaderObject->pmHandle,
                           mapType,
                           aInfo,
                           srcAddrType);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoaderTrgWrite_map",
                             status,
                             "ProcMgr_map failed!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgWrite_map", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief  Function to unmap a slave address from host address space.
 *
 *  @param      clientHandle Handle to the client loader object.
 *  @param      mapType     Type of mapping to be performed.
 *  @param      addrInfo    Structure containing map info.
 *  @param      srcAddrType Source address type.
 *
 *  @sa     ElfLoaderTrgWrite_unmap
 */
inline
Int
ElfLoaderTrgWrite_unmap (Ptr                clientHandle,
                         ProcMgr_MapMask    mapType,
                         ProcMgr_AddrInfo * aInfo,
                         ProcMgr_AddrType   srcAddrType)
{
    Int                  status        = LOADER_SUCCESS;
    _ElfLoader_Object * elfLoaderObject;

    GT_4trace (curTrace, GT_ENTER, "ElfLoaderTrgWrite_unmap",
               clientHandle, mapType, aInfo, srcAddrType);

    GT_assert (curTrace, (clientHandle != NULL));

    GT_assert (curTrace, (aInfo != NULL));
    GT_assert (curTrace, (srcAddrType < ProcMgr_AddrType_EndValue));

    elfLoaderObject = (_ElfLoader_Object *) clientHandle;
    GT_assert (curTrace, (elfLoaderObject != NULL));

    /* Write to target memory. */
    status = _ProcMgr_unmap (elfLoaderObject->pmHandle,
                             mapType,
                             aInfo,
                             srcAddrType);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoaderTrgWrite_unmap",
                             status,
                             "ProcMgr_unmap failed!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgWrite_unmap", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief  Function to map a slave address into host address space.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  mapInfo      mapping info.
 *  @param  mapType      Type of mapping.
 *
 *  @sa     ElfLoaderTrgWrite_unmap
 */
inline
Int
ElfLoaderTrgWrite_translate (Ptr              clientHandle,
                              Ptr *            dstAddr,
                              ProcMgr_AddrType dstAddrType,
                              Ptr              srcAddr,
                              ProcMgr_AddrType srcAddrType)
{
    Int                  status        = LOADER_SUCCESS;
    _ElfLoader_Object * elfLoaderObject;

    GT_5trace (curTrace, GT_ENTER, "ElfLoaderTrgWrite_translate",
               clientHandle, dstAddr, dstAddrType, srcAddr, srcAddrType);

    GT_assert (curTrace, (clientHandle != NULL));

    elfLoaderObject = (_ElfLoader_Object *) clientHandle;
    GT_assert (curTrace, (elfLoaderObject != NULL));

    /* Write to target memory. */
    status = ProcMgr_translateAddr (elfLoaderObject->pmHandle,
                                    dstAddr,
                                    dstAddrType,
                                    srcAddr,
                                    srcAddrType);

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoaderTrgWrite_translate",
                             status,
                             "ProcMgr_translateAddr failed!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderTrgWrite_translate", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/* -----------------------------------------------------------------------------
 *  Loading and Unloading of Dependent Files
 *  NOTE: Only applicable for dynamic loader. For other loaders, these functions
 *        do not need to be implemented and can simply return LOADER_E_NOTIMPL.
 *
 *  The dynamic loader core loader must coordinate loading and unloading
 *  dependent object files with the client side of the dynamic loader.
 *  This allows the client to keep its bookkeeping information up to date
 *  with what is currently loaded on the target architecture.
 *
 *  For instance, the client may need to interact with a file system or
 *  registry.  The client may also need to update debug information in
 *  synch with the loading and unloading of shared objects.
 * -----------------------------------------------------------------------------
 */
/*!
 *  @brief  Function to find and open a dependent file identified by the dllName
 *          parameter, then, if necessary, initiate a load call to actually load
 *          the shared object onto the target. A successful load will return a
 *          file ID that the client can associate with the newly loaded file.
 *          NOTE: Only applicable for dynamic loader. For other loaders, these
 *                functions do not need to be implemented and can simply return
 *                LOADER_E_NOTIMPL.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  dllName      Path to the DLL to be loaded.
 *
 *  @sa     ElfLoaderDll_loadDependent
 */
inline
Int
ElfLoaderDll_loadDependent (Ptr clientHandle, String dllName)
{
    GT_2trace (curTrace, GT_ENTER, "ElfLoaderDll_loadDependent",
               clientHandle, dllName);

    (Void) clientHandle; /* Not used. */
    (Void) dllName; /* Not used. */

    /* Nothing to be done here. Function is not supported for static loader. */
    GT_0trace (curTrace, GT_3CLASS, "ElfLoaderDll_loadDependent not supported.");

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderDll_loadDependent",
               LOADER_E_NOTIMPL);

    /*! @retval LOADER_E_NOTIMPL This function is not implemented for this
                                 loader. */
    return LOADER_E_NOTIMPL;
}


/*!
 *  @brief  Function to unload a dependent file identified by the fileId
 *          parameter. Then, client must initiate an unload call to actually
 *          unload the shared object to free the target memory occupied by the
 *          object file.
 *          The fileId received from the load function must be passed to this
 *          function.
 *          NOTE: Only applicable for dynamic loader. For other loaders, these
 *                functions do not need to be implemented and can simply return
 *                LOADER_E_NOTIMPL.
 *
 *  @param  clientHandle Handle to the client loader object.
 *  @param  fileId       ID of the dependent file to be unloaded.
 *
 *  @sa     ElfLoaderDll_loadDependent
 */
inline
Int
ElfLoaderDll_unloadDependent (Ptr clientHandle, UInt32 fileId)
{
    GT_2trace (curTrace, GT_ENTER, "ElfLoaderDll_unloadDependent",
               clientHandle, fileId);

    (Void) clientHandle; /* Not used. */
    (Void) fileId; /* Not used. */

    /* Nothing to be done here. Function is not supported for static loader. */
    GT_0trace (curTrace, GT_3CLASS, "ElfLoaderDll_unloadDependent not supported.");

    GT_1trace (curTrace, GT_LEAVE, "ElfLoaderDll_unloadDependent",
               LOADER_E_NOTIMPL);

    /*! @retval LOADER_E_NOTIMPL This function is not implemented for this
                                 loader. */
    return LOADER_E_NOTIMPL;
}


/* =============================================================================
 * APIs directly called by applications
 * =============================================================================
 */
/*!
 *  @brief      Function to get the default configuration for the ElfLoader
 *              module.
 *
 *              This function can be called by the application to get their
 *              configuration parameter to ElfLoader_setup filled in by the
 *              ElfLoader module with the default parameters. If the user does
 *              not wish to make any change in the default parameters, this API
 *              is not required to be called.
 *
 *  @param      cfg        Pointer to the ElfLoader module configuration
 *                         structure in which the default config is to be
 *                         returned.
 *
 *  @sa         ElfLoader_setup
 */
Void
ElfLoader_getConfig (ElfLoader_Config * cfg)
{
    GT_1trace (curTrace, GT_ENTER, "ElfLoader_getConfig", cfg);

    GT_assert (curTrace, (cfg != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (cfg == NULL) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_getConfig",
                             LOADER_E_INVALIDARG,
                             "Argument of type (ElfLoader_Config *) passed "
                             "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        Memory_copy (cfg,
                     &ElfLoader_state.defCfg,
                     sizeof (ElfLoader_Config));
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ElfLoader_getConfig");
}


/*!
 *  @brief      Function to setup the ElfLoader module.
 *
 *              This function sets up the ElfLoader module. This function must
 *              be called before any other instance-level APIs can be invoked.
 *              Module-level configuration needs to be provided to this
 *              function. If the user wishes to change some specific config
 *              parameters, then ElfLoader_getConfig can be called to get the
 *              configuration filled with the default values. After this, only
 *              the required configuration values can be changed. If the user
 *              does not wish to make any change in the default parameters, the
 *              application can simply call ElfLoader_setup with NULL
 *              parameters. The default parameters would get automatically used.
 *
 *  @param      cfg   Optional ElfLoader module configuration. If provided as
 *                    NULL, default configuration is used.
 *
 *  @sa         ElfLoader_destroy
 *              GateMutex_create
 */
Int
ElfLoader_setup (ElfLoader_Config * cfg)
{
    Int               status = LOADER_SUCCESS;
    Error_Block       eb;
    ElfLoader_Config  tmpCfg;

    GT_1trace (curTrace, GT_ENTER, "ElfLoader_setup", cfg);

    Error_init(&eb);

    /* This sets the refCount variable is not initialized, upper 16 bits is
     * written with module Id to ensure correctness of refCount variable.
     */
    Atomic_cmpmask_and_set (&ElfLoader_state.refCount,
                            LOADER_MAKE_MAGICSTAMP(0),
                            LOADER_MAKE_MAGICSTAMP(0));

    if (   Atomic_inc_return (&ElfLoader_state.refCount)
        != LOADER_MAKE_MAGICSTAMP(1u)) {
        status = LOADER_S_ALREADYSETUP;
        GT_0trace (curTrace,
                   GT_2CLASS,
                   "ElfLoader Module already initialized!");
    }
    else {
        if (cfg == NULL) {
            ElfLoader_getConfig (&tmpCfg);
            cfg = &tmpCfg;
        }

        /* Create a default gate handle for local module protection. */
        ElfLoader_state.gateHandle = (IGateProvider_Handle)
                              GateMutex_create ((GateMutex_Params *) NULL, &eb);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (ElfLoader_state.gateHandle == NULL) {
            /*! @retval LOADER_E_FAIL Failed to create GateMutex! */
            status = LOADER_E_FAIL;
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoader_setup",
                                 status,
                                 "Failed to create GateMutex!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Copy the user provided values into the state object. */
            Memory_copy (&ElfLoader_state.cfg,
                         cfg,
                         sizeof (ElfLoader_Config));

            /* Initialize the name to handles mapping array. */
            Memory_set (&ElfLoader_state.loaderHandles,
                        0,
                        (sizeof (ElfLoader_Handle) * MultiProc_MAXPROCESSORS));

            ElfLoader_state.isSetup = TRUE;
#if !defined(IPC_BUILD_OPTIMIZE)
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    }

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_setup", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to destroy the ElfLoader module.
 *
 *              Once this function is called, other ElfLoader module APIs, except
 *              for the ElfLoader_getConfig API cannot be called anymore.
 *
 *  @sa         ElfLoader_setup
 *              GateMutex_delete
 */
Int
ElfLoader_destroy (Void)
{
    Int    status = LOADER_SUCCESS;
    UInt16 i;

    GT_0trace (curTrace, GT_ENTER, "ElfLoader_destroy");

#if !defined(IPC_BUILD_OPTIMIZE)
    if (   Atomic_cmpmask_and_lt (&(ElfLoader_state.refCount),
                                  LOADER_MAKE_MAGICSTAMP(0),
                                  LOADER_MAKE_MAGICSTAMP(1))
        == TRUE) {
        /*! @retval LOADER_E_INVALIDSTATE Module was not initialized */
        status = LOADER_E_INVALIDSTATE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_destroy",
                             status,
                             "Module was not initialized!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (   Atomic_dec_return (&ElfLoader_state.refCount)
            == LOADER_MAKE_MAGICSTAMP(0)) {
            /* Check if any ElfLoader instances have not been deleted so far. If not,
             * delete them.
             */
            for (i = 0 ; i < MultiProc_MAXPROCESSORS ; i++) {
                GT_assert (curTrace, (ElfLoader_state.loaderHandles [i] == NULL));
                if (ElfLoader_state.loaderHandles [i] != NULL) {
                    ElfLoader_delete (&(ElfLoader_state.loaderHandles [i]));
                }
            }

            if (ElfLoader_state.gateHandle != NULL) {
                GateMutex_delete ((GateMutex_Handle *)
                                        &(ElfLoader_state.gateHandle));
            }

            ElfLoader_state.isSetup = FALSE;
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_destroy", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to initialize the parameters for this loader instance.
 *
 *  @param      handle  Handle to the loader instance. If provided as NULL, the
 *                      default parameters are returned, otherwise parameters
 *                      as configured for the loader instance are returned.
 *  @param      params  Configuration parameters.
 *
 *  @sa         ElfLoader_create
 */
Void
ElfLoader_Params_init (ElfLoader_Handle handle, ElfLoader_Params * params)
{
    ElfLoader_Object *  elfLoader    = (ElfLoader_Object *) handle;
    _ElfLoader_Object * elfLoaderObject;

    GT_2trace (curTrace, GT_ENTER, "ElfLoader_Params_init", handle, params);

    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (params == NULL) {
        GT_setFailureReason (curTrace,
                          GT_4CLASS,
                          "ElfLoader_Params_init",
                          LOADER_E_INVALIDARG,
                          "Argument of type (ElfLoader_Params *) passed "
                          "is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        if (handle == NULL) {
            params->reserved = 0;
        }
        else {
            elfLoaderObject = (_ElfLoader_Object *)
                                        elfLoader->elfLoaderObject;
            GT_assert (curTrace, (elfLoaderObject != NULL));

            /* Return updated ELF loader instance specific parameters. */
            Memory_copy (params,
                         &(elfLoaderObject->params),
                         sizeof (ElfLoader_Params));
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ElfLoader_Params_init");
}

/*!
 *  @brief      Function to create an instance of this loader.
 *
 *  @param      procId  Processor ID for which this loader instance is required.
 *  @param      params  Configuration parameters.
 *
 *  @sa         ElfLoader_delete
 */
ElfLoader_Handle
ElfLoader_create (      UInt16              procId,
                   const ElfLoader_Params * params)
{
#if !defined(IPC_BUILD_OPTIMIZE)
    Int                 status  = LOADER_SUCCESS;
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
    Loader_Object *     handle  = NULL;
    IArg                key;

    GT_2trace (curTrace, GT_ENTER, "ElfLoader_create", procId, params);

    GT_assert (curTrace, IS_VALID_PROCID (procId));
    GT_assert (curTrace, (params != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (!IS_VALID_PROCID (procId)) {
        /*! @retval NULL Function failed */
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_create",
                             status,
                             "Invalid procId specified");
    }
    else if (params == NULL) {
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_create",
                             status,
                             "params passed is null!");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Enter critical section protection. */
        key = IGateProvider_enter (ElfLoader_state.gateHandle);
#if !defined(IPC_BUILD_OPTIMIZE)
        /* Check if the loader already exists for specified procId. */
        if (ElfLoader_state.loaderHandles [procId] != NULL) {
            status = LOADER_E_ALREADYEXIST;
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_create",
                             status,
                             "Loader already exists for specified procId!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            /* Allocate memory for the handle */
            handle = (Loader_Object *) Memory_calloc (NULL,
                                                      sizeof (Loader_Object),
                                                      0,
                                                      NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (handle == NULL) {
                status = LOADER_E_MEMORY;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoader_create",
                                     status,
                                     "Memory allocation failed for handle!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

                /* Populate the handle fields */
                /* Loader functions. */
                handle->loaderFxnTable.attach = &ElfLoader_attach;
                handle->loaderFxnTable.detach = &ElfLoader_detach;
                handle->loaderFxnTable.load = &ElfLoader_load;
                handle->loaderFxnTable.loadSymbols =
                                                   &ElfLoader_loadSymbols;
                handle->loaderFxnTable.unload = &ElfLoader_unload;
                handle->loaderFxnTable.getSymbolAddress =
                                               &ElfLoader_getSymbolAddress;
                handle->loaderFxnTable.getEntryPt = &ElfLoader_getEntryPt;
                handle->loaderFxnTable.getSectionInfo =
                                                     &ElfLoader_getSectionInfo;
                handle->loaderFxnTable.getSectionData =
                                                     &ElfLoader_getSectionData;

#if 0           /* The following are *not* used by DLOAD ELF loader: */
                /* File I/O Interface */
                handle->fileFxnTable.seek = &ElfLoaderFile_seek;
                handle->fileFxnTable.tell = &ElfLoaderFile_tell;
                handle->fileFxnTable.read = &ElfLoaderFile_read;
                handle->fileFxnTable.close = &ElfLoaderFile_close;

                /* Host Memory management Interface */
                handle->memFxnTable.alloc = &ElfLoaderMem_alloc;
                handle->memFxnTable.free  = &ElfLoaderMem_free;

                /* Target Memory Allocator Interface */
                handle->trgMemFxnTable.alloc = &ElfLoaderTrgMem_alloc;
                handle->trgMemFxnTable.free  = &ElfLoaderTrgMem_free;

                /* Target Memory Access / Write Services */
                handle->trgWriteFxnTable.copy    = &ElfLoaderTrgWrite_copy;
                handle->trgWriteFxnTable.write   = &ElfLoaderTrgWrite_write;
                handle->trgWriteFxnTable.execute = &ElfLoaderTrgWrite_execute;
                handle->trgWriteFxnTable.map     = &ElfLoaderTrgWrite_map;
                handle->trgWriteFxnTable.unmap   = &ElfLoaderTrgWrite_unmap;
                handle->trgWriteFxnTable.translate =
                                                  &ElfLoaderTrgWrite_translate;
                /* Loading and Unloading of Dependent Files */
                handle->dllFxnTable.load   = &ElfLoaderDll_loadDependent;
                handle->dllFxnTable.unload = &ElfLoaderDll_unloadDependent;
#endif

                /* Allocate memory for the ElfLoader object */
                handle->object = (ElfLoader_Object *)
                                  Memory_calloc (NULL,
                                                 sizeof (ElfLoader_Object),
                                                 0,
                                                 NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
                if (handle->object == NULL) {
                    status = LOADER_E_MEMORY;
                    GT_setFailureReason (curTrace,
                         GT_4CLASS,
                         "ElfLoader_create",
                         status,
                         "Memory allocation failed for ElfLoader object!");
                }
                else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                    /* Allocate memory for the internal ElfLoader object */
                    ((ElfLoader_Object *) (handle->object))->elfLoaderObject =
                           (_ElfLoader_Object *)
                                      Memory_calloc (NULL,
                                                sizeof (_ElfLoader_Object),
                                                0,
                                                NULL);
#if !defined(IPC_BUILD_OPTIMIZE)
                    if (((ElfLoader_Object *)
                            (handle->object))->elfLoaderObject == NULL) {
                        status = LOADER_E_MEMORY;
                        GT_setFailureReason (curTrace,
                                    GT_4CLASS,
                                    "ElfLoader_create",
                                    status,
                                    "Memory allocation failed for internal"
                                    " ElfLoader object!");
                    }
                    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                        ((ElfLoader_Object *) (handle->object))->elfObject =
                              DLOAD_create(((ElfLoader_Object *)
                                            (handle->object))->elfLoaderObject);
#if !defined(IPC_BUILD_OPTIMIZE)
                        if (((ElfLoader_Object *)
                                 (handle->object))->elfObject == NULL) {
                            status = LOADER_E_MEMORY;
                            GT_setFailureReason (curTrace,
                                        GT_4CLASS,
                                        "ElfLoader_create",
                                        status,
                                        "DLOAD_create failed!");
                        }
                        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                            handle->procId = procId;
                            ElfLoader_state.loaderHandles [procId] =
                                                    (ElfLoader_Handle) handle;
#if !defined(IPC_BUILD_OPTIMIZE)
                        }
                    }
                }
            }
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Leave critical section protection. */
        IGateProvider_leave (ElfLoader_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        if (NULL != handle) {
            if (NULL != handle->object) {
                if (NULL != ((ElfLoader_Object *)
                            (handle->object))->elfLoaderObject) {
                    Memory_free (NULL, ((ElfLoader_Object *)
                                 (handle->object))->elfLoaderObject,
                                 sizeof (_ElfLoader_Object));
                }
                Memory_free (NULL, handle->object, sizeof (ElfLoader_Object));
            }
            Memory_free (NULL, handle, sizeof (Loader_Object));
        }
        /*! @retval NULL Function failed */
        handle = NULL;
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_create", handle);

    /*! @retval Valid-Handle Operation successful */
    return (ElfLoader_Handle) handle;
}


/*!
 *  @brief      Function to delete an instance of this loader.
 *
 *              The user provided pointer to the handle is reset after
 *              successful completion of this function.
 *
 *  @param      handlePtr   Pointer to handle to the loader instance
 *
 *  @sa         ElfLoader_create
 */
Int
ElfLoader_delete (ElfLoader_Handle * handlePtr)
{
    Int                  status           = LOADER_SUCCESS;
    DLOAD_HANDLE         elfObject        = NULL;
    _ElfLoader_Object *  elfLoaderObject  = NULL;
    Loader_Object *      handle;
    IArg                 key;

    GT_1trace (curTrace, GT_ENTER, "ElfLoader_delete", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handlePtr == NULL) {
        /*! @retval LOADER_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_delete",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval LOADER_E_HANDLE Invalid NULL *handlePtr specified */
        status = LOADER_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_delete",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        handle = (Loader_Object *) (*handlePtr);
        /* Enter critical section protection. */
        key = IGateProvider_enter (ElfLoader_state.gateHandle);

        GT_assert (curTrace, (IS_VALID_PROCID (handle->procId)));
        /* Reset handle in Loader handle array. */
        ElfLoader_state.loaderHandles [handle->procId] = NULL;

        /* Free memory used for the ElfLoader object. */
        if (handle->object != NULL) {
            elfObject = (DLOAD_HANDLE)((ElfLoader_Object *)
                                (handle->object))->elfObject;
            if (elfObject != NULL) {
                DLOAD_destroy(elfObject);
            }
            elfLoaderObject = ((ElfLoader_Object *)
                                (handle->object))->elfLoaderObject;
            /* Free memory used for the internal ElfLoader object. */
            if (elfLoaderObject != NULL) {
                Memory_free (NULL,
                             elfLoaderObject,
                             sizeof (_ElfLoader_Object));
            }

            Memory_free (NULL,
                         handle->object,
                         sizeof (ElfLoader_Object));
            handle->object = NULL;
        }

        /* Free memory used for the Loader object. */
        Memory_free (NULL, handle, sizeof (Loader_Object));
        *handlePtr = NULL;

        /* Leave critical section protection. */
        IGateProvider_leave (ElfLoader_state.gateHandle, key);
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_0trace (curTrace, GT_LEAVE, "ElfLoader_delete");

    /*! @retval LOADER_SUCCESS Operation successful */
    return (status);
}


/*!
 *  @brief      Function to open a handle to an instance of this loader. This
 *              function is called when access to the loader is required from
 *              a different process.
 *
 *  @param      procId  Processor ID addressed by this ElfLoader instance.
 *  @param      handle  Return parameter: Handle to the loader instance
 *
 *  @sa         ElfLoader_close
 */
Int
ElfLoader_open (ElfLoader_Handle * handlePtr, UInt16 procId)
{
    Int status = LOADER_SUCCESS;

    GT_2trace (curTrace, GT_ENTER, "ElfLoader_open", handlePtr, procId);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, IS_VALID_PROCID (procId));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handlePtr == NULL) {
        /*! @retval LOADER_E_HANDLE Invalid MULL handlePtr specified */
        status = LOADER_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_open",
                             status,
                             "Invalid NULL handlePtr specified");
    }
    else if (!IS_VALID_PROCID (procId)) {
        /*! @retval LOADER_E_INVALIDARG Invalid procId specified */
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_open",
                             status,
                             "Invalid procId specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Initialize return parameter handle. */
        *handlePtr = NULL;

        /* Check if the Loader exists and return the handle if found. */
        if (ElfLoader_state.loaderHandles [procId] == NULL) {
            /*! @retval LOADER_E_NOTFOUND Specified instance not found */
            status = LOADER_E_NOTFOUND;
            GT_setFailureReason (curTrace,
                              GT_4CLASS,
                              "ElfLoader_open",
                              status,
                              "Specified ElfLoader instance does not exist!");
        }
        else {
            *handlePtr = ElfLoader_state.loaderHandles [procId];
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_open", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to close a handle to an instance of this loader.
 *
 *  @param      handlePtr   Pointer to handle to the loader instance
 *
 *  @sa         ElfLoader_open
 */
Int
ElfLoader_close (ElfLoader_Handle * handlePtr)
{
    Int status = LOADER_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "ElfLoader_close", handlePtr);

    GT_assert (curTrace, (handlePtr != NULL));
    GT_assert (curTrace, ((handlePtr != NULL) && (*handlePtr != NULL)));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handlePtr == NULL) {
        /*! @retval LOADER_E_INVALIDARG Invalid NULL handlePtr pointer
                                         specified*/
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_close",
                             status,
                             "Invalid NULL handlePtr pointer specified");
    }
    else if (*handlePtr == NULL) {
        /*! @retval LOADER_E_HANDLE Invalid NULL *handlePtr specified */
        status = LOADER_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_close",
                             status,
                             "Invalid NULL *handlePtr specified");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        /* Nothing to be done for close. */
        *handlePtr = NULL;
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_close", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/* =============================================================================
 * APIs called by Loader module (part of function table interface)
 * =============================================================================
 */
/*!
 *  @brief      Function to attach to the Loader.
 *
 *  @param      handle  Handle to the loader instance
 *  @param      params  Attach params
 *
 *  @sa         ElfLoader_detach
 */
Int
ElfLoader_attach (Loader_Handle handle, Loader_AttachParams * params)
{
    Int                 status = LOADER_SUCCESS ;
    ElfLoader_Object * elfLoaderObj;

    GT_2trace (curTrace, GT_ENTER, "ElfLoader_attach", handle, params);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (params != NULL));

    /* Set the procHandle. */
    elfLoaderObj = (ElfLoader_Object *) (((Loader_Object *) handle)->object);
    ((_ElfLoader_Object *) (elfLoaderObj->elfLoaderObject))->procHandle =
                                                            params->procHandle;
    ((_ElfLoader_Object *) (elfLoaderObj->elfLoaderObject))->pmHandle =
                                                               params->pmHandle;

    /* Set the procArch. */
    ((_ElfLoader_Object *) (elfLoaderObj->elfLoaderObject))->procArch =
                                                            params->procArch;

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_attach",status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to detach from the Loader.
 *
 *  @param      handle  Handle to the loader instance
 *
 *  @sa         ElfLoader_attach
 */
Int
ElfLoader_detach (Loader_Handle handle)
{
    Int status = LOADER_SUCCESS;

    GT_1trace (curTrace, GT_ENTER, "ElfLoader_detach", handle);

    /* Nothing to be done for this. */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_detach",status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to load the slave processor.
 *
 *  @param      handle    Handle to the loader instance
 *  @param      imagePath Full file path of the executable to be loaded
 *  @param      argc      Number of arguments to be sent to the slave main
 *                        function
 *  @param      argv      String array for the arguments
 *  @param      params    Loader specific parameters (if any)
 *  @param      fileId    Return parameter: ID of the loaded file
 *
 *  @sa         ElfLoader_unload
 */
Int
ElfLoader_load (Loader_Handle       handle,
                String              imagePath,
                UInt32              argc,
                String *            argv,
                Ptr                 params,
                UInt32 *            fileId)
{
    Int                  status    = LOADER_SUCCESS ;
    OsalKfile_Handle     fileDesc  = NULL;
    Char *               mode      = "r";
    Loader_Object *      loaderObj = (Loader_Object *) handle;
    ElfLoader_Object *   elfLoaderObj;
    DLOAD_HANDLE         elfObj;
    _ElfLoader_Object *  _elfLoaderObj;
    TARGET_ADDRESS       ep;
    Int                  argStatus;

    GT_5trace (curTrace, GT_ENTER, "ElfLoader_load",
               handle, imagePath, argc, argv, params);

    /* params are not applicable for file based ElfLoader. */
    GT_assert (curTrace, (handle    != NULL));
    GT_assert (curTrace, (imagePath != NULL));
    GT_assert (curTrace,
               (   ((argc == 0) && (argv == NULL))
                || ((argc != 0) && (argv != NULL)))) ;
    GT_assert (curTrace, (fileId   != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handle == NULL) {
        /*! @retval LOADER_E_HANDLE NULL provided for argument handle. */
        status = LOADER_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_load",
                             status,
                             "NULL provided for argument handle");
    }
    else if (imagePath == NULL) {
        /*! @retval LOADER_E_INVALIDARG NULL provided for argument imagePath. */
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_load",
                             status,
                             "NULL provided for argument imagePath");
    }
    else if (   ((argc == 0) && (argv != NULL))
             || ((argc != 0) && (argv == NULL))) {
        /*! @retval LOADER_E_INVALIDARG Invalid values provided for argc/argv.*/
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_load",
                             status,
                             "Invalid values provided for argc/argv");
    }
    else if (fileId == NULL) {
        /*! @retval LOADER_E_INVALIDARG NULL provided for argument fileId. */
        status = LOADER_E_INVALIDARG;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_load",
                             status,
                             "NULL provided for argument fileId");
    }
    else {
#endif /* #if !defined(IPC_BUILD_OPTIMIZE) */
        status = OsalKfile_open (imagePath, mode, &fileDesc);
#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoader_load",
                                 status,
                                 "Failed to open file!");
        }
        else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
            GT_assert (curTrace, (fileDesc != NULL));
            elfLoaderObj = (ElfLoader_Object *) loaderObj->object;
            GT_assert (curTrace, (elfLoaderObj != NULL));
            _elfLoaderObj = elfLoaderObj->elfLoaderObject;
            GT_assert (curTrace, (_elfLoaderObj != NULL));
            _elfLoaderObj->fileDesc = fileDesc;
            elfObj = elfLoaderObj->elfObject;
            GT_assert (curTrace, (elfObj != NULL));

            /*
             * This cast to (LOADER_FILE_DESC *) is not ideal, but appears safe
             * as DLOAD_load does not look into fileDesc.
             */
            *fileId = DLOAD_load(elfObj, (LOADER_FILE_DESC *)fileDesc);
            if (*fileId == 0)  {
                 status = LOADER_E_FAIL;
            }

#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoader_load",
                                     status,
                                     "Failed to load ELF file!");
            }
            else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
                argStatus = DLOAD_prepare_for_execution(elfObj,
                                                     *fileId, &ep, argc, argv);

#if !defined(IPC_BUILD_OPTIMIZE)
                if (argStatus == FALSE) {
                    GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoader_load",
                                     argStatus,
                                     "Failed to write args!"
                                     " (ensure .args section is big enough)");
                }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

                /* Set the state of the Processor to loaded. */
                Processor_setState (_elfLoaderObj->procHandle,
                                    ProcMgr_State_Loaded);
#if !defined(IPC_BUILD_OPTIMIZE)
            }
        }
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_load", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to load symbols for the specified file. This will allow
 *              the symbols to be usable when linked against another object
 *              file.
 *              External symbols will be made available for global symbol
 *              linkage.
 *              NOTE: This function is only relevant for dynamic loader. Other
 *                    loaders can return LOADER_E_NOTIMPL.
 *
 *  @param      handle    Handle to the loader instance
 *  @param      imagePath Full file path of the executable to be loaded
 *  @param      params    Loader specific parameters (if any)
 *
 *  @sa         ElfLoader_load
 */
Int
ElfLoader_loadSymbols (Loader_Handle     handle,
                        String            imagePath,
                        Ptr               params)
{
    GT_3trace (curTrace, GT_ENTER, "ElfLoader_loadSymbols",
               handle, imagePath, params);

    (Void) handle; /* Not used. */
    (Void) imagePath; /* Not used. */
    (Void) params; /* Not used. */

    /* Nothing to be done here. Function is not supported for ELF parser. */
    GT_0trace (curTrace, GT_3CLASS, "ElfLoader_loadSymbols not supported.");

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_loadSymbols", LOADER_E_NOTIMPL);

    /*! @retval LOADER_E_NOTIMPL This function is not implemented for this
                                 loader. */
    return LOADER_E_NOTIMPL;
}

/*!
 *  @brief      Function to unload the previously loaded file on the slave
 *              processor.
 *
 *  @param      handle   Handle to the loader instance
 *  @param      fileId   ID of the file received from the load function
 *
 *  @sa         ElfLoader_load
 */
Int
ElfLoader_unload (Loader_Handle handle, UInt32 fileId)
{
    Int                  status    = LOADER_SUCCESS;
    Int                  tmpStatus = LOADER_SUCCESS;
    Loader_Object *      loaderObj = (Loader_Object *) handle;
    ElfLoader_Object *   elfLoaderObj;
    DLOAD_HANDLE         elfObj;
    _ElfLoader_Object *  _elfLoaderObj;

    GT_2trace (curTrace, GT_ENTER, "ElfLoader_unload", handle, fileId);

    GT_assert (curTrace, (handle != NULL));

#if !defined(IPC_BUILD_OPTIMIZE)
    if (handle == NULL) {
        /*! @retval LOADER_E_HANDLE NULL provided for argument handle. */
        status = LOADER_E_HANDLE;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_load",
                             status,
                             "NULL provided for argument handle");
    }
    else {
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        elfLoaderObj = (ElfLoader_Object *) loaderObj->object;
        GT_assert (curTrace, (elfLoaderObj != NULL));
        _elfLoaderObj = elfLoaderObj->elfLoaderObject;
        GT_assert (curTrace, (_elfLoaderObj != NULL));
        elfObj = elfLoaderObj->elfObject;
        GT_assert (curTrace, (elfObj != NULL));

        if (!DLOAD_unload(elfObj, fileId))  {
            status = LOADER_E_FAIL;
        }

#if !defined(IPC_BUILD_OPTIMIZE)
        if (status < 0) {
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoader_unload",
                                 status,
                                 "Failed to unload ELF file!");
        }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

        tmpStatus = OsalKfile_close ((OsalKfile_Handle *)
                                                 &(_elfLoaderObj->fileDesc));
        if ((tmpStatus < 0) && (status >= 0)) {
            status = tmpStatus;
#if !defined(IPC_BUILD_OPTIMIZE)
            GT_setFailureReason (curTrace,
                                 GT_4CLASS,
                                 "ElfLoader_unload",
                                 status,
                                 "Failed to close the file!");
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
#if !defined(IPC_BUILD_OPTIMIZE)
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_unload", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to retrieve the target address of a symbol from the
 *              specified file.
 *
 *  @param      handle   Handle to the loader instance
 *  @param      fileId   ID of the file received from the load function
 *  @param      symName  Name of the symbol
 *  @param      symValue Return parameter: Symbol address
 *
 *  @sa
 */
Int
ElfLoader_getSymbolAddress (Loader_Handle       handle,
                            UInt32              fileId,
                            String              symName,
                            UInt32 *            symValue)
{
    Int                  status = LOADER_SUCCESS;
    Loader_Object *      loaderObj = (Loader_Object *) handle;
    ElfLoader_Object *   elfLoaderObj;
    DLOAD_HANDLE         elfObj;

    GT_4trace (curTrace, GT_ENTER, "ElfLoader_getSymbolAddress",
               handle, fileId, symName, symValue);

    GT_1trace (curTrace, GT_1CLASS,
                 "ElfLoader_getSymbolAddress: symName [%s]\n",
                 symName);

    GT_assert (curTrace, (handle != NULL));

    elfLoaderObj = (ElfLoader_Object *) loaderObj->object;
    GT_assert (curTrace, (elfLoaderObj != NULL));
    elfObj = elfLoaderObj->elfObject;
    GT_assert (curTrace, (elfObj != NULL));

    if (!DLOAD_query_symbol(elfObj, fileId, (const char *)symName,
                            (TARGET_ADDRESS *)symValue))  {
        status = LOADER_E_FAIL;
    }

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_getSymbolAddress", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function to retrieve the entry point of the specified file.
 *
 *  @param      handle   Handle to the loader instance
 *  @param      fileId   ID of the file received from the load function
 *  @param      entryPt  Return parameter: Entry point of the executable
 *
 *  @sa         ElfLoader_load
 */
Int
ElfLoader_getEntryPt (Loader_Handle     handle,
                      UInt32            fileId,
                      UInt32 *          entryPt)
{
    Int                  status = LOADER_SUCCESS;
    Loader_Object *      loaderObj = (Loader_Object *) handle;
    ElfLoader_Object *   elfLoaderObj;
    DLOAD_HANDLE         elfObj;

    GT_3trace (curTrace, GT_ENTER, "ElfLoader_getEntryPt",
               handle, fileId, entryPt);

    GT_assert (curTrace, (handle  != NULL));
    GT_assert (curTrace, (entryPt != NULL));

    elfLoaderObj = (ElfLoader_Object *) loaderObj->object;
    GT_assert (curTrace, (elfLoaderObj != NULL));
    elfObj = elfLoaderObj->elfObject;
    GT_assert (curTrace, (elfObj != NULL));

    if (!DLOAD_get_entry_point(elfObj, fileId, (TARGET_ADDRESS *)entryPt)) {
       status = LOADER_E_FAIL;
    }

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_getEntryPt",
                             status,
                             "Failed to get ELF file entry point!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_getEntryPt", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function that returns section information given the name of
 *              section and number of bytes to read
 *              For ELF dynamic executables, the data to be found in
 *              ".<section_name>" must be delimited by two
 *              exported (into the .dynsym table) symbols named
 *              "<section_name>_Start" and "<section_name>_End" respectively.
 *              For Example, given:
 *                ".<section_name>"         = ".Ipc_SysMgr_Config"
 *                "<section_name>_Start"    = "Ipc_SysMgr_Config_Start"
 *                "<section_name>_End"      = "Ipc_SysMgr_Config_End"
 *              if "<section_name>_End" is missing, this implies zero data size,
 *              in which case only the section start address is of interest.
 *              The "<section_name>_Start" symbol is assumed to have the same
 *              target address as the section ".<section_name>" .
 *
 *  @param      handle      Handle to the ProcMgr object
 *  @param      fileId      ID of the file received from the load function
 *  @param      sectionName Name of section whose info is to be retrieved.
 *  @param      sectionInfo Return parameter
 *
 *  @sa
 */
Int ElfLoader_getSectionInfo (Loader_Handle         handle,
                               UInt32                fileId,
                               String                sectionName,
                               ProcMgr_SectionInfo * sectionInfo)
{
    Int                  status = LOADER_SUCCESS;
    Loader_Object *      loaderObj = (Loader_Object *) handle;
    ElfLoader_Object *   elfLoaderObj;
    DLOAD_HANDLE         elfObj;
    UInt32               sectAddr = 0;
    UInt32               sectSize = 0;

    GT_4trace (curTrace,
               GT_ENTER,
               "ElfLoader_getSectionInfo",
               handle,
               fileId,
               sectionName,
               sectionInfo);

    GT_assert (curTrace, (handle      != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (sectionName != NULL));
    /* Number of bytes to be read can be zero */
    GT_assert (curTrace, (sectionInfo != NULL));

    elfLoaderObj = (ElfLoader_Object *) loaderObj->object;
    GT_assert (curTrace, (elfLoaderObj != NULL));
    elfObj = elfLoaderObj->elfObject;
    GT_assert (curTrace, (elfObj != NULL));

    if (!DLOAD_get_section_info(elfObj, fileId, (const char *)sectionName,
                                (TARGET_ADDRESS *)&sectAddr, &sectSize))  {
        status = LOADER_E_FAIL;
    }
    else {
        sectionInfo->physicalAddress = sectAddr;
        sectionInfo->virtualAddress = sectAddr;
        sectionInfo->size = sectSize;
        sectionInfo->sectId = 0; // Not needed
    }

#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_getSectionInfo",
                             status,
                             "Failed to get ELF file section information!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_getSectionInfo", status);


    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*  @brief      Function that returns section data into a buffer, given section
 *              information to be read.
 *              For ELF dynamic executables, the data to be found in
 *              ".<section_name>" must be delimited by two
 *              exported (into the .dynsym table) symbols named
 *              "<section_name>_Start" and "<section_name>_End" respectively.
 *              For Example, given:
 *                ".<section_name>"         = ".Ipc_ResetVector"
 *                "<section_name>_Start"    = "Ipc_ResetVector_Start"
 *                "<section_name>_End"      = "Ipc_ResetVector_End"
 *              if "<section_name>_End" is missing, this implies zero data size,
 *              in which case only the section start address is of interest.
 *
 *  @param      handle      Handle to the ProcMgr object
 *  @param      fileId      ID of the file received from the load function
 *  @param      sectionInfo Section info to be read.
 *  @param      buffer      Return parameter
 *
 *  @sa
 */
Int ElfLoader_getSectionData (Loader_Handle        handle,
                               UInt32               fileId,
                               ProcMgr_SectionInfo * sectionInfo,
                               Ptr                  buffer)
{
    Loader_Object     *  loaderObj = (Loader_Object *) handle;
    ElfLoader_Object  *  elfLoaderObj;
    _ElfLoader_Object *  _elfLoaderObj;
    Processor_Handle     procHandle;
    UInt32               procAddr_masterPhys;
    ProcMgr_AddrInfo     aInfo;
    UInt32               numBytes;
    Int                  status = LOADER_SUCCESS;


    GT_4trace (curTrace,
               GT_ENTER,
               "ElfLoader_getSectionData",
               handle,
               fileId,
               sectionInfo,
               buffer);

    GT_assert (curTrace, (handle      != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (sectionInfo != NULL));
    /* Number of bytes to be read can be zero */
    GT_assert (curTrace, (buffer != NULL));

    /* Extract the Processor object from the depths of the Loader Object: */
    elfLoaderObj = (ElfLoader_Object *) loaderObj->object;
    GT_assert (curTrace, (elfLoaderObj != NULL));
    _elfLoaderObj = elfLoaderObj->elfLoaderObject;
    GT_assert (curTrace, (_elfLoaderObj != NULL));
    procHandle = _elfLoaderObj->procHandle;
    GT_assert (curTrace, (procHandle != NULL));

    numBytes = sectionInfo->size;
    /* Read numBytes bytes from sectionInfo->physicalAddress on target */

    /* Translate slave phys to master physical: */
    status = Processor_translateAddr (procHandle,
                                      &procAddr_masterPhys,
                                      sectionInfo->physicalAddress);
    if (status >= 0)  {
        aInfo.addr [ProcMgr_AddrType_MasterPhys] = procAddr_masterPhys;
        aInfo.addr [ProcMgr_AddrType_SlaveVirt]  = sectionInfo->physicalAddress;
        aInfo.size = numBytes;
        aInfo.isCached = FALSE;

        /*
         * Map master physical address to master virtual: this does NOT
         * program the slave MMU:
         */
        status = _ProcMgr_map (_elfLoaderObj->pmHandle,
                               (  ProcMgr_MASTERKNLVIRT
                                | ProcMgr_SLAVEVIRT),
                               &aInfo,
                               ProcMgr_AddrType_MasterPhys);

        if (status >= 0)  {
            /* Suspect this function has not been validated, so do a Memcopy */
            status = ProcMgr_read (_elfLoaderObj->pmHandle,
                                   sectionInfo->physicalAddress,
                                   &numBytes,
                                   buffer);
            if (status < 0)  {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoader_getSectionData",
                                     status,
                                     "Failed to read from target memory!");
            }
            /* Returned number of bytes read should be what we expected: */
            else if (numBytes != sectionInfo->size)  {
                status = LOADER_E_FAIL;
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "ElfLoader_getSectionData",
                                     status,
                                     "Got wrong numBytes read from target!");

            }
            else {
                 GT_2trace (curTrace, GT_1CLASS,
                 "ElfLoader_getSectionData: Read 0x%x bytes from target at"
                 " address 0x%x\n",
                 numBytes, sectionInfo->physicalAddress);
            }
        }
        else {
            GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_getSectionData",
                             status,
                             "ProcMgr_map failed!");
        }
    }
    else {
        GT_setFailureReason (curTrace,
                                GT_4CLASS,
                                "ElfLoader_getSectionData",
                                status,
                                "Processor_translateAddr failed!");
    } /* if (status >= 0) */


#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "ElfLoader_getSectionData",
                             status,
                             "No ELF file section information!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "ElfLoader_getSectionData", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
