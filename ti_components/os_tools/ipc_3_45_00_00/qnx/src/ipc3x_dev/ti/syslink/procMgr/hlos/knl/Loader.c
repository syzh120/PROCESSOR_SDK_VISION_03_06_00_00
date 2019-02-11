/*
 *  @file   Loader.c
 *
 *  @brief      Generic loader that calls into specific loader instance
 *              through function table interface.
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


/*-------------------------   Standard headers   -----------------------------*/
#include <ti/syslink/Std.h>


/*-------------------------   Module headers   -------------------------------*/
#include <ti/syslink/inc/knl/LoaderDefs.h>
#include <ti/syslink/inc/knl/Loader.h>

/*-------------------------   OSAL and utils   -------------------------------*/
#include <ti/syslink/utils/Trace.h>

#if defined (__cplusplus)
extern "C" {
#endif


/* =============================================================================
 * Functions called by ProcMgr
 * =============================================================================
 */
/*!
 *  @brief      Function to attach to the Loader.
 *
 *              This function calls into the specific loader implementation to
 *              attach to it.
 *              This function is called from the ProcMgr attach function, and
 *              hence is useful to perform any activities that may be required
 *              to be done after the slave is powered up. Depending on the type
 *              of loader, this function may or may not perform any activities.
 *
 *  @param      handle     Handle to the Loader object
 *
 *  @sa         Loader_detach
 */
inline
Int
Loader_attach (Loader_Handle handle, Loader_AttachParams * params)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_2trace (curTrace, GT_ENTER, "Loader_attach", handle, params);

    GT_assert (curTrace, (params != NULL));
    GT_assert (curTrace, ((params->params->bootMode != ProcMgr_BootMode_Boot) \
                       || (handle != NULL)));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    if(loaderHandle != NULL) {
        loaderHandle->bootMode = params->params->bootMode;
        if (loaderHandle->bootMode == ProcMgr_BootMode_Boot) {
            GT_assert (curTrace, (loaderHandle->loaderFxnTable.attach != NULL));
            status = loaderHandle->loaderFxnTable.attach (handle, params);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "Loader_attach",
                                     status,
                                     "Failed to attach to the specific loader!");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }
    }
    GT_1trace (curTrace, GT_LEAVE, "Loader_attach", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to detach from the Loader.
 *
 *              This function calls into the specific loader implementation to
 *              detach from it.
 *              This function is called from the ProcMgr detach function, and
 *              hence is useful to perform any activities that may be required
 *              to be done while the slave is still powered up.
 *              Depending on the type of loader, this function may or may not
 *              perform any activities.
 *
 *  @param      handle     Handle to the Loader object
 *
 *  @sa         Loader_attach
 */
inline
Int
Loader_detach (Loader_Handle handle)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_1trace (curTrace, GT_ENTER, "Loader_detach", handle);

    GT_assert (curTrace, (handle != NULL));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    if (loaderHandle != NULL) {

        if (loaderHandle->bootMode == ProcMgr_BootMode_Boot) {
            GT_assert (curTrace, (loaderHandle->loaderFxnTable.detach != NULL));
            status = loaderHandle->loaderFxnTable.detach (handle);
#if !defined(IPC_BUILD_OPTIMIZE)
            if (status < 0) {
                GT_setFailureReason (curTrace,
                                     GT_4CLASS,
                                     "Loader_detach",
                                     status,
                                     "Failed to detach from the specific loader!");
            }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */
        }

    }
    GT_1trace (curTrace, GT_LEAVE, "Loader_detach", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to load the slave Processor.
 *
 *              This function calls into the specific loader implementation to
 *              load the slave processor.
 *              This function loads the specified executable on the slave
 *              processor. The handle specifies the specific loader instance to
 *              be used. The params are specific to the loader and may be NULL
 *              if the loader does not require any.
 *
 *  @param      handle     Handle to the Loader object
 *  @param      imagePath  Full file path
 *  @param      argc       Number of arguments
 *  @param      argv       String array of arguments
 *  @param      params     Loader specific parameters
 *  @param      fileId     Return parameter: ID of the loaded file
 *
 *  @sa
 */
inline
Int
Loader_load (Loader_Handle handle,
             String        imagePath,
             UInt32        argc,
             String *      argv,
             Ptr           params,
             UInt32 *      fileId)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_5trace (curTrace, GT_ENTER, "Loader_load",
               handle, imagePath, argc, argv, params);

    GT_assert (curTrace, (handle != NULL));
    GT_assert (curTrace, (fileId != NULL));
    /* imagePath may be NULL if a non-file based loader is used. In that case,
     * loader-specific params will contain the required information.
     */

    GT_assert (curTrace,
               (   ((argc == 0) && (argv == NULL))
                || ((argc != 0) && (argv != NULL)))) ;

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace, (loaderHandle->loaderFxnTable.load != NULL));
    status = loaderHandle->loaderFxnTable.load (handle,
                                                imagePath,
                                                argc,
                                                argv,
                                                params,
                                                fileId);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_load",
                             status,
                             "Failed to load file on the slave processor!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_load", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to function to load symbols for the specified file.
 *
 *              This function calls into the specific loader implementation to
 *              load the symbols for the specified file.
 *              This function allows the symbols from this file to be usable
 *              when linked against another object file. External symbols will
 *              be made available for global symbol linkage.
 *              NOTE: This function is only relevant for dynamic loader.
 *                    Other loaders can return LOADER_E_NOTIMPL.
 *
 *  @param      handle     Handle to the Loader object
 *  @param      imagePath  Full file path
 *  @param      params     Loader specific parameters
 *
 *  @sa         Loader_load
 */
inline
Int
Loader_loadSymbols (Loader_Handle handle,
                    String        imagePath,
                    Ptr           params)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_3trace (curTrace, GT_ENTER, "Loader_loadSymbols",
               handle, imagePath, params);

    GT_assert (curTrace, (handle != NULL));
    /* imagePath may be NULL if a non-file based loader is used. In that case,
     * loader-specific params will contain the required information.
     */

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace, (loaderHandle->loaderFxnTable.load != NULL));
    status = loaderHandle->loaderFxnTable.loadSymbols (handle,
                                                       imagePath,
                                                       params);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_loadSymbols",
                             status,
                             "Failed to load symbols for the slave processor!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_loadSymbols", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to unload the previously loaded file on the slave
 *              processor.
 *
 *              This function calls into the specific loader implementation to
 *              unload the previously loaded file identified by the fileId.
 *              This function unloads the file that was previously loaded on the
 *              slave processor through the Loader_load API. It frees up any
 *              resources that were allocated during Loader_load for this file.
 *              The fileId received from the load function must be passed to
 *              this function.
 *
 *  @param      handle     Handle to the Loader object
 *  @param      fileId     ID of the loaded file to be unloaded
 *
 *  @sa         Loader_load
 */
inline
Int
Loader_unload (Loader_Handle handle, UInt32 fileId)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_2trace (curTrace, GT_ENTER, "Loader_unload", handle, fileId);

    GT_assert (curTrace, (handle != NULL));
    /* Cannot check for fileId because it is loader dependent. */

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace, (loaderHandle->loaderFxnTable.unload != NULL));
    status = loaderHandle->loaderFxnTable.unload (handle, fileId);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_unload",
                             status,
                             "Failed to unload file from the slave processor!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_unload", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to retrieve the target address of a symbol from the
 *              specified file.
 *
 *              This function calls into the specific loader implementation to
 *              retrieve the target address of a specified symbol.
 *              The fileId received from the load function must be passed to
 *              this function.
 *
 *  @param      handle     Handle to the Loader object
 *  @param      fileId     ID of the loaded file
 *  @param      symName    Name of the symbol to be checked
 *  @param      symValue   Return parameter: Target address of specified symbol.
 *
 *  @sa         Loader_load
 */
inline
Int
Loader_getSymbolAddress (Loader_Handle handle,
                         UInt32        fileId,
                         String        symName,
                         UInt32 *      symValue)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_4trace (curTrace, GT_ENTER, "Loader_getSymbolAddress",
               handle,
               fileId,
               symName,
               symValue);

    GT_assert (curTrace, (handle != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (symName  != NULL));
    GT_assert (curTrace, (symValue != NULL));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace,
               (loaderHandle->loaderFxnTable.getSymbolAddress != NULL));
    status = loaderHandle->loaderFxnTable.getSymbolAddress (handle,
                                                            fileId,
                                                            symName,
                                                            symValue);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_getSymbolAddress",
                             status,
                             "Failed to get the symbol address!");
        GT_1trace (curTrace, GT_4CLASS, "Symbol Name: %s", symName);
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_getSymbolAddress", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}


/*!
 *  @brief      Function to retrieve the entry point of the specified file.
 *
 *              This function calls into the specific loader implementation to
 *              retrieve the entry point of the loaded executable.
 *              The fileId received from the load function must be passed to
 *              this function.
 *
 *  @param      handle     Handle to the Loader object
 *  @param      fileId     ID of the loaded file
 *  @param      entryPt    Return parameter: Entry point of the loaded file
 *
 *  @sa         Loader_load
 */
inline
Int
Loader_getEntryPt (Loader_Handle handle,
                   UInt32        fileId,
                   UInt32 *      entryPt)
{
    Int             status       = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_3trace (curTrace, GT_ENTER, "Loader_getEntryPt",
               handle,
               fileId,
               entryPt);

    GT_assert (curTrace, (handle != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (entryPt != NULL));

    /* No parameter validation here since this is an internal module, and
     * validation has already happened at the ProcMgr level.
     */
    GT_assert (curTrace,
               (loaderHandle->loaderFxnTable.getEntryPt != NULL));
    status = loaderHandle->loaderFxnTable.getEntryPt (handle,
                                                      fileId,
                                                      entryPt);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_getEntryPt",
                             status,
                             "Failed to get the file entry point!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_getEntryPt", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}

/*!
 *  @brief      Function that returns section information given the name of
 *              section and number of bytes to read
 *
 *  @param      handle      Handle to the ProcMgr object
 *  @param      fileId      ID of the file received from the load function
 *  @param      sectionName Name of section to be retrieved
 *  @param      size        Number of bytes to be reaad from section's data
 *  @param      sectionInfo Return parameter
 *
 *  @sa
 */
Int Loader_getSectionInfo (Loader_Handle         handle,
                           UInt32                fileId,
                           String                sectionName,
                           ProcMgr_SectionInfo * sectionInfo)
{
    Int status = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_4trace (curTrace,
               GT_ENTER,
               "Loader_getSectionInfo",
               handle,
               fileId,
               sectionName,
               sectionInfo);

    GT_assert (curTrace, (handle      != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (sectionName != NULL));
    /* Number of bytes to be read can be zero */
    GT_assert (curTrace, (sectionInfo != NULL));
    GT_assert (curTrace,
               (loaderHandle->loaderFxnTable.getSectionInfo != NULL));

    status = loaderHandle->loaderFxnTable.getSectionInfo (handle,
                                                          fileId,
                                                          sectionName,
                                                          sectionInfo);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        status = LOADER_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_getSectionInfo",
                             status,
                             "Failed to get the file entry point!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_getSectionInfo", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}

/*  @brief      Function that returns section data in a buffer given section id
 *              and size to be read
 *
 *  @param      handle      Handle to the ProcMgr object
 *  @param      fileId      ID of the file received from the load function
 *  @param      sectionInfo Structure filled by Loader_getSectionInfo.
 *  @param      buffer      Return parameter
 *
 *  @sa
 */
Int Loader_getSectionData (Loader_Handle        handle,
                           UInt32               fileId,
                           ProcMgr_SectionInfo * sectionInfo,
                           Ptr                  buffer)
{
    Int status = LOADER_SUCCESS;
    Loader_Object * loaderHandle = (Loader_Object *) handle;

    GT_4trace (curTrace,
               GT_ENTER,
               "Loader_getSectionData",
               handle,
               fileId,
               sectionInfo,
               buffer);

    GT_assert (curTrace, (handle      != NULL));
    /* Cannot check for fileId because it is loader dependent. */
    GT_assert (curTrace, (sectionInfo != NULL));
    /* Number of bytes to be read and sectId can be zero */
    GT_assert (curTrace, (buffer != NULL));
    GT_assert (curTrace,
               (loaderHandle->loaderFxnTable.getSectionData != NULL));

    status = loaderHandle->loaderFxnTable.getSectionData (handle,
                                                          fileId,
                                                          sectionInfo,
                                                          buffer);
#if !defined(IPC_BUILD_OPTIMIZE)
    if (status < 0) {
        status = LOADER_E_FAIL;
        GT_setFailureReason (curTrace,
                             GT_4CLASS,
                             "Loader_getSectionData",
                             status,
                             "Failed to get the file entry point!");
    }
#endif /* if !defined(IPC_BUILD_OPTIMIZE) */

    GT_1trace (curTrace, GT_LEAVE, "Loader_getSectionData", status);

    /*! @retval LOADER_SUCCESS Operation successful */
    return status;
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
