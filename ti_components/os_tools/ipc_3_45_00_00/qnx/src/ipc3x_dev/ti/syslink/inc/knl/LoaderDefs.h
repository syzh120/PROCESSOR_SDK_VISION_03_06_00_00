/**
 *  @file   LoaderDefs.h
 *
 *  @brief      Definitions for the Loader interface.
 *
 *
 */
/*
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


#ifndef LoaderDefs_H_0x485f
#define LoaderDefs_H_0x485f


/* Module level headers */
#include <ti/syslink/ProcMgr.h>
#include <ProcDefs.h>


#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 *  Macros and types
 * =============================================================================
 */
/*!
 *  @brief  Configuration parameters for attaching to the Loader
 */
typedef struct Loader_AttachParams_tag {
    ProcMgr_AttachParams *  params;
    /*!< Common attach parameters for ProcMgr */
    Processor_Handle        procHandle;
    /*!< Handle to the Processor instance */
    ProcMgr_Handle          pmHandle;
    /*!< Handle to the ProcMgr instance */
    Processor_ProcArch      procArch;
    /*!< Processor architecture */
} Loader_AttachParams ;

/* Forward declaration for Loader */
typedef struct Loader_Object_tag Loader_Object;

/*!
 *  @brief  Defines Loader object handle
 */
typedef Loader_Object * Loader_Handle;


/* =============================================================================
 *  Function pointer types to be implemented by specific Loaders.
 * =============================================================================
 */
/*!
 *  @brief  Function pointer type for the function to attach to the Loader.
 *
 *          This function is called from the ProcMgr attach function, and hence
 *          is useful to perform any activities that may be required to be done
 *          after the slave is powered up. Depending on the type of loader, this
 *          function may or may not perform any activities.
 */
typedef Int (*Loader_AttachFxn) (Loader_Handle         handle,
                                 Loader_AttachParams * params);

/*!
 *  @brief  Function pointer type for the function to detach from the Loader.
 *
 *          This function is called from the ProcMgr detach function, and hence
 *          is useful to perform any finalization activities that may be
 *          required to be done while the slave is still powered up.
 *          Depending on the type of loader, this function may or may not
 *          perform any activities.
 */
typedef Int (*Loader_DetachFxn) (Loader_Handle handle);

/*!
 *  @brief  Function pointer type for the function to load the slave processor.
 *          Returns file ID in the passed fileId parameter.
 */
typedef Int (*Loader_LoadFxn) (Loader_Handle handle,
                               String        imagePath,
                               UInt32        argc,
                               String *      argv,
                               Ptr           params,
                               UInt32 *      fileId);

/*!
 *  @brief  Function pointer type for the function to load symbols for the
 *          specified file. This will allow the symbols to be usable when linked
 *          against another object file.
 *          External symbols will be made available for global symbol linkage.
 *          NOTE: This function is only relevant for dynamic loader. Other
 *                loaders can return LOADER_E_NOTIMPL.
 */
typedef Int (*Loader_LoadSymbolsFxn) (Loader_Handle handle,
                                      String        imagePath,
                                      Ptr           params);

/*!
 *  @brief  Function pointer type for the function to unload the previously
 *          loaded file on the slave processor. The fileId received from the
 *          load function must be passed to this function.
 */
typedef Int (*Loader_UnloadFxn) (Loader_Handle handle, UInt32 fileId);

/*!
 *  @brief  Function pointer type for the function to retrieve the target
 *          address of a symbol from the specified file.
 *          The fileId received from the load function must be passed to this
 *          function.
 */
typedef Int (*Loader_GetSymbolAddressFxn) (Loader_Handle handle,
                                           UInt32        fileId,
                                           String        symName,
                                           UInt32 *      symValue);

/*!
 *  @brief  Function pointer type for the function to retrieve the entry point
 *          of the specified file.
 *          The fileId received from the load function must be passed to this
 *          function.
 */
typedef Int (*Loader_GetEntryPtFxn) (Loader_Handle handle,
                                     UInt32        fileId,
                                     UInt32 *      entryPt);
/*!
 *  @brief  Function that returns section information given the name of section
 *          and number of bytes to read
 */
typedef Int (*Loader_GetSectionInfo) (Loader_Handle         handle,
                                      UInt32                fileId,
                                      String                sectionName,
                                      ProcMgr_SectionInfo * sectionInfo);

/*!
 *  @brief  Function that returns section data in a buffer given section info
 *          filled by previous call to Loader_GetSectionInfo.
 */
typedef Int (*Loader_GetSectionData) (Loader_Handle         handle,
                                      UInt32                fileId,
                                      ProcMgr_SectionInfo * sectionInfo,
                                      Ptr                   buffer);


/* =============================================================================
 *  Function table interface
 * =============================================================================
 */
/*!
 *  @brief  Function table interface for Loader.
 */
typedef struct Loader_FxnTable_tag {
    Loader_AttachFxn           attach;
    /*!< Function to attach to the loader */
    Loader_DetachFxn           detach;
    /*!< Function to detach from the loader */
    Loader_LoadFxn             load;
    /*!< Function to load the slave executable */
    Loader_LoadSymbolsFxn      loadSymbols;
    /*!< Function to load symbols for the slave executable */
    Loader_UnloadFxn           unload;
    /*!< Function to unload the slave executable */
    Loader_GetSymbolAddressFxn getSymbolAddress;
    /*!< Function to get symbol address from executable */
    Loader_GetEntryPtFxn       getEntryPt;
    /*!< Function to get entry point from executable */
    Loader_GetSectionInfo      getSectionInfo;
    /*!< Function to get section info from executable */
    Loader_GetSectionData      getSectionData;
    /*!< Function to get section data from executable */
} Loader_FxnTable;


/* =============================================================================
 * Client Provided Functions
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
 *  @brief   Enumerates the values used for repositioning the file position
 *           indicator.
 */
typedef enum {
    LoaderFile_Pos_SeekSet  = 0x0,
    /*!< Seek from beginning of file. */
    LoaderFile_Pos_SeekCur  = 0x1,
    /*!< Seek from current position. */
    LoaderFile_Pos_SeekEnd  = 0x2,
    /*!< Seek from end of file. */
    LoaderFile_Pos_EndValue = 0x3
    /*!< End delimiter indicating start of invalid values for this enum */
} LoaderFile_Pos;


/*!
 *  @brief  Function pointer type for the function to seek to a position in the
 *          file based on the values for offset and pos.
 */
typedef Int (*LoaderFile_Seek) (Ptr            clientHandle,
                                Ptr            fileDesc,
                                Int32          offset,
                                LoaderFile_Pos pos);

/*!
 *  @brief  Function pointer type for the function to return the current file
 *          position in the file.
 *          Returns the position in the file.
 */
typedef UInt32 (*LoaderFile_Tell) (Ptr clientHandle, Ptr fileDesc);

/*!
 *  @brief  Function pointer type for the function to read (size * count) bytes
 *          of data from the file.
 *          Returns the bytes actually read.
 */
typedef UInt32 (*LoaderFile_Read) (Ptr    clientHandle,
                                   Ptr    fileDesc,
                                   Char * buffer,
                                   UInt32 size,
                                   UInt32 count);
/*
 *  Function table interface for File I/O Interface
 *
 */
typedef struct LoaderFile_FxnTable_tag {
    LoaderFile_Seek    seek;
    /*!< File I/O Interface: Seek function */
    LoaderFile_Tell    tell;
    /*!< File I/O Interface: Tell function */
    LoaderFile_Read    read;
    /*!< File I/O Interface: Read function */
} LoaderFile_FxnTable;

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
 *  @brief  Function pointer type for the function to allocate specified bytes
 *          of memory.
 *          Returns a pointer to the memory buffer.
 */
typedef Ptr (*LoaderMem_Alloc) (Ptr clientHandle, UInt32 size);

/*!
 *  @brief  Function pointer type for the function to free the specified buffer.
 */
typedef Void (*LoaderMem_Free) (Ptr clientHandle, Ptr buffer, UInt32 size);

/*
 *  Function table interface for Host Memory management Interface
 *
 */
typedef struct LoaderMem_FxnTable_tag {
    LoaderMem_Alloc   alloc;
    /*!< Host Memory management Interface: Alloc function */
    LoaderMem_Free    free;
    /*!< Host Memory management Interface: Free function */
} LoaderMem_FxnTable;


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
 *  @var     LOADER_SEG_EXECUTABLE
 *
 *  @brief   Segment characteristics: Memory must be executable
 */
#define LOADER_SEG_EXECUTABLE  0x1

/*!
 *  @var     LOADER_SEG_RELOCATABLE
 *
 *  @brief   Segment characteristics: Segment must be relocatable
 */
#define LOADER_SEG_RELOCATABLE  0x2

/*!
 *  @brief   Define structure to represent placement and size details of a
 *           segment to be loaded.
 */
typedef struct Loader_MemSegment_tag {
   UInt32   trgPage;
   /*!< Requested/returned memory page */
   UInt32   trgAddress;
   /*!< Requested/returned address */
   UInt32   objSize;
   /*!< Size of init'd part of segment */
   UInt32   memSize;
   /*!< Size of memory block for segment */
} Loader_MemSegment;

/*!
 *  @brief   Define structure to represent a target memory request made by the
 *           core loader on behalf of a segment that the loader needs to
 *           relocate and write into target memory.
 */
typedef struct Loader_MemRequest_tag {
   Ptr                        fileDesc;
   /*!< File being loaded */
   Loader_MemSegment *        segment;
   /*!< Object for request/return alloc */
   Void *                     hostAddress;
   /*!< Return host pointer from copy function */
   Bool                       isLoaded;
   /*!< Returned as true if segment is already in target memory */
   UInt32                     offset;
   /*!< File offset of segment's raw data */
   UInt32                     endian;
   /*!< Endianness of target opp host */
   UInt32                     flags;
   /*!< allocation request flags */
   UInt32                     align;
   /*!< Alignment of target memory block */
} Loader_MemRequest;

/*!
 *  @brief  Function pointer type for the function to allocate specified bytes
 *          of target memory.
 */
typedef Int (*LoaderTrgMem_Alloc) (Ptr                  clientHandle,
                                   Loader_MemRequest *  memReq);

/*!
 *  @brief  Function pointer type for the function to free the specified target
 *          memory buffer.
 */
typedef Int (*LoaderTrgMem_Free) (Ptr                   clientHandle,
                                  Loader_MemRequest *   memReq);

/*
 *  Function table interface for Target Memory Allocator Interface
 *
 */
typedef struct LoaderTrgMem_FxnTable_tag {
    LoaderTrgMem_Alloc alloc;
    /*!< Target Memory Allocator Interface: Alloc function */
    LoaderTrgMem_Free  free;
    /*!< Target Memory Allocator Interface: Free function */
} LoaderTrgMem_FxnTable;

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
 *  @brief  Function pointer type for the function to read data from target address to
 *          provided host accessible buffer..
 */
typedef Int (*LoaderTrgWrite_Read) (Ptr    clientHandle,
                                       Ptr    ptr,
                                       UInt32 size,
                                       UInt32 nmemb,
                                       Ptr    src);

/*!
 *  @brief  Function pointer type for the function to copy data into the
 *          provided segment.
 */
typedef Int (*LoaderTrgWrite_Copy) (Ptr                 clientHandle,
                                    Loader_MemRequest * memReq);

/*!
 *  @brief  Function pointer type for the function to write data to the target
 *          memory.
 */
typedef Int (*LoaderTrgWrite_Write) (Ptr                 clientHandle,
                                     Loader_MemRequest * memReq);

/*!
 *  @brief  Function pointer type for the function to start execution of the
 *          target from the given execAddr.
 */
typedef Int (*LoaderTrgWrite_Execute) (Ptr    clientHandle,
                                       UInt32 execAddr);

/*!
 *  @brief  Function pointer type for the function to map slave address.
 */
typedef Int (*LoaderTrgWrite_Map) (Ptr                clientHandle,
                                   ProcMgr_MapMask    mapMask,
                                   ProcMgr_AddrInfo * addrInfo,
                                   ProcMgr_AddrType   srcAddrType);

/*!
 *  @brief  Function pointer type for the function to unmap slave address.
 */
typedef Int (*LoaderTrgWrite_Unmap) (Ptr      clientHandle,
                                     ProcMgr_MapMask    mapMask,
                                     ProcMgr_AddrInfo * addrInfo,
                                     ProcMgr_AddrType   srcAddrType);

/*!
 *  @brief  Function pointer type for the function to translate addresses.
 */
typedef Int (*LoaderTrgWrite_translate) (Ptr              clientHandle,
                                         Ptr *            dstAddr,
                                         ProcMgr_AddrType dstAddrType,
                                         Ptr              srcAddr,
                                         ProcMgr_AddrType srcAddrType);

/*
 *  Function table interface for Target Memory Access / Write Services
 *
 */
typedef struct LoaderTrgWrite_FxnTable_tag {
    LoaderTrgWrite_Copy     copy;
    /*!< Target Memory Access / Write Services: Copy function */
    LoaderTrgWrite_Write    write;
    /*!< Target Memory Access / Write Services: Write function */
    LoaderTrgWrite_Execute  execute;
    /*!< Target Memory Access / Write Services: Execute function */
    LoaderTrgWrite_Map      map;
    /*!< Target Memory Access / map Services: Map function */
    LoaderTrgWrite_Unmap    unmap;
    /*!< Target Memory Access / map Services: Unmap function */
    LoaderTrgWrite_translate translate;
    /*!< Target Memory Access / translate Services: translate function */
} LoaderTrgWrite_FxnTable;


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
 *  @brief  Function pointer type for the function to find and open a dependent
 *          file identified by the dllName parameter, then, if necessary,
 *          initiate a load call to actually load the shared object onto the
 *          target. A successful load will return a file ID that the client can
 *          associate with the newly loaded file.
 *          NOTE: Only applicable for dynamic loader. For other loaders, these
 *                functions do not need to be implemented and can simply return
 *                LOADER_E_NOTIMPL.
 */
typedef Int (*LoaderDll_LoadDependent) (Ptr    clientHandle,
                                        String dllName);

/*!
 *  @brief  Function pointer type for the function to unload a dependent file
 *          identified by the fileId parameter. Then, client must initiate an
 *          unload call to actually unload the shared object to free the target
 *          memory occupied by the object file.
 *          The fileId received from the load function must be passed to this
 *          function.
 *          NOTE: Only applicable for dynamic loader. For other loaders, these
 *                functions do not need to be implemented and can simply return
 *                LOADER_E_NOTIMPL.
 */
typedef Int (*LoaderDll_UnloadDependent) (Ptr clientHandle, UInt32 fileId);

/*
 *  Function table interface for Loading and Unloading of Dependent Files
 *
 */
typedef struct LoaderDll_FxnTable {
    LoaderDll_LoadDependent     load;
    /*!< Loading and Unloading of Dependent Files: Load function */
    LoaderDll_UnloadDependent   unload;
    /*!< Loading and Unloading of Dependent Files: Unload function */
} LoaderDll_FxnTable;


/* =============================================================================
 * Loader structure
 * =============================================================================
 */
/*
 *  Generic loader object. This object defines the handle type for all loader
 *  operations.
 */
struct Loader_Object_tag {
    Loader_FxnTable         loaderFxnTable;
    /*!< Interface function table to plug into the generic Loader. */
    LoaderFile_FxnTable     fileFxnTable;
    /*!< Client function table for File I/O Interface */
    LoaderMem_FxnTable      memFxnTable;
    /*!< Client function table for Host Memory management Interface */
    LoaderTrgMem_FxnTable   trgMemFxnTable;
    /*!< Client function table for Target Memory Allocator Interface */
    LoaderTrgWrite_FxnTable trgWriteFxnTable;
    /*!< Client function table for Target Memory Access / Write Services */
    LoaderDll_FxnTable      dllFxnTable;
    /*!< Client function table for Loading and Unloading of Dependent Files */
    Ptr                     object;
    /*!< Pointer to loader-specific object. */
    UInt16                  procId;
    /*!< Processor ID addressed by this Loader instance. */
    ProcMgr_BootMode      bootMode;
    /*!< Boot mode for the slave processor. */
};


#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* LoaderDefs_H_0x485f */
