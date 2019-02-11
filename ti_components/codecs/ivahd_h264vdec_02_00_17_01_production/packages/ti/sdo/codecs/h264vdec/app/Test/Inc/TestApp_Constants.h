/*
*******************************************************************************
 * HDVICP2.0 Based H.264 HP Decoder
 * 
 * "HDVICP2.0 Based H.264 HP Decoder" is a software module developed on TI's 
 *  HDVICP2 based SOCs. This module is capable of decoding a compressed 
 *  high/main/baseline profile H.264 bit-stream into a YUV 4:2:0 Raw video.
 *  Based on "ISO/IEC 14496-10". 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
*******************************************************************************
*/


/**  
*******************************************************************************
 * @file TestApp_Constants.h                        
 *                                       
 * @brief  This File contains macros & enums that will be used by 
 *         Sample Test application. 
 *
 * @author:  Ramakrishna Adireddy
 *
 * @version 0.1 (Jan 2009) : Base version Created
 * @version 0.2 (Apr 2010) : Added macros and enums for input datasync
 *                           [Keshava Prasad]
 * @version 0.3 (Jul 2010) : Added macros and enums for API out of bound check
 *                           [Ramakrishna Adireddy]
 * @version 0.4 (Aug 2011) : Modified Macros related to width and height to 
 *                           support 4kx4k resolution.
 *                           [Suresh Reddy]
 * @version 0.5 (Oct 2012) : Modified Macros related to width to support
 *                           4320x4096 resolution [Suresh Reddy]
 ******************************************************************************
*/
#ifndef _TESTAPP_CONSTANTS_H_
#define _TESTAPP_CONSTANTS_H_

/******************************************************************************
*  INCLUDE FILES                                                
******************************************************************************/
#include <stdio.h>

/******************************************************************************
*  MACROS                                                
******************************************************************************/

/** 
 *  Macro to enable/disable the run on OMAP4 SDC
*/
/*#define SIMULATOR_RUN */
/*#undef  SIMULATOR_RUN */ 

/** 
 *  Macro to enable/disable the run on OMAP4 SDC
*/
#define DUMP_PROFILE_NUMS
#undef  DUMP_PROFILE_NUMS

/** 
 *  Macro that works as control switch to enable/disable PCI file io
 *  mode.
*/
#define USE_PCI
#undef  USE_PCI

/** 
 *  Macro to enable fast file IO from A9 in Linux environment. Not to be 
 *  enabled here. Add USE_HOST_FILE_IO macro in make file to use fast file i/o.
*/
/*#define USE_HOST_FILE_IO
#undef  USE_HOST_FILE_IO*/

/** 
 *  Macro to control the way application want to write out the yuv data
 *  in output file.
*/
#define DUMP_WITHPADDING
#undef  DUMP_WITHPADDING

/** 
 *  Macro to control Seek operation.
*/
#define TEST_SEEK_OP
#undef  TEST_SEEK_OP

/** 
 *  Macro to enable memory corruption test
*/
#define MEM_CORRUPTION_TEST
#undef  MEM_CORRUPTION_TEST

/** 
 *  Macro to control SEI_VUI dump operation.
*/
#define SEI_VUI_DUMP
#undef  SEI_VUI_DUMP

#define WR_MEM_32(addr, data)  *(volatile unsigned int*)(addr)= \
                                                          (unsigned int)(data)
#define RD_MEM_32(addr)        *(volatile unsigned int*)(addr) 

#ifdef HIGHRES_SUPPORT
/** 
 *  Macro for width of the Display buffer
*/
#define IMAGE_WIDTH            4320 /* To support 4320x4096 resolution */
/** 
 *  Macro for Height of the Display buffer
*/
#define IMAGE_HEIGHT           4096 /* To support 4kx4k resolution */
#else
#define IMAGE_WIDTH            2048
#define IMAGE_HEIGHT           2048
#endif

#define D1_MBINFO_BUFSIZE      (45*36*208)
#define HD_MBINFO_BUFSIZE      (80*45*208)
#define FULLHD_MBINFO_BUFSIZE  (120*68*208)

/** 
 *  Macro to indicate input Buffer size.
*/
#define INPUT_BUFFER_SIZE      (0x000400000)
#define INPUT_DATASYNC_BUFFER_SIZE (INPUT_BUFFER_SIZE >> 3)
#define INFLIE_READ_THRESHOLD  (0x000200000)

/** 
 *  Macro to indicate the input buffer size for fixed Length 
 *  input datasync mode.
*/
#define FIXEDLENGTH_DSMODE_SIZE     (4096)
#define MIN_DATASIZE_SLICEDS        (1024)

/**
 * There is need for multiple DS buffers since the previous buffer 
 * given may not be fully consumed yet.This macro defines the number 
 * of buffers used for slice and NAL datasync inputs.
 */
#define NUM_BUFS_INPUTDS 3
/** 
 *  Max value of dataSyncDescriptor->numBlocks accepted
 *  by decoder when operated in IH264VDEC_TI_SLICEMODE 
*/
#define MAX_BLOCKS_PER_INPUTDS   32
/**
 *  Gap between the datasync blocks in case of slice level datasync.
 *  this value is just used to create non contigous array of slices/NAL units
*/
#define GAP_BETWEEN_DS_BLOCKS 10
/** 
 *  Macro to indicate input Buffer size.
 *  In Full file read case, allocate bigger input buffer.
*/
#define DISPLAY_YUV_SIZE       (IMAGE_WIDTH)*(IMAGE_HEIGHT )

#ifdef _QT_
  #define BIT_STREAM_SIZE        26540
#endif

/** 
 *  Maximum size of the string to hold file name along with path
*/
#define STRING_SIZE            512

/** 
 *  In case of TILER Memory, the stride is constant & below macro defines
 *  the pitch value.
*/
#define APP_TILER_PITCH      (0x4000)

#define CHROMA_CONTAINER_8BITS   1
#define CHROMA_CONTAINER_16BITS  2

#if defined(HOST_ARM9)
  #define VDMAVIEW_EXTMEM      (0x07FFFFFF)
#elif defined(HOST_M3)
  #define VDMAVIEW_EXTMEM      (0xFFFFFFFF)
#elif defined(HOST_ASIC)
  #define VDMAVIEW_EXTMEM      (0x1FFFFFFF)
#else
  #define VDMAVIEW_EXTMEM      (0x07FFFFFF)
#endif

#define   PADX  32
#define   PADY  24

#define END_OF_SEQ_NAL_SIZE    (4)
#define NUM_INPUT_BLOCKS       (1)
#define NUM_INPUT_DATAUNITS    (1)

#define NUM_OUTPUT_BLOCKS      (1)
#define NUM_OUTPUT_DATAUNITS   (1)

#define FULL_IMAGE_X (IMAGE_WIDTH + 2*PADX)
#define FULL_IMAGE_Y (IMAGE_HEIGHT + 4*PADY)

#define ICEC_CNT_CTRL   (0x40050)
#define ICEC_CNT_VAL    (0x40054)
#define SYSTICKREG      (*(volatile int*)0xE000E010)
#define SYSTICKREL      (*(volatile int*)0xE000E014)
#define SYSTICKVAL      (*(volatile int*)0xE000E018)
#define SYSTICKRELVAL   0x00FFFFFF 

#ifdef MEM_CORRUPTION_TEST
#define MC3_MEM_OFFSET     0x00030000 
#define CALC3_MEM_OFFSET   0x00028000  
#define ECD3_MEM_OFFSET    0x00020000    

#define MC3_CFG_OFFSET     0x00059000 
#define CALC3_CFG_OFFSET   0x00058000  
#define ECD3_CFG_OFFSET    0x00059800    

#define SYSCTRL_OFFSET            0x0005A400
#define SYS_CLKCTRL_OFFSET        (SYSCTRL_OFFSET + 0x50)
#define SYS_CLKSTATUS_OFFSET      (SYSCTRL_OFFSET + 0x54)
#endif


/*----------------------------------------------------------------------------*/
/* The IRES_TILEDMEMORY_Obj: Tiled memory resource handles                    */
/*----------------------------------------------------------------------------*/
#define NUM_TILEDMEM_OBJECTS 25

/** 
 ******************************************************************************
 *  @enum       AppOOBchk
 *  @brief      This tells application function's return status.
 *  @details   
 ******************************************************************************
*/
typedef enum _AppOOBchk
{
  APP_SAME_CONFIG = 100,
    /**<
    * This indicates to stick with same config & continue
    */   
  APP_NEXT_CONFIG = 101
    /**<
    * This indicates to jump to next config by exiting current config.
    */   
}AppOOBchk;

/** 
 ******************************************************************************
 *  @enum       AppRetStatus
 *  @brief      This tells application function's return status.
 *  @details   
 ******************************************************************************
*/
typedef enum _AppRetStatus 
{
  APP_EOK,
    /**<
    * This indicates the function return status as OK
    */   
  APP_EFAIL,
    /**<
    * This indicates the function return status as FAIL, but application
    * can proceed further with this status.
    */  
  APP_EXIT
    /**<
    * This indicates the application has exit as some critical error occured.
    */  
}AppRetStatus;

/** 
 ******************************************************************************
 *  @enum       BsReadMode
 *  @brief      This tells the reading mode of input bit stream.
 *  @details   
 ******************************************************************************
*/
typedef enum _BsReadMode 
{
  BS_BUFFER_FULL,
    /**<
    * This indicates that read bit stream until it fills input buffer full.
    * New fill happens only when the bytes consumption by codec crosses a
    * predefined threshold. 
    */   
  BS_FRAME_MODE
    /**<
    * This indicates that input bit stream is read at frame basis. We read
    * exactly the bytes needed for one frame decoding at a time.
    */   
}BsReadMode;

/** 
 ******************************************************************************
 *  @enum       timeCapture
 *  @brief      This tells the reading mode of input bit stream.
 *  @details   
 ******************************************************************************
*/
typedef enum _timeCapture 
{
  PROCESS_START,
  PROCESS_END,   
  HDVICP_ACQUIRE,
  HDVICP_WAIT,
  HDVICP_DONE,  
  HDVICP_RELEASE,
  IVAHD_POSTMSG
}timeCapture;

/** 
 ******************************************************************************
 *  @enum       InputDataSyncMode
 *  @brief      Enumerations for the InputDatasync Modes 
 *  @details   
 ******************************************************************************
*/
typedef enum _InputDataSyncMode 
{
    APP_INPUTDS_OFF = 0, 
      /**< Datasync is off 
      */
    APP_INPUTDS_FIXEDLENGTH = 1,
      /**< Datasync: Interms of multiples of 2K 
      */
    APP_INPUTDS_SLICEMODE = 2,   
      /**< Datasync: Slice Mode 
      */
    APP_INPUTDS_NALMODE = 3  
      /**< Datasync: NAL unit Mode without Start code
      */
}InputDataSyncMode;

/** 
 ******************************************************************************
 *  @enum       metaDataMode
 *  @brief      Enumerations for the InputDatasync Modes 
 *  @details   
 ******************************************************************************
*/
typedef enum _appMetaDataMode 
{
    APP_SEI_DATA = 0, 
      /**< SEI meta data
      */
    APP_VUI_DATA = 1,
      /**< VUI meta data
      */
    APP_MB_INFO = 2   
      /**< Macro Block header data
      */
}metaDataMode;

/** 
 ******************************************************************************
 *  @enum       parBoundaryExitLevel
 *  @brief      Enumerations for exit levels during parameter boudary testing.
 *  @details   
 ******************************************************************************
*/
typedef enum _parBoundaryExitLevel 
{
    CREATE_TIME_LEVEL = 1, 
      /**< Exit at algorithm creation time 
      */
    CONTROL_CALL_LEVEL = 2
      /**< Exit at control call level 
      */
}parBoundaryExitLevel;

#endif
