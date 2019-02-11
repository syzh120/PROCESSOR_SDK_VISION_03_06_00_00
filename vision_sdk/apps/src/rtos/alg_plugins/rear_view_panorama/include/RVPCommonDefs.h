/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                    Perception and Analytics Lab
*
*         Copyright (c) 2016 Texas Instruments, Incorporated.
*                        All Rights Reserved.
*
*
*          FOR TI INTERNAL USE ONLY. NOT TO BE REDISTRIBUTED.
*
*                 TI Confidential - Maximum Restrictions
*
*
*
*=======================================================================
*
*  File: RVPCommonDefs.h
*
*  Public (visible to framework) definitions for RVP library
*
=======================================================================*/


//To include system type def header
#ifndef _RVP_COMMONDEFS_H_
#define _RVP_COMMONDEFS_H_


#ifndef PC_VERSION
#include <include/link_api/system.h>
#include "memRequestAlgo.h"
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "../../commonutils/linAlg/linAlg2DTypes.h"
#include "../../commonutils/linAlg/linAlg3DTypes.h"

#define LIN_ALG_FLOUBLE_TYPE 0 /* 0 = float, 1 = double */

/***************************************************************************
ALGORITHM PARAMETERS THAT DO NOT CHANGE WITH USECASE
***************************************************************************/
//RVP 
#define RVP_MAX_NUM_VIEWS (6) /*maximum number of cameras supported*/

/***************************************************************************
ALGORITHM-LEVEL PROCESS STATUS
***************************************************************************/
#define ALGORITHM_PROCESS_OK 0
#define ALGORITHM_PROCESS_FAIL -1
#define ALGORITHM_PROCESS_DISABLED 2

 
#endif //_RVP_COMMONDEFS_H_
