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
 * \ingroup SYSTEM_LINK_API
 *
 *
 * @{
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \file   system_link_info.h
 *
 * \brief  System CH Information Data structure
 *
 *******************************************************************************
 */

#ifndef SYSTEM_CH_INFO_H_
#define SYSTEM_CH_INFO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 * \brief Possible fields inside of System_LinkChInfo.flags
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Utility macros to get and set the bit-fields in 32-bit value.
 *
 *******************************************************************************
 */
#define SystemUtils_unpack_bitfield(container, mask, offset)              \
                   (((container) & (mask)) >> (offset))
#define SystemUtils_pack_bitfield(container, value, mask, offset)         \
                   ((UInt32)((UInt32)((container) & ((UInt32)(~((UInt32)(mask)))))) | ((UInt32)(((UInt32)(value) << (offset)) & (mask))))

/* @} */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Channel specific info
 *
 *         Used by a link to set itself up based on channel info of previous
 *         link
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32 flags;
    /**< Refer macros above to set / get values into / from flags */
    UInt32 pitch[SYSTEM_MAX_PLANES];
    /**< Pitch for various formats / planes */
    UInt32 startX;
    /**< Start x position */
    UInt32 startY;
    /**< Start y position */
    UInt32 width;
    /**< channel resolution - width */
    UInt32 height;
    /**< channel resolution - height */
} System_LinkChInfo;

/**
 *******************************************************************************
 *
 *  \brief  In queue params
 *
 *          This structure contains input queue parameters from which a
 *          link gets it's data
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 prevLinkId;
    /**< Previous link ID to which current link will be connected */

    UInt32 prevLinkQueId;
    /**< Previous link Que ID, with which current link
     *   will exchange frames */
} System_LinkInQueParams;

/**
 *******************************************************************************
 *
 * \brief  Out queue params
 *
 *         This structure contains output queue parameters to which a
 *         link is connected to.
 *
 *******************************************************************************
 */
typedef struct {
    UInt32 nextLink;
    /**< Next link ID to which current link will be connected */
} System_LinkOutQueParams;

/**
 *******************************************************************************
 *
 *  \brief LINKs output queue information
 *         Specifies a place holder that describe the output information
 *         of the LINK
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32              numCh;
    /**< No of channel that would be sent out */
    System_LinkChInfo   chInfo[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Each channels configurations */

} System_LinkQueInfo;

/**
 *******************************************************************************
 *
 * \brief LINKs information
 *        Specifies a place holder that describe the LINK information
 *
 *******************************************************************************
 */
typedef struct
{
    UInt32              numQue;
    /**< Number of output queue that a LINK supports */
    System_LinkQueInfo  queInfo[SYSTEM_MAX_OUT_QUE];
    /**< Each queue configurations */
} System_LinkInfo;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */

static inline UInt32 System_Link_Ch_Info_Get_Flag_Buf_Type
                                                (UInt32 container);
static inline UInt32 System_Link_Ch_Info_Set_Flag_Buf_Type
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Link_Ch_Info_Get_Flag_Bitstream_Format
                                                (UInt32 container);
static inline UInt32 System_Link_Ch_Info_Set_Flag_Bitstream_Format
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Link_Ch_Info_Get_Flag_Scan_Format
                                                (UInt32 container);
static inline UInt32 System_Link_Ch_Info_Set_Flag_Scan_Format
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Link_Ch_Info_Get_Flag_Mem_Type
                                                (UInt32 container);
static inline UInt32 System_Link_Ch_Info_Set_Flag_Mem_Type
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update
                                                (UInt32 container);
static inline UInt32 System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update
                                                (UInt32 container,UInt32 value);

static inline UInt32 System_Link_Ch_Info_Get_Flag_Data_Format
                                                (UInt32 container);
static inline UInt32 System_Link_Ch_Info_Set_Flag_Data_Format
                                                (UInt32 container,UInt32 value);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Utility macros to get buffer type in flag field of buffer
 *
 *        Refer Enum System_BufferType for different possible values
 *
 *        Encoded in bit-field (0x0000000F)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Get_Flag_Buf_Type(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x0000000FU, 0x0U);
}

/**
 *******************************************************************************
 *
 * \brief Utility macros to set buffer type in flag field of buffer
 *
 *        Refer Enum System_BufferType for different possible values
 *
 *        Encoded in bit-field (0x0000000F)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Set_Flag_Buf_Type(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x0000000FU, 0x0U);
    return container;
}

/**
 *******************************************************************************
 *
 *  \brief Utility macro to get the coding type in bit stream buffers.
 *
 *         Refer Enum System_BitstreamCodingType for different possible values
 *
 *         Encoded in bit-field (0x000000F0)
 *
 *******************************************************************************
 */

static inline UInt32 System_Link_Ch_Info_Get_Flag_Bitstream_Format(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x000000F0U, (UInt32)4U);
}

/**
 *******************************************************************************
 *
 *  \brief Utility macro to set the coding type in bit stream buffers.
 *
 *         Refer Enum System_BitstreamCodingType for different possible values
 *
 *         Encoded in bit-field (0x000000F0)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Set_Flag_Bitstream_Format(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x000000F0U, (UInt32)4U);
    return container;
}

/**
 *******************************************************************************
 *
 * \brief Utility function to get the scan format in buffer
 *
 *        Refer Enum System_VideoScanFormat for values
 *
 *        Encoded in bit-field (0x00000100)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Get_Flag_Scan_Format(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x00000100U, (UInt32)8U);
}

/**
 *******************************************************************************
 *
 * \brief Utility function to set the scan format in buffer
 *
 *        Refer Enum System_VideoScanFormat for values
 *
 *        Encoded in bit-field (0x00000100)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Set_Flag_Scan_Format(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x00000100U, (UInt32)8U);
    return container;
}

 /**
 *******************************************************************************
 *
 *  \brief Utility macro to get the memtype fields from buffer.
 *
 *         Refer Enum System_MemoryType for values
 *
 *         Encoded in bit-field (0x00000200)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Get_Flag_Mem_Type(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x00000200U, (UInt32)9U);
}

/**
 *******************************************************************************
 *
 *  \brief Utility macro to set the memtype fields from buffer.
 *
 *         Refer Enum System_MemoryType for values
 *
 *         Encoded in bit-field (0x00000200)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Set_Flag_Mem_Type(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x00000200U, (UInt32)9U);
    return container;
}


/**
 *******************************************************************************
 *
 *   \brief Macro to get run-time params fields in buffer
 *
 *         1: params changed, do run time parameter update
 *         0: No parameter update
 *
 *         Ignored during create time
 *
 *         Encoded in bit-field (0x00000400)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Get_Flag_Is_Rt_Prm_Update(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x00000400U, (UInt32)10U);
}

/**
 *******************************************************************************
 *
 *   \brief Macro to set run-time params fields in buffer
 *
 *         1: params changed, do run time parameter update
 *         0: No parameter update
 *
 *         Ignored during create time
 *
 *         Encoded in bit-field (0x00000400)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Set_Flag_Is_Rt_Prm_Update(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x00000400U, (UInt32)10U);
    return container;
}


/**
 *******************************************************************************
 *
 *  \brief Macro to get data format in system_buffer flag field
 *
 *         Refer Enum System_VideoDataFormat for different possible values
 *
 *         Encoded in bit-field (0x0FFFF000)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Get_Flag_Data_Format(UInt32 container)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    return SystemUtils_unpack_bitfield(container, 0x0FFFF000U, (UInt32)12U);
}


/**
 *******************************************************************************
 *
 *  \brief Macro to set data format in system_buffer flag field
 *
 *         Refer Enum System_VideoDataFormat for different possible values
 *
 *         Encoded in bit-field (0x0FFFF000)
 *
 *******************************************************************************
 */
static inline UInt32 System_Link_Ch_Info_Set_Flag_Data_Format(UInt32 container,UInt32 value)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */

    container = SystemUtils_pack_bitfield(container, value, 0x0FFFF000U, (UInt32)12U);
    return container;
}

#ifdef  __cplusplus
}
#endif

#endif

/*@}*/
