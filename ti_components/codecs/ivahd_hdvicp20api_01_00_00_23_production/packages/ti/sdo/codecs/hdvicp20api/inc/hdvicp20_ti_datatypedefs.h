/*
********************************************************************************
 * HDVICP2.0/IVA-HD API
 * 
 * "HDVICP2.0 API" is software module developed for TI's HDVICP2 based SOCs. 
 * This module provides APIs for programming of HDVCIP2.0 hardware accelerators 
 * which can be used for video codec implementation.
 * 
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
********************************************************************************
*/
/**  
********************************************************************************
 * @file  hdvicp20_ti_datatypedefs.h                          
 *                                       
 * @brief This file defines the basic data type definations that are used in the
 *        project. 
 *
********************************************************************************
*/

#ifndef __HDVICP20_TI_DATA_TYPEDEFS__
#define __HDVICP20_TI_DATA_TYPEDEFS__

/*******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*---------------------- data declarations -----------------------------------*/

typedef char  S8;                 /*!< typdef char             S8    */
typedef short S16;                /*!< typedef short           S16   */
typedef int   S32;                /*!< typedef int             S32   */
typedef long  S64;                /*!< typedef long            S64   */

typedef unsigned char      U8;    /*!< typedef unsigned char   U8    */
typedef unsigned short     U16;   /*!< typedef unsigned short  U16   */
typedef unsigned int       U32;   /*!< typedef unsigned int    U32   */
typedef unsigned long long U64;   /*!< typedef unsigned long   U64   */

typedef char  *pS8;               /*!< typedef char*           pS8   */
typedef short *pS16;              /*!< typedef short*          pS16  */
typedef int   *pS32;              /*!< typedef int*            pS32  */
typedef long  *pS64;              /*!< typedef long*           pS64  */

typedef unsigned char  *pU8;      /*!< typedef unsigned char*  pU8  */
typedef unsigned short *pU16;     /*!< typedef unsigned short* pU16 */
typedef unsigned int   *pU32;     /*!< typedef unsigned int*   pU32 */
typedef unsigned long  *pU64;     /*!< typedef unsigned long*  pU64 */

typedef void *pV;
typedef void V;
typedef unsigned int Se_fn_t;     /*!< fixed-pattern bit string using n bits */
typedef int Se_in_t;              /*!< signed integer using n bits           */
typedef unsigned int Se_un_t;     /*!< unsigned integer using n bits         */
typedef int Se_sev_t;             /*!< signed integer exp-golomb coded syntax
                                       element                               */
typedef unsigned int Se_uev_t;    /*!< unsigned integer exp-golomb coded syntax
                                       element                               */
typedef unsigned int Se_tev_t;    /*!< truncated exp-golomb coded syntax
                                       element                               */
typedef unsigned int Se_uv_t;     /*!< unsigned integer, length dependent on 
                                       other syntax                          */

typedef int IDX;       /* for Index     */
typedef int C_BOOL;    /* for Twofold/binary chice  */

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#ifndef SUCCESS
#define SUCCESS  (0)
#endif

#ifndef FAIL
#define FAIL    (-1)
#endif

#endif   /* __HDVICP20_TI_DATA_TYPEDEFS__ */


