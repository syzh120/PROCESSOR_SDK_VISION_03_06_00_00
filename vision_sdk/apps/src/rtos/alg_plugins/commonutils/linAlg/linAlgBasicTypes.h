/*=======================================================================
 *
 *            Texas Instruments Internal Reference Software
 *
 *                           EP Systems Lab
 *                     Embedded Signal Processing
 *                             Imaging R&D
 *         
 *         Copyright (c) 2014 Texas Instruments, Incorporated.
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
 *  File: linAlgBasicTypes.h
 *  
 =======================================================================*/

#ifndef _LINALG_BASIC_TYPES_INCLUDED_

#define _LINALG_BASIC_TYPES_INCLUDED_

/*Definition of Flouble */
#if LIN_ALG_FLOUBLE_TYPE == 0
typedef float Flouble;
#elif LIN_ALG_FLOUBLE_TYPE == 1
typedef double Flouble;
#else
#error("Unknown value for LIN_ALG_FLOUBLE_TYPE");
#endif


#endif

