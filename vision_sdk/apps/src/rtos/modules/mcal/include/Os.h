/* ======================================================================
 *   Copyright (C) 2015-2017 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file   Os.h
 *
 *  \brief  This file contains OS layer prototype declarations and Type
 *          definations.
 */

#ifndef OS_H_
#define OS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/*LDRA_NOANALYSIS*/
#include "Std_Types.h"
/*LDRA_ANALYSIS*/
#include "Os_Cfg.h"

#ifdef __cplusplus
extern "C" {
#endif
/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define ISR(func)   void func(void)

/** \brief Counters related typedefs */
typedef sint16    CounterType;
typedef uint32    TickType;
typedef TickType *TickRefType;

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/*TI_INSPECTED 63 D : MISRAC_2012_R8.6
 * "Reason - Definition for below prototyped procedure
 *  is external to lib, defined in app." */
StatusType GetCounterValue(CounterType CounterID, TickRefType Value);
/*TI_INSPECTED 63 D : MISRAC_2012_R8.6
 * "Reason - Definition for below prototyped procedure
 *  is external to lib, defined in app." */
StatusType GetElapsedValue(CounterType CounterID, TickRefType Value,
                           TickRefType ElapsedValue);
#ifdef __cplusplus
}
#endif

#endif  /* #ifndef OS_H_ */

